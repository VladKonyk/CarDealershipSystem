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

    // Налаштовуємо ліміти числових полів
    ui->spinId->setMaximum(999999);
    ui->spinYear->setRange(1900, 2030);
    ui->spinYear->setValue(2024);
    ui->spinPrice->setMaximum(10000000.00);
    ui->spinEngine->setMaximum(10.0);
    ui->spinBattery->setMaximum(200);
    ui->spinRange->setMaximum(2000);

    // Автогенерація та блокування поля ID
    int nextId = controller.generateNextId();
    ui->spinId->setValue(nextId);
    ui->spinId->setReadOnly(true);
    ui->spinId->setStyleSheet("background-color: #e0e0e0; color: #555555;");

    // НАДІЙНИЙ СПОСІБ: Ручне підключення сигналів.
    // Якщо якесь ім'я (cbType, btnAdd, btnClose) не збігається з UI-дизайнером,
    // компилятор відразу видає помилку "no member named..."
    connect(ui->cbType, &QComboBox::currentIndexChanged, this, &SupplierDialog::handleTypeChanged);
    connect(ui->btnAdd, &QPushButton::clicked, this, &SupplierDialog::handleAddClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &SupplierDialog::handleCloseClicked);

    // Одразу викликаємо налаштування полів для початкового стану (Електро)
    handleTypeChanged(ui->cbType->currentIndex());
}

SupplierDialog::~SupplierDialog()
{
    delete ui;
}

// Функція увімкнення/вимкнення полів
void SupplierDialog::handleTypeChanged(int index)
{
    bool isEV = (index == 0);
    bool isICE = (index == 1);
    bool isHybrid = (index == 2);

    ui->spinBattery->setEnabled(isEV || isHybrid);
    ui->spinRange->setEnabled(isEV || isHybrid);
    ui->spinEngine->setEnabled(isICE || isHybrid);
    ui->editFuel->setEnabled(isICE);
}

// Натискання кнопки "Додати авто" з повною валідацією
void SupplierDialog::handleAddClicked()
{
    int typeIndex = ui->cbType->currentIndex();
    int id = ui->spinId->value();
    string make = ui->editMake->text().toStdString();
    string model = ui->editModel->text().toStdString();
    int year = ui->spinYear->value();
    double price = ui->spinPrice->value();

    // 1. Базова перевірка на порожні текстові поля
    if (make.empty() || model.empty()) {
        QMessageBox::warning(this, "Помилка введення", "Марка та модель не можуть бути порожніми!");
        return;
    }

    // 2. Специфічна перевірка залежно від типу
    if (typeIndex == 0) { // Електро
        int battery = ui->spinBattery->value();
        int range = ui->spinRange->value();
        if (battery <= 0 || range <= 0) {
            QMessageBox::warning(this, "Помилка введення", "Для електромобіля обов'язково вкажіть ємність батареї та запас ходу (більше 0)!");
            return;
        }
        controller.registerNewVehicle(make_shared<ElectricCar>(id, make, model, year, price, battery, range));
    }
    else if (typeIndex == 1) { // ДВЗ
        double engine = ui->spinEngine->value();
        string fuel = ui->editFuel->text().trimmed().toStdString();
        if (engine <= 0.0 || fuel.empty()) {
            QMessageBox::warning(this, "Помилка введення", "Для авто з ДВЗ обов'язково вкажіть об'єм двигуна (більше 0) та тип палива!");
            return;
        }
        controller.registerNewVehicle(make_shared<CombustionCar>(id, make, model, year, price, engine, fuel));
    }
    else if (typeIndex == 2) { // Гібрид
        double engine = ui->spinEngine->value();
        int battery = ui->spinBattery->value();
        int range = ui->spinRange->value();
        if (engine <= 0.0 || battery <= 0 || range <= 0) {
            QMessageBox::warning(this, "Помилка введення", "Для гібрида обов'язково вкажіть об'єм двигуна, ємність батареї та запас ходу!");
            return;
        }
        controller.registerNewVehicle(make_shared<HybridCar>(id, make, model, year, price, engine, battery, range));
    }

    QMessageBox::information(this, "Успіх", "Автомобіль успішно додано на склад!");
    this->close();
}

void SupplierDialog::handleCloseClicked()
{
    this->close();
}