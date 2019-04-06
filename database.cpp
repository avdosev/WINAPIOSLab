#include "database.h"

#include <QMapIterator>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "datastream.h"

static const QString nameFileDataBase = "database.db";

DataBase::DataBase()
{
    moding = false;

    QString dir = QDir::currentPath() + "\\" + nameFileDataBase;
    load(dir);
}

DataBase::~DataBase()
{
    QString dir = QDir::currentPath() + "\\" + nameFileDataBase;
    save(dir);
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

TyristManual DataBase::record(id_type id) const {
	if(data.contains(id))
		return data[id];
    //если нет такого айди то кидаем исключение
    throw std::runtime_error("запись с нужным id отсутствует");
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
    DataStream stream;
    if (stream.open(filename, DataStream::out | DataStream::trunc)) {
        qDebug() << "файл успешно был создан";
    } else {
        qDebug() << "не предвиденная ошибка";
        qDebug() << "файл:" << filename << "не создан";
        return false;
    }

    // сначала закидываем размер
    // потом все элементы контейнера
    stream << data.size();
    QMapIterator<id_type, TyristManual> it (data);
	while (it.hasNext()) {
        TyristManual tmp = it.next().value();
        stream << tmp.get_restType();
        stream << tmp.get_country();
        stream << tmp.get_restPlace();
        stream << tmp.get_cost();
        stream << tmp.get_duration();
		stream << tmp.get_visa();
	}

	moding = false;
    return true;
}

bool DataBase::load(QString filename) {
    DataStream stream;
    if(!stream.open(filename, DataStream::in)) {
        qDebug() << "файл:" << filename << " не открылся";
		return false; // если файл не открылся
	}
    int size;
    stream >> size;
    for (int i = 0; i < size; i++) {
    //while (!stream.eof()) { // не работает
        TyristManual tmp_tyrist;
		QString tmp_str;
		int tmp_int;
		stream >> tmp_int;
		tmp_tyrist.set_restType(tmp_int);
		stream >> tmp_int;
        tmp_tyrist.set_country(tmp_int);
		stream >> tmp_str;
        tmp_tyrist.set_restPlace(tmp_str);
		stream >> tmp_int;
        tmp_tyrist.set_cost(tmp_int);
		stream >> tmp_int;
        tmp_tyrist.set_duration(tmp_int);
		stream >> tmp_int;
		tmp_tyrist.set_visa(tmp_int);
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
