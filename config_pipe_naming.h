#ifndef SERVER_PIPE_NAMING_H
#define SERVER_PIPE_NAMING_H

#include <QString>

const QString
serverDataInputPipeName = "\\\\.\\pipe\\dataInputPipe",
serverDataOutputPipeName = "\\\\.\\pipe\\dataOutputPipe",
serverCommandInputPipeName = "\\\\.\\pipe\\commandInputPipe"
;

const QString
clientDataInputPipeName = "\\\\.\\pipe\\dataOutputPipe",
clientDataOutputPipeName = "\\\\.\\pipe\\dataInputPipe",
clientCommandOutputPipeName = "\\\\.\\pipe\\commandInputPipe"
;

#endif // SERVER_PIPE_NAMING_H
