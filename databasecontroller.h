#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <databaseprototype.h>
#include <pipestream.h>

class DataBaseController : public DataBasePrototype
{
    private:
        mutable PipeStream commandOutputStream, dataInputStream, dataOutputStream;
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
};

#endif // DATABASECONTROLLER_H
