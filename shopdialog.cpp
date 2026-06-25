#include "shopdialog.h"
#include "ui_shopdialog.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <cmath> // Для локального прорахунку формули

using namespace std;

ShopDialog::ShopDialog(ShopController& ctrl, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShopDialog)
    , controller(ctrl)
{
    ui->setupUi(this);
    setWindowTitle("Панель Представника Магазину (Продажі та Фінанси)");

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Тип" << "Марка" << "Модель" << "Рік" << "Ціна ($)");
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Налаштування полів за замовчуванням
    ui->spinMaxPrice->setValue(100000.0);
    ui->spinRate->setValue(5.0);
    ui->spinMonths->setValue(36);

    loadTableData();
}

ShopDialog::~ShopDialog()
{
    delete ui;
}

// Завантаження таблиці з урахуванням діапазону цін
void ShopDialog::loadTableData(double minPrice, double maxPrice)
{
    ui->tableWidget->setRowCount(0);
    const auto& list = controller.getInventory();

    int row = 0;
    for (const auto& vehicle : list) {
        if (vehicle->getPrice() >= minPrice && vehicle->getPrice() <= maxPrice) {
            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(vehicle->getId())));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(vehicle->getVehicleType())));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vehicle->getMake())));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(vehicle->getModel())));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(vehicle->getYear())));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(vehicle->getPrice(), 'f', 2)));
            row++;
        }
    }
}

void ShopDialog::on_btnFilter_clicked()
{
    loadTableData(ui->spinMinPrice->value(), ui->spinMaxPrice->value());
}

void ShopDialog::on_btnReset_clicked()
{
    ui->spinMinPrice->setValue(0);
    ui->spinMaxPrice->setValue(100000.0);
    loadTableData(); // Скидання фільтра (від 0 до нескінченності)
}

void ShopDialog::on_btnCalculate_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Помилка", "Виберіть автомобіль з каталогу для розрахунку кредиту!");
        return;
    }

    int id = ui->tableWidget->item(currentRow, 0)->text().toInt();
    double price = ui->tableWidget->item(currentRow, 5)->text().toDouble();

    double downPayment = ui->spinDownPayment->value();
    double rate = ui->spinRate->value();
    int months = ui->spinMonths->value();

    if (downPayment >= price) {
        QMessageBox::information(this, "Інформація", "Аванс повністю покриває або перевищує вартість авто. Кредит не потрібен.");
        return;
    }

    // Викликаємо наш бекенд-двигун (він згенерує детальний financial_report.txt)
    controller.calculateClientLoan(id, downPayment, rate, months);

    // Локально рахуємо щомісячний платіж для виведення на екран у графічному вікні
    double principal = price - downPayment;
    double monthlyRate = (rate / 100.0) / 12.0;
    double monthlyPayment = (principal * monthlyRate * pow(1 + monthlyRate, months)) / (pow(1 + monthlyRate, months) - 1);

    QString msg = QString("Вартість авто: $%1\nАванс: $%2\nСума кредиту: $%3\n\nЩомісячний платіж: $%4\n\nДетальний графік амортизації збережено у файл 'financial_report.txt'.")
                      .arg(price, 0, 'f', 2)
                      .arg(downPayment, 0, 'f', 2)
                      .arg(principal, 0, 'f', 2)
                      .arg(monthlyPayment, 0, 'f', 2);

    QMessageBox::information(this, "Фінансовий розрахунок", msg);
}

void ShopDialog::on_btnSell_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Помилка", "Виберіть автомобіль для продажу!");
        return;
    }

    int id = ui->tableWidget->item(currentRow, 0)->text().toInt();
    QString make = ui->tableWidget->item(currentRow, 2)->text();
    QString model = ui->tableWidget->item(currentRow, 3)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження продажу",
                                  "Оформити продаж " + make + " " + model + "?\nАвтомобіль буде списано зі складу.",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        controller.processSale(id);
        QMessageBox::information(this, "Продаж успішний", "Угоду закрито! Автомобіль передано клієнту.");
        loadTableData(); // Оновлюємо таблицю
    }
}

void ShopDialog::on_btnClose_clicked()
{
    this->close();
}