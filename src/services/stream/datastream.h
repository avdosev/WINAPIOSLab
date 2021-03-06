#pragma once

#include <QString>

#include <windef.h>

using Size_t = unsigned long;

class DataStream
{
    protected:
        HANDLE file;
        //OFSTRUCT infoFile;
        bool endFile;
    public:
        enum io {
            in = 1,             // открыть для чтения
            out = 2,            // отрыть для записи
            ate = 4,            // при открытии переместить указатель в конец файла
            app = out | ate,    // открыть файл для записи в конец файла
            create = 8,         // создать новый файл
            trunc = 16          // удалить содержимое файла, если он существует
        };

        DataStream();
        virtual ~DataStream();
        bool is_open();
        virtual void close();
        bool eof();
        bool write(void* begin, Size_t size);
        bool read(void* begin, Size_t size);

        // в нормальном классе так быть не должно
        HANDLE getHandle() const;
        void setHandle(HANDLE);


        virtual bool open(QString filename, uint32_t flags) = 0;
};

DataStream& operator << (DataStream&, QChar);
DataStream& operator << (DataStream&, QString);
DataStream& operator >> (DataStream&, QChar&);
DataStream& operator >> (DataStream&, QString&);

template <typename num_t>
DataStream& operator << (DataStream& stream, num_t value) {
    stream.write(&value, sizeof(value));
    return stream;
}

template <typename num_t>
DataStream& operator >> (DataStream& stream, num_t& value) {
    stream.read(&value, sizeof(value));
    return stream;
}

