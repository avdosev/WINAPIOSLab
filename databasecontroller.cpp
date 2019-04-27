#include "databasecontroller.h"

#include <server_command.h>

const static QString
commandOutputStreamName,
dataInputStreamName,
dataOutputStreamName
;

DataBaseController::DataBaseController() {
    bool fullConnect = true, notConnectedStream = false;

    bool commandOutConnected
    commandOutputStream.open(commandOutputStreamName, DataStream::out);
    dataInputStream.open(dataInputStreamName, DataStream::in);
    dataOutputStream.open(dataOutputStreamName, DataStream::out);

    if (!fullConnect);
}

DataBaseController::~DataBaseController() {

}

int DataBaseController::count() const {

}

id_type DataBaseController::append(TyristManual record) {

}

void DataBaseController::remove(id_type id) {

}

void DataBaseController::update(id_type record_id, TyristManual record) {

}

TyristManual DataBaseController::record(id_type id) const {

}

QVector<TyristManual> DataBaseController::records() {

}

bool DataBaseController::save(QString filename) {

}

bool DataBaseController::load(QString filename) {

}

void DataBaseController::clear() {

}

bool DataBaseController::isModidfied() const {

}
