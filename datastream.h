#ifndef WINDATASTREAM_H
#define WINDATASTREAM_H

#include <QString>
#include <QDebug>

#include <windows.h>


using Size_t = unsigned long;

class DataStream
{
    private:
        HANDLE file;
        OFSTRUCT infoFile;
        bool endFile;
    public:
        enum io {
            in = 1,             // открыть для чтения
            out = 2,            // отрыть для записи
            ate = 4,            // при открытии переместить указатель в конец файла
            app = in | ate,     // открыть файл для записи в конец файла
            trunc = 8           // удалить содержимое файла, если он существует
        };

        DataStream();
        ~DataStream();
        bool open(QString filename, uint32_t flags);
        bool is_open();
        void close();
        bool eof();
        Size_t write(void* begin, Size_t size);
        Size_t read(void* begin, Size_t size);

};

DataStream& operator << (DataStream&, QChar);
DataStream& operator << (DataStream&, QString);

template <typename num_t>
DataStream& operator << (DataStream& stream, num_t value) {
    qDebug() << "num_t operator " << value << sizeof(num_t);
    stream.write(&value, sizeof(value));
    return stream;
}

#endif // WINDATASTREAM_H
