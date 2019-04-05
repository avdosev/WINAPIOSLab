//"чувак это лаба по оп сделаная за пару часов за день-несколько до сдачи, успокойся"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mestootduxavalidator.h"
#include "QDebug"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setWindowTitle(tr("Туристический справочник"));
    ui->mestoOtduxaStr->setValidator(new mestoOtduxaValidator(this));
    ui->type_otdux->addItems(tyristManual::getListRestTypes());
    ui->strana->addItems(tyristManual::getListCountry());

	//делаем все кнопки активными
	loadDataToUi(tyristManual());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadDataToUi(const tyristManual & import) {
	ui->Visa_mastercard->setChecked(import.get_visa());
    ui->day->setValue(import.get_duration());
    ui->pay->setValue(import.get_cost());
    ui->mestoOtduxaStr->setText(import.get_restPlace());
    ui->strana->setCurrentRow(import.get_country());
    ui->type_otdux->setCurrentRow(import.get_restType());
}

tyristManual MainWindow::getDataFromUi() {
	tyristManual temp;

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
void MainWindow::addRecord(const tyristManual& value) {
    auto id = addRecordToDatabase(value);
    addRecordToUi(id);
}

id_type MainWindow::addRecordToDatabase(const tyristManual & import) {
	id_type t = records.append(import);
    return t;
}

void MainWindow::addRecordToUi(id_type id) {
	tyristManualQListWidgetItem* temp = new tyristManualQListWidgetItem(id, &records);
	ui->browserRecord->addItem(temp);
	ui->browserRecord->setCurrentItem(temp);
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
    addRecord(tyristManual());
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
		loadDataToUi(tyristManual());
}

void MainWindow::on_strana_currentRowChanged(int currentRow)
{
    bool new_state;
    new_state = currentRow != 0;
    ui->Visa_mastercard->setEnabled(new_state);
}

void MainWindow::on_fill_clicked()
{
	for (int i = 0; i < 10; i++) {
        addRecord(tyristManual::createRandomObject());
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
		loadDataToUi(tyristManual());
	}
}

tyristManualQListWidgetItem* MainWindow::getCurrentItem() {
    //ну шо кастуем
    //к концу лабы буду чувствовать себя магом
    return static_cast<tyristManualQListWidgetItem*>(ui->browserRecord->currentItem());
}


