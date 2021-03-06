#ifndef TYRISTMANUALDATABASE_H
#define TYRISTMANUALDATABASE_H

#include <QMap>

#include "databaseprototype.h"
#include "services/thread/timer.h"

class DataBase : public DataBasePrototype
{
	private:
        QMap <id_type, TyristManual> data;
		bool moding;
        bool isUniqueId(id_type id) const;
        id_type getUniqueId() const;
        Timer autoSaveTimer;
	public:
        DataBase();
        ~DataBase();
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

#endif // TYRISTMANUALDATABASE_H
