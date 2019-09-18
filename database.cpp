#include "database.h"

#include <QMapIterator>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "stream/filestream.h"

static const QString dirFileDataBase = "./database.db";
static const uint periodAutoSave = 10000; // по моим расчетам около 10 секунд

DataBase::DataBase()
{
    moding = false;

    load(dirFileDataBase);
    autoSaveTimer.set_time_miliseconds(periodAutoSave);
    autoSaveTimer.set_callback([this](){
        qDebug() << "database autosaved";
        this->save(dirFileDataBase);
    });
    autoSaveTimer.start();
}

DataBase::~DataBase()
{
    autoSaveTimer.stop();
    save(dirFileDataBase);
}

int DataBase::count() const {
	return data.size();
}

id_type DataBase::append(TyristManual record) {
	moding = true;
    id_type temp_id = getUniqueId();
    data.insert(temp_id, record);
    data[temp_id].id = temp_id;
    return temp_id;
}

void DataBase::remove(id_type id) {
	data.remove(id);
    moding = true;
}

void DataBase::update(id_type record_id, TyristManual record) {
    moding = true;
    record.id = record_id;
    data[record_id] = record;
}

int DataBase::compareRecordsByID(id_type first, id_type second) {
    return TyristManual::compare(this->record(first),this->record(second));

}

TyristManual DataBase::record(id_type id) const {
	if(data.contains(id))
		return data[id];
    //если нет такого айди то кидаем исключение
    std::string what_error = "records with id " + std::to_string(id) + " not found";
    throw std::runtime_error(what_error);
}

QVector<TyristManual> DataBase::records() {
    QMapIterator<id_type, TyristManual> it (data);
    QVector <TyristManual> res;
	while (it.hasNext()) {
		res.push_back(it.next().value());
	}
	return res;
}

bool DataBase::save(QString filename) {
    FileStream stream;
    if (stream.open(filename, FileStream::out | FileStream::trunc)) {
        qDebug() << "file saved";
    } else {
        qDebug() << "file save error";
        qDebug() << "file:" << filename << "not created";
        return false;
    }

    // сначала закидываем размер
    // потом все элементы контейнера
    stream << data.size();
    QMapIterator<id_type, TyristManual> it (data);
	while (it.hasNext()) {
        TyristManual tmp = it.next().value();
        stream << tmp;
	}

	moding = false;
    return true;
}

bool DataBase::load(QString filename) {
    FileStream stream;
    if(!stream.open(filename, FileStream::in)) {
        qDebug() << "file:" << filename << " not opened";
		return false; // если файл не открылся
	}
    int size;
    stream >> size;
    for (int i = 0; i < size; i++) {
    //while (!stream.eof()) { // не работает
        TyristManual tmp_tyrist;
        stream >> tmp_tyrist;
		append(tmp_tyrist);
    }
	return true;
}

void DataBase::clear() {
	data.clear();
	moding = true;
}

bool DataBase::isModidfied() const {
	return moding;
}


bool DataBase::isUniqueId(id_type id) const {
    if (id == 0) return false;
    return !data.contains(id);
}

id_type DataBase::getUniqueId() const {
    id_type id = static_cast<id_type>(qrand());
    while (!isUniqueId(id)) {
        id = static_cast<id_type>(qrand());
	}
	return id;
}
