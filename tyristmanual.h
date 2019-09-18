#ifndef TYRISTMANUAL_H
#define TYRISTMANUAL_H

#include <QString>
#include <QStringList>

using id_type = unsigned int;

class TyristManual {
	private:
		static QStringList listRestTypes;
		static QStringList listCountry;
        int restType;
        int country;
        QString restPlace;
        int cost;
        int duration;
        bool visa;

	public:
		id_type id;
		TyristManual();
		TyristManual(const TyristManual& c);
		~TyristManual();

        int get_restType() const ;
        int get_country() const ;
        QString get_restPlace() const ;
        int get_cost() const ;
        int get_duration() const ;
		int get_visa() const ;

		static int compare(const TyristManual & comp1, const TyristManual & comp2);
		static TyristManual createRandomObject();
		static const QStringList& getListRestTypes();
		static const QStringList& getListCountry();

		TyristManual& operator = (const TyristManual& c);

		operator QString() const;
		QString toQString() const;

        void set_restType(int t);
        void set_country(int t);
        void set_restPlace(QString t);
        void set_cost(int t);
        void set_duration(int t);
		void set_visa(bool t);
};

bool operator >  (const TyristManual& c1, const TyristManual& c2);
bool operator >= (const TyristManual& c1, const TyristManual& c2);
bool operator <  (const TyristManual& c1, const TyristManual& c2);
bool operator <= (const TyristManual& c1, const TyristManual& c2);
bool operator == (const TyristManual& c1, const TyristManual& c2);
bool operator != (const TyristManual& c1, const TyristManual& c2);

#include <stream/datastream.h>

DataStream& operator << (DataStream&, TyristManual);
DataStream& operator >> (DataStream&, TyristManual&);

#endif // TYRISTMANUAL_H
