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
    map<clientID_t, ServerWorker> workers;
    bool running = true;

    Thread connectLoop;
    connectLoop.start( [&](){
        PipeStream connectPipe(ConnectPipeName, DataStream::create | DataStream::out);
        clientID_t clientID = 0;
        while (running) {
            connectPipe.waitingClient();
            clientID++;
            workers.emplace(make_pair(clientID, std::move(ServerWorker(signalOutputPipe, db)))); // TODO FIX
            auto& swork = workers[clientID];
            Thread worker;
            worker.start([clientID, &swork](){
                auto resCode = swork.exec(clientID);
                qDebug() << "server worker end with code " << resCode;
            });
            connectPipe << clientID;
        }
    });

    char puk; // смысловая переменная

    // ждемс
    cout << "Для продолжения работы программы нажмите любую клавишу..." << endl;
    cin.get();

    // press F to pay respect
    running = false;
    if (connectLoop.running()) {
        connectLoop.quit(); // в бан
    }
    for (auto& item: workers) {
        item.second.quit();
    }
    signalOutputPipe << ClientCommand::end_connection;
    return 0;
}
