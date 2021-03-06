#ifndef TYRISTMANUALQLISTWIDGETITEM_H
#define TYRISTMANUALQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <databasecontroller.h>

class tyristManualQListWidgetItem : public QListWidgetItem//хоп а кто ето тут наследуется
{
		unsigned int id;
        DataBaseController* d;
	public:
        tyristManualQListWidgetItem(id_type _id, DataBaseController* _d) {
            id = _id;
            d = _d;
            update_text();
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
