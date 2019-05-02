#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <databaseprototype.h>
#include <pipestream.h>
#include <thread.h>
#include <QObject>

class DataBaseController : public QObject, public DataBasePrototype
{
        Q_OBJECT
    private:
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream, signalInputStream;
        Thread chekingSignal;
    public:
        DataBaseController();
        ~DataBaseController();
        int count() const;
        id_type append(TyristManual record);
        void remove(id_type id);
        void update(id_type record_id, TyristManual record);
        int compareRecordsByID(id_type, id_type);
        TyristManual record(id_type id) const;
        QVector<TyristManual> records();
        bool save(QString filename);
        bool load(QString filename);
        void clear();
        bool isModidfied() const;
    signals:
        void update_signal(id_type);
        void append_signal(id_type);

};

#endif // DATABASECONTROLLER_H
