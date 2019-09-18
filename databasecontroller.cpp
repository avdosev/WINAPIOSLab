#include "databasecontroller.h"

#include <server_command.h>

#include <exception>

#include <QDebug>
#include <QThread>

#include "config/config_pipe_naming.h"

Q_DECLARE_METATYPE(ClientCommand)

DataBaseController::DataBaseController() {
    bool fullConnect = false;
    int poputok = 0;
    bool commandOutConnected = false, dataInputConnected = false, dataOutputConnected = false,
            signalInputConnected = false;

    clientID_t id = 0;

    PipeStream connectPipe(ConnectPipeName, DataStream::in);

    if (connectPipe.is_open()) {
        connectPipe >> id;
        qDebug() << "my id: " << id;
        connectPipe.close();

        commandOutConnected = commandOutputStream.open(clientCommandOutputPipeName + QString::number(id), DataStream::out);
        dataInputConnected = dataInputStream.open(clientDataInputPipeName + QString::number(id), DataStream::in);
        dataOutputConnected = dataOutputStream.open(clientDataOutputPipeName + QString::number(id), DataStream::out);
        signalInputConnected = signalInputStream.open(clientSignalsInputPipeName + QString::number(id), DataStream::in);

        fullConnect = commandOutConnected && dataInputConnected && dataOutputConnected && signalInputConnected;
    }

    if (!fullConnect) {
        throw std::runtime_error("error connected to server");
    }

    qRegisterMetaType <ClientCommand> ("ClientCommand");
    checkerThread = new QThread();
    checker = new ServerSignalChecker(signalInputStream);
    checker->moveToThread(checkerThread);
    connect(checkerThread, SIGNAL(finished()),  checkerThread, SLOT(deleteLater()));
    connect(checkerThread, SIGNAL(started()), checker, SLOT(start()));
    connect(this, SIGNAL(checking_next_signal()), checker, SLOT(start()));
    connect(checker, &ServerSignalChecker::check_command, this, &DataBaseController::serverSignaled);
    checkerThread->start();
}

DataBaseController::~DataBaseController() {
    if (commandOutputStream.is_open()) {
        qDebug() << "end connection";
        commandOutputStream << ServerCommand::end_connection;
    }
}

DataBaseController::ServerSignalChecker::ServerSignalChecker(PipeStream& input) : signalInputStream(input) {

}

void DataBaseController::ServerSignalChecker::start() {
    ClientCommand command;
    signalInputStream >> command;
    emit check_command(command);
}

void DataBaseController::serverSignaled(ClientCommand command) {
    id_type id;
    switch (command) {
        case ClientCommand::append:
            signalInputStream >> id;
            emit append_signal(id);
            break;
        case ClientCommand::update:
            signalInputStream >> id;
            emit update_signal(id);
            break;
        case ClientCommand::remove:
            signalInputStream >> id;
            emit remove_signal(id);
            break;
        case ClientCommand::clear:
            emit clear_signal();
            break;
        case ClientCommand::end_connection:
            emit server_stop_signal();
        default:
            qDebug() << "сервак посылает странные сигналы";
    }
    if (command != ClientCommand::end_connection)
        emit checking_next_signal();
}


int DataBaseController::count() const {
    int count;
    commandOutputStream << ServerCommand::count;
    dataInputStream >> count;
    return count;
}

void DataBaseController::append(TyristManual record) {
    commandOutputStream << ServerCommand::append;
    dataOutputStream << record;
}

void DataBaseController::remove(id_type id) {
    commandOutputStream << ServerCommand::remove;
    dataOutputStream << id;
}

void DataBaseController::update(id_type record_id, TyristManual record) {
    commandOutputStream << ServerCommand::update;
    dataOutputStream << record_id << record;
}

TyristManual DataBaseController::record(id_type id) const {
    TyristManual tmp;

    commandOutputStream << ServerCommand::record;
    dataOutputStream << id;
    dataInputStream >> tmp;

    return tmp;
}

QVector<TyristManual> DataBaseController::records() {
    QVector<TyristManual> tmp;
    int vector_size = 0;
    commandOutputStream << ServerCommand::records;
    dataInputStream >> vector_size;
    tmp.reserve(vector_size);
    for (int i = 0; i < vector_size; i++) {
        TyristManual tmp_record;
        dataInputStream >> tmp_record;
        tmp.push_back(tmp_record);
    }
    return tmp;
}

bool DataBaseController::save(QString filename) {
    bool bulk;

    commandOutputStream << ServerCommand::save;
    dataOutputStream << filename;
    dataInputStream >> bulk;

    return bulk;
}

bool DataBaseController::load(QString filename) {
    bool bulk;

    commandOutputStream << ServerCommand::load;
    dataOutputStream << filename;
    dataInputStream >> bulk;

    return bulk;
}

void DataBaseController::clear() {
    commandOutputStream << ServerCommand::clear;
}

bool DataBaseController::isModidfied() const {
    bool res;

    commandOutputStream << ServerCommand::is_modified;
    dataInputStream >> res;

    return res;
}

int DataBaseController::compareRecordsByID(id_type first, id_type second) {
    int res;

    commandOutputStream << ServerCommand::compare_two_records;
    dataOutputStream << first << second;
    dataInputStream >> res;

    return res;
}
