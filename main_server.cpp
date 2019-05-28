#include <QCoreApplication>

#include <config_pipe_naming.h>
#include <database.h>
#include <pipestream.h>
#include <serverworker.h>
#include <thread.h>

#include <QDebug>
#include <iostream>

#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    DataBase db;
    PipeStream signalOutputPipe(serverSignalsOutputPipeName, DataStream::create | DataStream::out);
    std::map<clientID_t, ServerWorker> workers;
    bool running = true;

    Thread connectLoop;
    connectLoop.start( [&running, signalOutputPipe](){
        PipeStream connectPipe(ConnectPipeName, DataStream::create | DataStream::out);
        clientID_t clientID = 0;
        while (running) {
            connectPipe.waitingClient();
            clientID++;
            ServerWorker swork(signalOutputPipe, db);
            Thread worker;
            worker.start([clientID, &swork](){
                auto resCode = swork.exec(clientID);
                qDebug() << "server worker end with code " << resCode;
            });
            connectPipe << clientID;
        }
    });

    running = false;
    signalOutputPipe << ClientCommand::end_connection;

}
