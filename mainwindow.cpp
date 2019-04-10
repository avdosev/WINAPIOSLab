#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mestootduxavalidator.h"
#include "QDebug"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

MainWindow::MainWindow(DataBaseController controller, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    records = controller;// это важно

	setWindowTitle(tr("Туристический справочник"));
    ui->mestoOtduxaStr->setValidator(new mestoOtduxaValidator(this));
    ui->type_otdux->addItems(TyristManual::getListRestTypes());
    ui->strana->addItems(TyristManual::getListCountry());

	//делаем все кнопки активными
	loadDataToUi(TyristManual());

    //если внутри что то есть то загружаем
    QVector <TyristManual> temp_vector = records.records();
    QVectorIterator <TyristManual> it(temp_vector);
    while (it.hasNext()) {
        id_type id = it.next().id;
        addRecordToUi(id, false);
    }
    updateBrowserRecords();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadDataToUi(const TyristManual & import) {
	ui->Visa_mastercard->setChecked(import.get_visa());
    ui->day->setValue(import.get_duration());
    ui->pay->setValue(import.get_cost());
    ui->mestoOtduxaStr->setText(import.get_restPlace());
    ui->strana->setCurrentRow(import.get_country());
    ui->type_otdux->setCurrentRow(import.get_restType());
}

TyristManual MainWindow::getDataFromUi() {
	TyristManual temp;

    temp.set_cost(ui->pay->value());
    temp.set_duration(ui->day->value());
    temp.set_visa(ui->Visa_mastercard->isChecked());
    temp.set_restPlace(ui->mestoOtduxaStr->text());
    temp.set_restType(ui->type_otdux->currentRow());
    temp.set_country(ui->strana->currentRow());

	return temp;
}

void MainWindow::updateBrowserRecords() {
	ui->browserRecord->sortItems();
}

bool MainWindow::hasAcceptableInput() {
	if(!(ui->mestoOtduxaStr->hasAcceptableInput())) {
        QMessageBox::warning(this,"Ошибка", "проверь правильно ли ты ввел данные в поле для ввода");
		return false;
	}
	return true;
}

//добавляекм запись и базу данных и в ui
void MainWindow::addRecord(const TyristManual& value, bool setCurrent) {
    auto id = addRecordToDatabase(value);
    addRecordToUi(id, setCurrent);
}

id_type MainWindow::addRecordToDatabase(const TyristManual & import) {
	id_type t = records.append(import);
    return t;
}

void MainWindow::addRecordToUi(id_type id, bool setCurrent) {
	tyristManualQListWidgetItem* temp = new tyristManualQListWidgetItem(id, &records);
	ui->browserRecord->addItem(temp);
    if (setCurrent) ui->browserRecord->setCurrentItem(temp);
}

void MainWindow::on_save_clicked()
{
	if (hasAcceptableInput()) {
        auto currentItem = getCurrentItem();
        if (currentItem != nullptr) {
            id_type id = currentItem->get_id();
            auto temp = getDataFromUi();
            records.update(id, temp);
			currentItem->update_text();
			updateBrowserRecords();
		}
		else {
            addRecord(getDataFromUi());
		}
	}
}

void MainWindow::on_create_clicked()
{
	//if (hasAcceptableInput()) {
    addRecord(TyristManual());
	updateBrowserRecords();
	//}
}

void MainWindow::on_delet_clicked()
{
    auto rec = getCurrentItem();
    if (rec != nullptr) {
		records.remove(rec->get_id());
		delete rec;
	}
}

void MainWindow::on_otmena_clicked()
{
	//тут все понятно я думаю
    auto currentItem = getCurrentItem();
    if (currentItem != nullptr)
		loadDataToUi(records.record(currentItem->get_id()));
	else
		loadDataToUi(TyristManual());
}

void MainWindow::on_strana_currentRowChanged(int currentRow)
{
    bool new_state;
    new_state = currentRow != 0;
    ui->Visa_mastercard->setEnabled(new_state);
}

void MainWindow::on_fill_clicked()
{
    for (int i = 0; i < 15; i++) {
        addRecord(TyristManual::createRandomObject(), false);
	}
	updateBrowserRecords();
}

void MainWindow::on_browserRecord_currentItemChanged()
{
    auto currentItem = getCurrentItem();
    if (currentItem != nullptr) {
		//обновляем уи так сказатъ
        id_type idCurrentRecord = currentItem->get_id();
		loadDataToUi(records.record(idCurrentRecord));
	}
	else {
		loadDataToUi(TyristManual());
	}
}

tyristManualQListWidgetItem* MainWindow::getCurrentItem() {
    // ну шо кастуем
    // к концу лабы буду чувствовать себя магом

    // я был молод и глуп
    // настоящая магия это вин апи
    return static_cast<tyristManualQListWidgetItem*>(ui->browserRecord->currentItem());
}



void MainWindow::on_removeAllBtn_clicked() {
    records.clear();
    ui->browserRecord->clear();
}
