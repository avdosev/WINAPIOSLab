#include "server.h"

#include <QDebug>

#include <pipestream.h>

Server::Server() : running(false)
{

}

int Server::exec() {
    qDebug() << "STARTING THE SERVER";

    QString dataInputPipeName = "",
            dataOutputPipeName = "",
            commandInputPipeName = "";

    PipeStream dataInputPipe, dataOutputPipe, commandInputPipe;



    if (!dataInputPipe.open(dataInputPipeName, DataStream::create | DataStream::in) ||
            dataOutputPipe.open(dataOutputPipeName, DataStream::create | DataStream::out) ||
            commandInputPipe.open(commandInputPipeName, DataStream::create | DataStream::in))
    {
        qCritical() << "Couldn't create pipe";
        return -1;
    }

    qDebug() << "Input pipe has created." << endl << "Waiting for clients.." << endl;

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
                output << db.count();
                break;
            }
            case ServerCommand::append: {
                TyristManual value;
                input >> value;
                output << db.append(value);
                break;
            }
            case ServerCommand::remove: {
                id_type id;
                input >> id;
                db.remove(id);
                break;
            }
            case ServerCommand::update: {
                id_type id;
                TyristManual value;
                input >> id >> value;
                db.update(id, value);
                break;
            }
            case ServerCommand::compare_two_records: {
                id_type first, second;
                input >> first >> second;
                output << db.compareRecordsByID(first, second);
                break;
            }
            case ServerCommand::records: {
                auto recs = db.records();
                output << recs.size();
                for (TyristManual item : recs) {
                    output << item;
                }
                break;
            }
            case ServerCommand::record: {
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
