#ifndef DATABASEPROTOTYPE_H
#define DATABASEPROTOTYPE_H

#include <tyristmanual.h>

#include <QVector>

class DataBasePrototype
{
    public:
        virtual int count() const = 0;
        virtual id_type append(TyristManual record) = 0;
        virtual void remove(id_type id) = 0;
        virtual void update(id_type record_id, TyristManual record) = 0;
        virtual TyristManual record(id_type id) const = 0;
        virtual QVector<TyristManual> records() = 0;
        virtual bool save(QString filename) = 0;
        virtual bool load(QString filename) = 0;
        virtual void clear() = 0;
        virtual bool isModidfied() const = 0;
        virtual ~DataBasePrototype(){}
};

#endif // DATABASEPROTOTYPE_H
