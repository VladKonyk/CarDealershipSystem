#include "warehousedialog.h"
#include "ui_warehousedialog.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QMessageBox>

using namespace std;

WarehouseDialog::WarehouseDialog(WarehouseController& ctrl, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WarehouseDialog)
    , controller(ctrl)
{
    ui->setupUi(this);
    setWindowTitle("Панель Працівника Складу");

    // Налаштовуємо 6 колонок таблиці
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Тип" << "Марка" << "Модель" << "Рік" << "Ціна ($)");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Автоматично завантажуємо дані при відкритті вікна
    loadTableData();
}

WarehouseDialog::~WarehouseDialog()
{
    delete ui;
}

void WarehouseDialog::loadTableData()
{
    // Очищаємо старі дані перед оновленням
    ui->tableWidget->setRowCount(0);

    // Отримуємо доступ до вектора через контролер
    const auto& list = controller.getInventory();

    // Встановлюємо кількість рядків у таблиці відповідно до кількості авто на складі
    ui->tableWidget->setRowCount(list.size());

    int row = 0;
    for (const auto& vehicle : list) {
        // Перетворюємо дані зі стандартних типів C++ (string, int, double) у типи Qt (QString)
        QString idStr = QString::number(vehicle->getId());
        QString typeStr = QString::fromStdString(vehicle->getVehicleType());
        QString makeStr = QString::fromStdString(vehicle->getMake());
        QString modelStr = QString::fromStdString(vehicle->getModel());
        QString yearStr = QString::number(vehicle->getYear());
        QString priceStr = QString::number(vehicle->getPrice(), 'f', 2); // 'f', 2 — два знаки після коми

        // Заповнюємо кожну клітинку рядка об'єктами QTableWidgetItem
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(idStr));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(typeStr));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(makeStr));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(modelStr));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(yearStr));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(priceStr));

        row++;
    }
}

void WarehouseDialog::on_pushButton_clicked()
{
    loadTableData(); // Слот кнопки "Оновити список"
}

void WarehouseDialog::on_pushButton_2_clicked()
{
    this->close(); // Слот кнопки "Закрити"
}

void WarehouseDialog::on_btnChangePrice_clicked()
{
    // Отримуємо індекс виділеного рядка (-1, якщо нічого не виділено)
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Помилка", "Будь ласка, виберіть автомобіль у таблиці!");
        return;
    }

    // Отримуємо ID автомобіля з першої колонки (індекс 0) виділеного рядка
    int vehicleId = ui->tableWidget->item(currentRow, 0)->text().toInt();

    // Отримуємо поточну ціну для відображення у вікні вводу
    double currentPrice = ui->tableWidget->item(currentRow, 5)->text().toDouble();

    // Викликаємо вікно вводу нової ціни
    bool ok;
    double newPrice = QInputDialog::getDouble(this, "Зміна ціни",
                                              "Введіть нову ціну для авто ID " + QString::number(vehicleId) + ":",
                                              currentPrice, 0, 1000000, 2, &ok);

    // Якщо користувач натиснув "ОК" і ввів дані
    if (ok) {
        controller.markDownPrice(vehicleId, newPrice);
        loadTableData(); // Оновлюємо таблицю, щоб побачити зміни
        QMessageBox::information(this, "Успіх", "Ціну успішно оновлено!");
    }
}

void WarehouseDialog::on_btnDelete_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Помилка", "Будь ласка, виберіть автомобіль для списання!");
        return;
    }

    int vehicleId = ui->tableWidget->item(currentRow, 0)->text().toInt();
    QString make = ui->tableWidget->item(currentRow, 2)->text();
    QString model = ui->tableWidget->item(currentRow, 3)->text();

    // Запитуємо підтвердження перед безповоротним видаленням
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження",
                                  "Ви впевнені, що хочете списати " + make + " " + model + " (ID: " + QString::number(vehicleId) + ")?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        controller.writeOffVehicle(vehicleId);
        loadTableData(); // Оновлюємо таблицю (рядок зникне)
    }
}