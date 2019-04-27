#ifndef PIPESTREAM_H
#define PIPESTREAM_H

#include <datastream.h>

class PipeStream : public DataStream
{
    public:
        bool open(QString filename, uint32_t flags);
};

#endif // PIPESTREAM_H
