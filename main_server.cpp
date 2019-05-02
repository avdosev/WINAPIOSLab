#include <QCoreApplication>

#include <server.h>

using namespace std;

int main(int argc, char *argv[])
{
    Server server;
    auto resultServerRunning = server.exec();
    return resultServerRunning;
}
