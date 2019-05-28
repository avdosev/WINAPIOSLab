#include "serverworker.h"

#include <QDebug>

#include <pipestream.h>
#include <config_pipe_naming.h>

ServerWorker::ServerWorker(PipeStream& signalPipe, DataBase& database) : running(false), signalOutputPipe(signalPipe), db(database)
{

}

int ServerWorker::exec(clientID_t id) {
    qDebug() << "STARTING THE SERVER";



    PipeStream dataInputPipe, dataOutputPipe, commandInputPipe;

    if (!dataInputPipe.open(serverDataInputPipeName + QString::number(id), DataStream::create | DataStream::in) ||
            !dataOutputPipe.open(serverDataOutputPipeName + QString::number(id), DataStream::create | DataStream::out) ||
            !commandInputPipe.open(serverCommandInputPipeName + QString::number(id), DataStream::create | DataStream::in))
    {
        qCritical() << "Couldn't create pipe";
        return -1;
    }

    qDebug() << "Input pipe has created." << endl << "Waiting for clients.." << endl;
    // по идее достаточно дождаться какогото одного
    // но это не точно
    commandInputPipe.waitingClient();

    qDebug() << "Client has been connected." << endl << endl;


    do {
        ServerCommand c;
        // чтение из потока команд
        commandInputPipe >> c;
        running = this->doCommand(c, dataInputPipe, dataOutputPipe);
    } while (running);

    qDebug() << "########## FINISHING THE SERVER ##########" << endl << endl;

    return 0;
}


bool ServerWorker::doCommand(ServerCommand command, PipeStream &input, PipeStream &output) {
    try {
        switch (command) {
            case ServerCommand::count: {
                qDebug() << "count";
                output << db.count();
                break;
            }
            case ServerCommand::append: {
                qDebug() << "append";
                TyristManual value;
                input >> value;
                signalOutputPipe << ClientCommand::append << db.append(value);
                break;
            }
            case ServerCommand::remove: {
                qDebug() << "remove";
                id_type id;
                input >> id;
                db.remove(id);
                signalOutputPipe << ClientCommand::remove << id;
                break;
            }
            case ServerCommand::update: {
                qDebug() << "update";
                id_type id;
                TyristManual value;
                input >> id >> value;
                db.update(id, value);
                signalOutputPipe << ClientCommand::update << id;
                break;
            }
            case ServerCommand::compare_two_records: {
                // qDebug() << "compare two record";
                // как бы да, но нет
                id_type first, second;
                input >> first >> second;
                output << db.compareRecordsByID(first, second);
                break;
            }
            case ServerCommand::records: {
                qDebug() << "records";
                auto recs = db.records();
                output << recs.size();
                for (TyristManual item : recs) {
                    output << item;
                }
                break;
            }
            case ServerCommand::record: {
                qDebug() << "record";
                id_type id;
                input >> id;
                output << db.record(id);
                break;
            }
            case ServerCommand::save: {
                QString filename;
                input >> filename;
                output << db.save(filename);
                break;
            }
            case ServerCommand::load: {
                QString filename;
                input >> filename;
                output << db.load(filename);
                break;
            }
            case ServerCommand::clear: {
                qDebug() << "clear";
                signalOutputPipe << ClientCommand::clear;
                db.clear();
                break;
            }
            case ServerCommand::is_modified: {
                output << db.isModidfied();
                break;
            }
            case ServerCommand::end_connection: {
                return false;
            }
            default: {
                qDebug() << "dont have command: " << long(command);
            }
        }
    } catch (std::runtime_error error) {
        qCritical() << error.what();
        return false;
    }
    return true;
}

void ServerWorker::quit() {
    signalOutputPipe << ClientCommand::end_connection;
}
