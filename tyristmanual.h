#ifndef TYRISTMANUAL_H
#define TYRISTMANUAL_H

#include <QString>
#include <QStringList>

using id_type = unsigned int;

class tyristManual {
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
		tyristManual();
		tyristManual(const tyristManual& c);
		~tyristManual();

        int get_restType() const ;
        int get_country() const ;
        QString get_restPlace() const ;
        int get_cost() const ;
        int get_duration() const ;
		int get_visa() const ;

		static int compare(const tyristManual & comp1, const tyristManual & comp2);
		static tyristManual createRandomObject();
		static const QStringList& getListRestTypes();
		static const QStringList& getListCountry();

		tyristManual& operator = (const tyristManual& c);

		operator QString() const;
		QString toQString() const;

        void set_restType(int t);
        void set_country(int t);
        void set_restPlace(QString t);
        void set_cost(int t);
        void set_duration(int t);
		void set_visa(bool t);
};

bool operator >  (const tyristManual& c1, const tyristManual& c2);
bool operator >= (const tyristManual& c1, const tyristManual& c2);
bool operator <  (const tyristManual& c1, const tyristManual& c2);
bool operator <= (const tyristManual& c1, const tyristManual& c2);
bool operator == (const tyristManual& c1, const tyristManual& c2);
bool operator != (const tyristManual& c1, const tyristManual& c2);
#endif // TYRISTMANUAL_H
