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
        ~MainWindow();

        TyristManual getDataFromUi();
		void loadDataToUi(const TyristManual & import);
        tyristManualQListWidgetItem* getCurrentItem();

		void updateBrowserRecords();

		bool hasAcceptableInput();

        void addRecordToDatabase(const TyristManual & import);

    public slots:
        void addRecordToUi(id_type id);
        void updateRecordByID(id_type id);
        void removeRecordFromUiByID(id_type);
        void clearBrowser();


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
        QMap <id_type, tyristManualQListWidgetItem*> browserWidgetItems;
};

#endif // MAINWINDOW_H
