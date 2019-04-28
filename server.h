#ifndef SERVER_H
#define SERVER_H

#include <database.h>
#include <server_command.h>

class Server
{
    private:
        DataBase db;
        bool running;
    public:
        Server();
        bool doCommand(ServerCommand command, PipeStream &,PipeStream &);
        int exec();
        void quit();
};

#endif // SERVER_H
