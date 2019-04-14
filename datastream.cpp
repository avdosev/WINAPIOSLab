//#include <windows.h>

#include "datastream.h"

#include <windows.h>
#include <QDebug>

DataStream::DataStream() {
    file = NULL;
    //memset(&infoFile, 0, sizeof(infoFile));
}

DataStream::~DataStream() {
    close();
}

bool DataStream::open(QString filename, uint32_t flags) {
    if (file != NULL) close();
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
        CreationDisposition |= OPEN_EXISTING;
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
    }

    if ((bitflags & io::ate) && fileOpen) SetFilePointer(file,0,NULL,FILE_END);

    return fileOpen;
}

bool DataStream::is_open() {
    return file != INVALID_HANDLE_VALUE && file != NULL;
}

void DataStream::close() {
    CloseHandle(file);
    file = NULL;
}

bool DataStream::eof() {
    bool rd;
    rd = true;
    return !rd;
}

bool DataStream::read(void* begin, Size_t size) {
    auto bRes = ReadFile(file, begin, size, &size, NULL);
    if (!bRes) {
        qDebug() << "fail read";
    }
    return bRes;
}

bool DataStream::write(void* begin, Size_t size) {
    auto bRes = WriteFile(file, begin, size, &size, NULL);
    if (!bRes) {
        qDebug() << "fail write";
    }
    return bRes;
}

DataStream& operator << (DataStream& stream, QString value) {
    stream << value.size();
    for (auto item : value) {
        stream << item;
    }
    return stream;
}

DataStream& operator << (DataStream& stream, QChar value) {
    stream.write(&value.unicode(), sizeof(value));
    return stream;
}

DataStream& operator >> (DataStream& stream, QString &value) {
    int size;
    stream >> size;
    value.clear();
    value.reserve(size);

    QChar item;
    for (int i = 0; i < size; i++) {
        stream >> item;
        value.push_back(item);
    }

    return stream;
}

DataStream& operator >> (DataStream& stream, QChar &value) {
    uint16_t chr;
    stream.read(&chr, sizeof(chr));
    value = chr;
    return stream;
}


