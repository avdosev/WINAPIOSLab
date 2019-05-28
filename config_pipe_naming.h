#ifndef SERVER_PIPE_NAMING_H
#define SERVER_PIPE_NAMING_H

#include <QString>

const QString
serverDataInputPipeName = "\\\\.\\pipe\\dataInputPipe",
serverDataOutputPipeName = "\\\\.\\pipe\\dataOutputPipe",
serverCommandInputPipeName = "\\\\.\\pipe\\commandInputPipe",
serverSignalsOutputPipeName = "\\\\.\\pipe\\signalsOutputPipe",
;

const QString
clientDataInputPipeName = "\\\\.\\pipe\\dataOutputPipe",
clientDataOutputPipeName = "\\\\.\\pipe\\dataInputPipe",
clientCommandOutputPipeName = "\\\\.\\pipe\\commandInputPipe",
clientSignalsInputPipeName = "\\\\.\\pipe\\signalsOutputPipe"
;

const QString ConnectPipeName = "\\\\.\\pipe\\connect";

#endif // SERVER_PIPE_NAMING_H
