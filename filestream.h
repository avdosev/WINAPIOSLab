#pragma once

#include <datastream.h>

class FileStream : public DataStream
{
    public:
        bool open(QString filename, uint32_t flags);
};



//#endif // WINDATASTREAM_H
