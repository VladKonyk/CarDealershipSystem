#include "mainwindow.h"
#include "ui_mainwindow.h" // Залежно від вашої збірки може бути "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include "warehousedialog.h" // Підключаємо наше нове вікно складу
#include "supplierdialog.h"
#include "shopdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , supplierCtrl(manager)   // Ініціалізація контролерів посиланням на менеджер
    , warehouseCtrl(manager)
    , shopCtrl(manager)
{
    ui->setupUi(this);
    setWindowTitle("Головне меню автосалону");

    manager.loadInventory(); // Автоматичне завантаження з файлу при старті програми
    if (!manager.loadInventory()) {
        QMessageBox::critical(this, "Помилка", "Критична помилка: Файл бази даних не знайдено!");
        QCoreApplication::quit();
    }
}

MainWindow::~MainWindow()
{
    manager.saveInventory(); // Автоматичне збереження у файл при закритті програми
    delete ui;
}

void MainWindow::on_btnSupplier_clicked()
{
    SupplierDialog dialog(supplierCtrl, this);
    dialog.exec();
}

void MainWindow::on_btnWarehouse_clicked()
{
    // Створюємо об'єкт вікна складу, передаючи йому відповідний контролер
    WarehouseDialog dialog(warehouseCtrl, this);

    // exec() відкриває вікно як модальне (блокує головне вікно, поки склад відкритий)
    dialog.exec();
}

void MainWindow::on_btnShop_clicked()
{
    ShopDialog dialog(shopCtrl, this);
    dialog.exec();
}