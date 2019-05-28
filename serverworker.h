#pragma once

#include <database.h>

#include <server_command.h>

#include <pipestream.h>

using clientID_t = unsigned;

class ServerWorker
{
    private:
        PipeStream& signalOutputPipe;
        DataBase& db;
        bool running;
    public:
        ServerWorker(PipeStream& signalPipe, DataBase& database);
        bool doCommand(ServerCommand command, PipeStream &,PipeStream &);
        int exec(clientID_t);
        void quit();
};
