#include "supplierdialog.h"
#include "ui_supplierdialog.h"
#include <QMessageBox>
#include "ElectricCar.h"
#include "CombustionCar.h"
#include "HybridCar.h"

using namespace std;

SupplierDialog::SupplierDialog(SupplierController& ctrl, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SupplierDialog)
    , controller(ctrl)
{
    ui->setupUi(this);
    setWindowTitle("Реєстрація нової партії");

    // Налаштовуємо максимальні значення для числових полів, щоб вони вміщували реальні дані
    ui->spinId->setMaximum(999999);
    ui->spinYear->setRange(1900, 2030);
    ui->spinYear->setValue(2024);
    ui->spinPrice->setMaximum(10000000.00);
    ui->spinEngine->setMaximum(10.0);
    ui->spinBattery->setMaximum(200);
    ui->spinRange->setMaximum(2000);
}

SupplierDialog::~SupplierDialog()
{
    delete ui;
}

void SupplierDialog::on_btnAdd_clicked()
{
    // Зчитуємо базові дані
    int typeIndex = ui->cbType->currentIndex(); // 0 - Електро, 1 - ДВЗ, 2 - Гібрид
    int id = ui->spinId->value();
    string make = ui->editMake->text().toStdString();
    string model = ui->editModel->text().toStdString();
    int year = ui->spinYear->value();
    double price = ui->spinPrice->value();

    // Базова перевірка, чи не порожні текстові поля
    if (make.empty() || model.empty()) {
        QMessageBox::warning(this, "Помилка", "Марка та модель не можуть бути порожніми!");
        return;
    }

    // Зчитуємо специфічні дані та створюємо об'єкти поліморфно
    if (typeIndex == 0) { // Електро
        int battery = ui->spinBattery->value();
        int range = ui->spinRange->value();
        controller.registerNewVehicle(make_shared<ElectricCar>(id, make, model, year, price, battery, range));
    }
    else if (typeIndex == 1) { // ДВЗ
        double engine = ui->spinEngine->value();
        string fuel = ui->editFuel->text().toStdString();
        controller.registerNewVehicle(make_shared<CombustionCar>(id, make, model, year, price, engine, fuel));
    }
    else if (typeIndex == 2) { // Гібрид
        double engine = ui->spinEngine->value();
        int battery = ui->spinBattery->value();
        int range = ui->spinRange->value();
        controller.registerNewVehicle(make_shared<HybridCar>(id, make, model, year, price, engine, battery, range));
    }

    QMessageBox::information(this, "Успіх", "Автомобіль успішно додано на склад!");
    this->close(); // Закриваємо вікно після успішного додавання
}

void SupplierDialog::on_btnClose_clicked()
{
    this->close();
}