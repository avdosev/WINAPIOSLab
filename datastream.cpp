#include <windows.h>

#include "datastream.h"
#include <QDebug>

DataStream::DataStream() {
    file = NULL;
    memset(&infoFile, 0, sizeof(infoFile));
}

DataStream::~DataStream() {
    close();
}

bool DataStream::open(QString filename, uint32_t flags) {
    DWORD DesiredAccess = 0, // в режим чтения/запись
            CreationDisposition = 0, // как открывать
            FileAttribute = 0; // атрибут файла - константа
    uint32_t bitflags = flags;
    FileAttribute = FILE_ATTRIBUTE_NORMAL;
    if (bitflags & io::in)  DesiredAccess |= GENERIC_READ;
    if (bitflags & io::out) DesiredAccess |= GENERIC_WRITE;

    if (bitflags & io::create) {
        CreationDisposition |= CREATE_ALWAYS;
    } else {
        CreationDisposition |= OPEN_ALWAYS;
    }

    if (bitflags & io::trunc) {
        open(filename, io::create); // создаем файл в любом случае после чего идем по плану
        close();
    }

    file = CreateFileA(filename.toStdString().c_str(),
                       DesiredAccess,
                       0,
                       NULL,
                       CreationDisposition,
                       FileAttribute,
                       NULL);

    bool fileOpen = file != INVALID_HANDLE_VALUE;

    if (!fileOpen) {
        qDebug() << "Ошибка при открытии файла: " << filename;
    } else {
        qDebug() << "Файл: " << filename << " успешно открыт";
    }

    if ((bitflags & io::ate) && fileOpen) SetFilePointer(file,0,NULL,FILE_END);

    return fileOpen;
}

bool DataStream::is_open() {
    return file != INVALID_HANDLE_VALUE && file != NULL;
}

void DataStream::close() {
    qDebug() << "закрытие потока";
    CloseHandle(file);
    file = NULL;
}

bool DataStream::eof() {
    return endFile;
}

Size_t DataStream::read(void* begin, Size_t size) {
    endFile = ReadFile(file, begin, size, &size, NULL) && size != 0;
    return size;
}

Size_t DataStream::write(void* begin, Size_t size) {
    auto bRes = WriteFile(file, begin, size, &size, NULL);
    if (!bRes) {
        qDebug() << "fail write";
    }
    return size;
}

DataStream& operator << (DataStream& stream, QString value) {
    qDebug() << "QString operator " << value << sizeof(value);
    stream << value.size();
    for (auto item : value) {
        stream << item;
    }
    return stream;
}

DataStream& operator << (DataStream& stream, QChar value) {
    qDebug() << "QChar operator " << value << sizeof(value);
    stream.write(&value.unicode(), sizeof(value));
    return stream;
}


