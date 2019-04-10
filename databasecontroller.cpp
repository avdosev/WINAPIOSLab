#include "databasecontroller.h"

DataBaseController::DataBaseController(DataBasePrototype* prototype) : prototype_ptr(prototype) {

}

DataBaseController::~DataBaseController() {

}

int DataBaseController::count() const {
    return prototype_ptr->count();
}

id_type DataBaseController::append(TyristManual record) {
    return prototype_ptr->append(record);
}

void DataBaseController::remove(id_type id) {
    prototype_ptr->remove(id);
}

void DataBaseController::update(id_type record_id, TyristManual record) {
    prototype_ptr->update(record_id, record);
}

TyristManual DataBaseController::record(id_type id) const {
    return prototype_ptr->record(id);
}

QVector<TyristManual> DataBaseController::records() {
    return prototype_ptr->records();
}

bool DataBaseController::save(QString filename) {
    return prototype_ptr->save(filename);
}

bool DataBaseController::load(QString filename) {
    return prototype_ptr->load(filename);
}

void DataBaseController::clear() {
    prototype_ptr->clear();
}

bool DataBaseController::isModidfied() const {
    return prototype_ptr->isModidfied();
}
