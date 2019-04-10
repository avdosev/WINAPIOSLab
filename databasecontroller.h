#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <databaseprototype.h>
#include <memory>

class DataBaseController : public DataBasePrototype
{
    private:
        std::shared_ptr<DataBasePrototype> prototype_ptr;
    public:
        DataBaseController(DataBasePrototype* prototype = nullptr);
        ~DataBaseController();
        int count() const;
        id_type append(TyristManual record);
        void remove(id_type id);
        void update(id_type record_id, TyristManual record);
        TyristManual record(id_type id) const;
        QVector<TyristManual> records();
        bool save(QString filename);
        bool load(QString filename);
        void clear();
        bool isModidfied() const;
};

#endif // DATABASECONTROLLER_H
