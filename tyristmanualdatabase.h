#ifndef TYRISTMANUALDATABASE_H
#define TYRISTMANUALDATABASE_H

#include "tyristmanual.h"
#include <QMap>
#include <QVector>


class tyristManualDataBase
{
	private:
		QMap <id_type, tyristManual> data;
		bool moding;
	public:
		tyristManualDataBase();
		int count() const;
        id_type append(tyristManual record);
		void remove(id_type id);
        void update(id_type record_id, tyristManual record);
        tyristManual record(id_type id) const;
        QVector<tyristManual> records();
        bool save(QString filename);
		bool load(QString filename);
		void clear();
        bool isModidfied() const;
		bool isUniqueId(id_type id) const;
        id_type getUniqueId() const;

};

#endif // TYRISTMANUALDATABASE_H
