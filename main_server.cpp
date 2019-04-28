#include <QCoreApplication>

#include <iostream>
#include <map>
#include <functional>

#include <server_command.h>

using namespace std;

void logCommand(QString c)
{
    cout << "Current command: " << c.toStdString() << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();

    QString dataInputPipeName,
            dataOutputPipeName,
            commandInputPipeName;

    cout << "########## STARTING THE SERVER ##########" << endl << endl;

    //hPipeIn = CreateNamedPipe(inputPipeName2,

    if (false)
    {
        cerr << "Couldn't create input pipe" << endl;
        cin.get();
        return 0;
    }

    cout << "Input pipe has created." << endl << "Waiting for clients.." << endl;
    //ConnectNamedPipe(hPipeIn, nullptr);
    cout << "Client output has been connected." << endl << endl;

    bool running = true;
    map <ServerCommand, function<void()>> commands;
    while (running)
    {
        ServerCommand c;

        // чтение из потока команд

    }
    cout << "########## FINISHING THE SERVER ##########" << endl << endl;

    return 0;
}

void getCount()
{
    logCommand("count");
}

void doAppend()
{
    logCommand("append");

}

void doUpdate()
{
    logCommand("update");

}

void doRemove()
{
    logCommand("remove");

}

void getRecord()
{
    logCommand("record");

}

void getRecords()
{
    logCommand("records");

}

void doClear()
{
    logCommand("clear");

}

void getModified()
{
    logCommand("modified");
}
