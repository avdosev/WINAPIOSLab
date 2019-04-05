#include "tyristmanual.h"

#include <QTime>

QStringList tyristManual::listRestTypes;
QStringList tyristManual::listCountry;

tyristManual::tyristManual()
{
    restType = 0;
    country = 0;
    cost = 3000;
    duration = 2;
    visa = false;
	id = 0;
}

tyristManual::tyristManual(const tyristManual& c)
{
	restType = c.restType;
    country = c.country;
    restPlace = c.restPlace;
    cost = c.cost;
    duration = c.duration;
	visa =c.visa;
	id = c.id;
}


tyristManual::~tyristManual()
{

}

tyristManual& tyristManual::operator = (const tyristManual& c) {
    restType = c.restType;
    country = c.country;
    restPlace = c.restPlace;
    cost = c.cost;
    duration = c.duration;
	visa =c.visa;
	id = c.id;
	return *this;
}

int tyristManual::compare(const tyristManual & comp1, const tyristManual & comp2) {
	//происходит сравнение по следующим полям: вид отдыха, страна, стоимость путевки
	if (comp1.restType != comp2.restType) return comp1.restType-comp2.restType;
	if (comp1.country != comp2.country) return comp1.country-comp2.country;
	if (comp1.cost != comp2.cost) return comp1.cost - comp2.cost;
	return 0;
}

const QStringList& tyristManual::getListRestTypes() {
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

const QStringList& tyristManual::getListCountry() {
	if (listCountry.size() == 0) {
		listCountry
		<< "Россия"
		<< "Абхазия"
		<< "Турция"
		<< "Египет";
	}
	return listCountry;
}

tyristManual tyristManual::createRandomObject() {
	tyristManual temp;
	QStringList spisok;
	spisok << "Гонконг" << "Лондон" << "Москва" << "Париж" << "Киев" << "Волгоград" << "Рим"<< "Прага" << "Стамбул" << "Мадрид" << "Харьков" << "Львов" << "Одесса" << "Луганск"
    << "Берлин" << "Простогород" << "Кельн" << "Ростов" << "Каир" << "Александрия" << "Кена" << "Чтототам";
	static bool r = true;
	if (r) { qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); r = false; }

	temp.set_restType(qrand()%tyristManual::getListRestTypes().size());
	temp.set_visa(qrand()%2);
	temp.set_country(qrand()%tyristManual::getListCountry().size());
	temp.set_restPlace(spisok.at(qrand()%spisok.size()));
	temp.set_cost(qrand()%96000 + 3000);
	temp.set_duration(qrand()%28 + 2);

	return temp;
}

tyristManual::operator QString() const {
    return tyristManual::getListRestTypes().at(restType) + "  |  " + restPlace + "  |  " + QString::number(cost);
}

QString tyristManual::toQString() const {
    return tyristManual::getListRestTypes().at(restType) + "  |  " + restPlace + "  |  " + QString::number(cost);
}

bool operator > (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) > 0;
}
bool operator >= (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) >= 0;
}
bool operator < (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) < 0;
}
bool operator <= (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) <= 0;
}
bool operator == (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) == 0;
}
bool operator != (const tyristManual& c1, const tyristManual& c2) {
	return tyristManual::compare(c1, c2) != 0;
}

int tyristManual::get_restType() const {
    return restType;
}
int tyristManual::get_country() const {
    return country;
}
QString tyristManual::get_restPlace() const {
    return restPlace;
}
int tyristManual::get_cost() const {
    return cost;
}
int tyristManual::get_duration() const {
    return duration;
}
int tyristManual::get_visa() const {
	return visa;
}

void tyristManual::set_restType(int t) {
    restType = t;
}
void tyristManual::set_country(int t) {
	if (t==0) visa = false;
    country = t;
}
void tyristManual::set_restPlace(QString t) {
    restPlace = t;
}
void tyristManual::set_cost(int t) {
    cost = t;
}
void tyristManual::set_duration(int t) {
    duration = t;
}
void tyristManual::set_visa(bool t) {
	visa = t;
}
