#ifndef TYRISTMANUALDATABASE_H
#define TYRISTMANUALDATABASE_H

#include <QMap>
#include <QVector>

#include "tyristmanual.h"

class DataBase
{
	private:
        QMap <id_type, TyristManual> data;
		bool moding;
	public:
        DataBase();
        ~DataBase();
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
		bool isUniqueId(id_type id) const;
        id_type getUniqueId() const;

};

#endif // TYRISTMANUALDATABASE_H
