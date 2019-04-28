#pragma once

#include <datastream.h>

class PipeStream : public DataStream
{
    public:
        bool open(QString filename, uint32_t flags);
        bool waitingClient();
};
