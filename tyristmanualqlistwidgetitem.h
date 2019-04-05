#ifndef TYRISTMANUALQLISTWIDGETITEM_H
#define TYRISTMANUALQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <tyristmanualdatabase.h>

class tyristManualQListWidgetItem : public QListWidgetItem//хоп а кто ето тут наследуется
{
		unsigned int id;
		tyristManualDataBase* d;
	public:
        tyristManualQListWidgetItem(unsigned int _id, tyristManualDataBase* _d) {
            id = _id;
            d = _d;
            update_text();
        }

		id_type get_id() {
			return id;
		}

		tyristManual get_record() {
			return d->record(id);
		}

		void update_text() {
			setText(d->record(id).toQString());
		}

        bool operator < (const QListWidgetItem &other) const {
            const tyristManualQListWidgetItem& tmp = static_cast<const tyristManualQListWidgetItem&>(other);
            return this->d->record(id) < tmp.d->record(tmp.id);
        }
};

#endif // TYRISTMANUALQLISTWIDGETITEM_H
