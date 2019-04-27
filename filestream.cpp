//#include <windows.h>

#include "filestream.h"

#include <winbase.h>

#include <QDebug>


bool FileStream::open(QString filename, uint32_t flags) {
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
        qDebug() << "File open error: " << filename;
    }

    if ((bitflags & io::ate) && fileOpen) SetFilePointer(file,0,NULL,FILE_END);

    return fileOpen;
}
