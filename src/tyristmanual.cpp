#include "tyristmanual.h"

#include <QTime>

QStringList TyristManual::listRestTypes;
QStringList TyristManual::listCountry;

TyristManual::TyristManual()
{
    restType = 0;
    country = 0;
    cost = 3000;
    duration = 2;
    visa = false;
	id = 0;
}

TyristManual::TyristManual(const TyristManual& c)
{
	restType = c.restType;
    country = c.country;
    restPlace = c.restPlace;
    cost = c.cost;
    duration = c.duration;
	visa =c.visa;
	id = c.id;
}


TyristManual::~TyristManual()
{

}

TyristManual& TyristManual::operator = (const TyristManual& c) {
    restType = c.restType;
    country = c.country;
    restPlace = c.restPlace;
    cost = c.cost;
    duration = c.duration;
	visa =c.visa;
	id = c.id;
	return *this;
}

int TyristManual::compare(const TyristManual & comp1, const TyristManual & comp2) {
	//происходит сравнение по следующим полям: вид отдыха, страна, стоимость путевки
	if (comp1.restType != comp2.restType) return comp1.restType-comp2.restType;
	if (comp1.country != comp2.country) return comp1.country-comp2.country;
	if (comp1.cost != comp2.cost) return comp1.cost - comp2.cost;
	return 0;
}

const QStringList& TyristManual::getListRestTypes() {
	if (listRestTypes.size() == 0) {
		listRestTypes
		<< "пляжный"
		<< "экскурсионный"
		<< "экзотический"
		<< "круиз"
		<< "VIP"
		<< "лечебный"
		<< "экстремальный"
		<< "горнолыжный";
	}
	return listRestTypes;
}

const QStringList& TyristManual::getListCountry() {
	if (listCountry.size() == 0) {
		listCountry
		<< "Россия"
		<< "Абхазия"
		<< "Турция"
		<< "Египет";
	}
	return listCountry;
}

TyristManual TyristManual::createRandomObject() {
	TyristManual temp;
	QStringList spisok;
	spisok << "Гонконг" << "Лондон" << "Москва" << "Париж" << "Киев" << "Волгоград" << "Рим"<< "Прага" << "Стамбул" << "Мадрид" << "Харьков" << "Львов" << "Одесса" << "Луганск"
    << "Берлин" << "Простогород" << "Кельн" << "Ростов" << "Каир" << "Александрия" << "Кена" << "Чтототам";
	static bool r = true;
	if (r) { qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); r = false; }

	temp.set_restType(qrand()%TyristManual::getListRestTypes().size());
	temp.set_visa(qrand()%2);
	temp.set_country(qrand()%TyristManual::getListCountry().size());
	temp.set_restPlace(spisok.at(qrand()%spisok.size()));
	temp.set_cost(qrand()%96000 + 3000);
	temp.set_duration(qrand()%28 + 2);

	return temp;
}

TyristManual::operator QString() const {
    return TyristManual::getListRestTypes().at(restType) + "  |  " + restPlace + "  |  " + QString::number(cost);
}

QString TyristManual::toQString() const {
    return TyristManual::getListRestTypes().at(restType) + "  |  " + restPlace + "  |  " + QString::number(cost);
}

DataStream& operator << (DataStream& stream, TyristManual tmp) {
    stream << tmp.get_restType();
    stream << tmp.get_country();
    stream << tmp.get_restPlace();
    stream << tmp.get_cost();
    stream << tmp.get_duration();
    stream << tmp.get_visa();
    stream << tmp.id;
    return stream;
}
DataStream& operator >> (DataStream& stream, TyristManual& tmp_tyrist) {
    QString tmp_str;
    int tmp_int;
    stream >> tmp_int;
    tmp_tyrist.set_restType(tmp_int);
    stream >> tmp_int;
    tmp_tyrist.set_country(tmp_int);
    stream >> tmp_str;
    tmp_tyrist.set_restPlace(tmp_str);
    stream >> tmp_int;
    tmp_tyrist.set_cost(tmp_int);
    stream >> tmp_int;
    tmp_tyrist.set_duration(tmp_int);
    stream >> tmp_int;
    tmp_tyrist.set_visa(tmp_int);
    stream >> tmp_tyrist.id;
    return stream;
}

bool operator > (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) > 0;
}
bool operator >= (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) >= 0;
}
bool operator < (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) < 0;
}
bool operator <= (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) <= 0;
}
bool operator == (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) == 0;
}
bool operator != (const TyristManual& c1, const TyristManual& c2) {
	return TyristManual::compare(c1, c2) != 0;
}

int TyristManual::get_restType() const {
    return restType;
}
int TyristManual::get_country() const {
    return country;
}
QString TyristManual::get_restPlace() const {
    return restPlace;
}
int TyristManual::get_cost() const {
    return cost;
}
int TyristManual::get_duration() const {
    return duration;
}
int TyristManual::get_visa() const {
	return visa;
}

void TyristManual::set_restType(int t) {
    restType = t;
}
void TyristManual::set_country(int t) {
	if (t==0) visa = false;
    country = t;
}
void TyristManual::set_restPlace(QString t) {
    restPlace = t;
}
void TyristManual::set_cost(int t) {
    cost = t;
}
void TyristManual::set_duration(int t) {
    duration = t;
}
void TyristManual::set_visa(bool t) {
	visa = t;
}
