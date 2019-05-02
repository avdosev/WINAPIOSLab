#ifndef TYRISTMANUALQLISTWIDGETITEM_H
#define TYRISTMANUALQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <databaseprototype.h>

class tyristManualQListWidgetItem : public QListWidgetItem//хоп а кто ето тут наследуется
{
		unsigned int id;
        DataBasePrototype* d;
	public:
        tyristManualQListWidgetItem(id_type _id, DataBasePrototype* _d) {
            id = _id;
            d = _d;
            update_text();
        }

        tyristManualQListWidgetItem(id_type _id, DataBasePrototype* _d, QString _text) {
            id = _id;
            d = _d;
            this->setText(_text);
        }

		id_type get_id() {
			return id;
		}

		TyristManual get_record() {
			return d->record(id);
		}

		void update_text() {
			setText(d->record(id).toQString());
		}

        bool operator < (const QListWidgetItem &other) const {
            const tyristManualQListWidgetItem& tmp = static_cast<const tyristManualQListWidgetItem&>(other);
            return d->compareRecordsByID(this->id, tmp.id) <= -1;
        }
};

#endif // TYRISTMANUALQLISTWIDGETITEM_H
