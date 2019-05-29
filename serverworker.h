#pragma once

#include <database.h>

#include <server_command.h>

#include <pipestream.h>

#include <map>

class ServerWorker
{
    private:
        using pipes_t = std::map<clientID_t, std::shared_ptr<PipeStream>>;
        pipes_t* pipes;
        DataBase* db;
        clientID_t clientid;
        bool running = false;
    public:
        ServerWorker();
        ServerWorker(pipes_t& signalPipe, DataBase& database, clientID_t id);
        bool doCommand(ServerCommand command, PipeStream &,PipeStream &);
        int exec();
        void quit();
};
