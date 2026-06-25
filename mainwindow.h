#pragma once
#include <QMainWindow>
#include "InventoryManager.h"
#include "SupplierController.h"
#include "WarehouseController.h"
#include "ShopController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSupplier_clicked();
    void on_btnWarehouse_clicked();
    void on_btnShop_clicked();

private:
    Ui::MainWindow *ui;

    InventoryManager manager; // База даних додатка

    // Оголошуємо контролери як поля класу головного вікна
    SupplierController supplierCtrl;
    WarehouseController warehouseCtrl;
    ShopController shopCtrl;
};