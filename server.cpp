#include "server.h"

#include <QDebug>

#include <pipestream.h>

Server::Server() : running(false)
{

}

int Server::exec() {
    qDebug() << "STARTING THE SERVER";

    QString dataInputPipeName = "\\\\.\\pipe\\dataInputPipe",
            dataOutputPipeName = "\\\\.\\pipe\\dataOutputPipe",
            commandInputPipeName = "\\\\.\\pipe\\commandInputPipe";

    PipeStream dataInputPipe, dataOutputPipe, commandInputPipe;

    if (!dataInputPipe.open(dataInputPipeName, DataStream::create | DataStream::in) ||
            !dataOutputPipe.open(dataOutputPipeName, DataStream::create | DataStream::out) ||
            !commandInputPipe.open(commandInputPipeName, DataStream::create | DataStream::in))
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


bool Server::doCommand(ServerCommand command, PipeStream &input, PipeStream &output) {
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
                output << db.append(value);
                break;
            }
            case ServerCommand::remove: {
                qDebug() << "remove";
                id_type id;
                input >> id;
                db.remove(id);
                break;
            }
            case ServerCommand::update: {
                qDebug() << "update";
                id_type id;
                TyristManual value;
                input >> id >> value;
                db.update(id, value);
                break;
            }
            case ServerCommand::compare_two_records: {
                qDebug() << "compare two record";
                id_type first, second;
                input >> first >> second;
                output << db.compareRecordsByID(first, second);
                break;
            }
            case ServerCommand::records: {
                qDebug() << "records";
                auto recs = db.records();
                qDebug() << "size" << recs.size() << "\nwith items";
                output << recs.size();
                for (TyristManual item : recs) {
                    output << item;
                    qDebug() << "item: " << item.id;

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
                db.clear();
                break;
            }
            case ServerCommand::is_modified: {
                break;
            }
            case ServerCommand::end_connection: {
                output << db.isModidfied();
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
