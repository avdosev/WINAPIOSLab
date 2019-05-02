#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tyristmanual.h"
#include "databasecontroller.h"
#include "tyristmanualqlistwidgetitem.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
        explicit MainWindow(QWidget *parent = nullptr);

        TyristManual getDataFromUi();
		void loadDataToUi(const TyristManual & import);

		void updateBrowserRecords();

		bool hasAcceptableInput();

        void addRecord(const TyristManual&, bool setCurrent = true);

        id_type addRecordToDatabase(const TyristManual & import);

        void addRecordToUi(id_type id, QString text, bool setCurrent = true);
        void addRecordToUi(id_type id, bool setCurrent = true);

        tyristManualQListWidgetItem* getCurrentItem();

		~MainWindow();

	private slots:

		void on_otmena_clicked();

		void on_save_clicked();

		void on_strana_currentRowChanged(int currentRow);

		void on_create_clicked();

		void on_delet_clicked();

		void on_fill_clicked();

        void on_browserRecord_currentItemChanged();

        void on_removeAllBtn_clicked();

    private:
		Ui::MainWindow *ui;
        DataBaseController records;
};

#endif // MAINWINDOW_H
