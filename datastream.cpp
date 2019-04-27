#include "datastream.h"

#include <windows.h>
#include <QDebug>

DataStream::DataStream()
{
    file = NULL;
}

DataStream::~DataStream() {
    close();
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
    Size_t readByte = size;
    auto bRes = ReadFile(file, begin, size, &readByte, NULL);
    if (!bRes && readByte != size) {
        qDebug() << "fail read";
    }
    return bRes;
}

bool DataStream::write(void* begin, Size_t size) {
    Size_t readByte = size;
    auto bRes = WriteFile(file, begin, size, &readByte, NULL);
    if (!bRes && readByte != size) {
        qDebug() << "fail write";
    }
    return bRes;
}

HANDLE DataStream::getHandle() const {
    return this->file;
}
void DataStream::setHandle(HANDLE newHandle) {
    this->file = newHandle;
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
