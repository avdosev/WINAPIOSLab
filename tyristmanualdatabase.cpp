#include "tyristmanualdatabase.h"

#include <QMapIterator>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "datastream.h"

tyristManualDataBase::tyristManualDataBase()
{
    moding = false;
}

tyristManualDataBase::~tyristManualDataBase()
{
    QString dir = QDir::currentPath() + "\\database.db";
    if (!save(dir)) {
        qDebug() << "не успешное завершение базы данных";
    }
}

int tyristManualDataBase::count() const {
	return data.size();
}

id_type tyristManualDataBase::append(tyristManual record) {
	moding = true;
    id_type temp_id = getUniqueId();
    data.insert(temp_id, record);
    data[temp_id].id = temp_id;
    return temp_id;
}

void tyristManualDataBase::remove(id_type id) {
	data.remove(id);
    moding = true;
}

void tyristManualDataBase::update(id_type record_id, tyristManual record) {
    moding = true;
    record.id = record_id;
    data[record_id] = record;

}

tyristManual tyristManualDataBase::record(id_type id) const {
	if(data.contains(id))
		return data[id];
    //если нет такого айди то кидаем исключение
    throw std::runtime_error("запись с нужным id отсутствует");
}

QVector<tyristManual> tyristManualDataBase::records() {
	QMapIterator<id_type, tyristManual> it (data);
	QVector <tyristManual> res;
	while (it.hasNext()) {
		res.push_back(it.next().value());
	}
	//qSort(res);
	return res;
}

bool tyristManualDataBase::save(QString filename) {
    DataStream stream;
    if (stream.open(filename, DataStream::out | DataStream::trunc)) {
        qDebug() << "файл успешно был создан";
    } else {
        qDebug() << "не предвиденная ошибка";
        qDebug() << "файл:" << filename << "не сохранен";
        return false;
    }
	QMapIterator<id_type, tyristManual> it (data);
	while (it.hasNext()) {
		tyristManual tmp = it.next().value();
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

bool tyristManualDataBase::load(QString filename) {
	QFile *file = new QFile(filename);
    if(!file->open(QIODevice::ReadOnly)) {
		return false; // если файл не открылся
	}
    /*QDataStream stream(file);
	while (!stream.atEnd()) {//от не пригодилось
		tyristManual tmp_tyrist;
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
    }*/
	return true;
}

void tyristManualDataBase::clear() {
	data.clear();
	moding = true;
}

bool tyristManualDataBase::isModidfied() const {
	return moding;
}


bool tyristManualDataBase::isUniqueId(id_type id) const {
    if (id == 0) return false;
    return !data.contains(id);
}

id_type tyristManualDataBase::getUniqueId() const {
	id_type id = qrand();
    while (!isUniqueId(id)) {
		id = qrand();
	}
	return id;
}
