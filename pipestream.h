#pragma once

#include <datastream.h>

class PipeStream : public DataStream
{
    public:
        PipeStream();
        PipeStream(QString filename, uint32_t flags);
        bool open(QString filename, uint32_t flags);
        bool waitingClient();
};
