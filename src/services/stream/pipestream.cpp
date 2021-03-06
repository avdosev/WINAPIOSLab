#include "pipestream.h"

#include <winbase.h>
#include "filestream.h"
#include <QDebug>

PipeStream::PipeStream() {

}

PipeStream::PipeStream(QString filename, uint32_t flags) {
    open(filename, flags);
}

bool PipeStream::open(QString filename, uint32_t flags) {
    DWORD openMode = 0, pipeMode = 0;
    DWORD bufferSizeIn = 1024, bufferSizeOut = 1024, maxInstances = 254, timeOut = 5000;


    pipeMode = PIPE_TYPE_MESSAGE | PIPE_WAIT;
    pipeMode |= PIPE_READMODE_MESSAGE;
    if (flags & io::in) {
        openMode |= PIPE_ACCESS_INBOUND;
    }
    if (flags & io::out) {
        openMode |= PIPE_ACCESS_OUTBOUND;
    }


    if (flags & io::create) {
        file = CreateNamedPipeA(filename.toStdString().c_str(),
                         openMode,
                         pipeMode,
                         maxInstances,
                         bufferSizeIn,
                         bufferSizeOut,
                         timeOut,
                         nullptr);
        type = 2;
    } else {
        // игра классов
        FileStream game;
        game.open(filename, flags);
        //PipeStream &next_game = reinterpret_cast <PipeStream&>(game);
        //this->file = next_game.file;
        file = game.getHandle();
        game.setHandle(NULL);
        type = 1;
    }


    bool fileOpen = file != INVALID_HANDLE_VALUE;

    if (!fileOpen) {
        qDebug() << "Pipe create error: " << filename;
    }

    return fileOpen;
}

bool PipeStream::waitingClient() {
    return ConnectNamedPipe(file, nullptr);
}

void PipeStream::close() {
    if (type < 2) {
        CloseHandle(file);
    } else {
        DisconnectNamedPipe(file);
    }
    file = NULL;
}
