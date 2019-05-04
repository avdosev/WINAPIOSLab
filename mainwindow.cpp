#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mestootduxavalidator.h"

#include <tyristmanual.h>

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
    ui->type_otdux->addItems(TyristManual::getListRestTypes());
    ui->strana->addItems(TyristManual::getListCountry());

    // делаем все кнопки активными
    loadDataToUi(TyristManual());
    ui->browserRecord->setSortingEnabled(true);
    // если внутри что то есть то загружаем
    QVector <TyristManual> temp_vector = records.records();
    QVectorIterator <TyristManual> it(temp_vector);
    while (it.hasNext()) {
        auto item = it.next();
        auto id = item.id;
        addRecordToUi(id);
    }
    connect(&records, &DataBaseController::update_signal, this, &MainWindow::updateRecordByID);
    connect(&records, &DataBaseController::append_signal, this, &MainWindow::addRecordToUi);
    connect(&records, &DataBaseController::remove_signal, this, &MainWindow::removeRecordFromUiByID);
    connect(&records, &DataBaseController::clear_signal , this, &MainWindow::clearBrowser);
    //updateBrowserRecords();
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
    //ui->browserRecord->sortItems();
}

bool MainWindow::hasAcceptableInput() {
    if(!(ui->mestoOtduxaStr->hasAcceptableInput())) {
        QMessageBox::warning(this,"Ошибка", "проверь правильно ли ты ввел данные в поле для ввода");
        return false;
    }
    return true;
}

void MainWindow::addRecordToDatabase(const TyristManual & import) {
    records.append(import);
}

void MainWindow::addRecordToUi(id_type id) {
    tyristManualQListWidgetItem* temp = new tyristManualQListWidgetItem(id, &records);
    ui->browserRecord->addItem(temp);
    ui->browserRecord->setCurrentItem(temp);
    browserWidgetItems.insert(id, temp);
}

void MainWindow::updateRecordByID(id_type id) {
    removeRecordFromUiByID(id);
    addRecordToUi(id);
}

void MainWindow::removeRecordFromUiByID(id_type id) {
    if (browserWidgetItems.contains(id)) {
        // я не ебу почему, но так не вылетает
        // должно быть наоборот
        browserWidgetItems.remove(id);
        delete browserWidgetItems[id];
    }
}

void MainWindow::clearBrowser() {
    browserWidgetItems.clear();
    ui->browserRecord->clear();
}

void MainWindow::on_save_clicked()
{
    if (hasAcceptableInput()) {
        auto currentItem = getCurrentItem();
        if (currentItem != nullptr) {
            id_type id = currentItem->get_id();
            auto temp = getDataFromUi();
            records.update(id, temp);
        }
        else {
            addRecordToDatabase(getDataFromUi());
        }
    }
}

void MainWindow::on_create_clicked()
{
    addRecordToDatabase(TyristManual());
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
        addRecordToDatabase(TyristManual::createRandomObject());
    }
    //updateBrowserRecords();
}

void MainWindow::on_browserRecord_currentItemChanged()
{
    auto currentItem = getCurrentItem();
    if (currentItem != nullptr) {
        //обновляем уи так сказатъ
        id_type idCurrentRecord = currentItem->get_id();
        loadDataToUi(records.record(idCurrentRecord));
    } else {
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
}
