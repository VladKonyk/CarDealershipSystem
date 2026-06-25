#pragma once
#include <QDialog>
#include "WarehouseController.h"

namespace Ui {
class WarehouseDialog;
}

class WarehouseDialog : public QDialog
{
    Q_OBJECT

public:
    // Конструктор тепер приймає посилання на контролер
    explicit WarehouseDialog(WarehouseController& ctrl, QWidget *parent = nullptr);
    ~WarehouseDialog();

private slots:
    void on_pushButton_clicked();   // Кнопка "Оновити"
    void on_pushButton_2_clicked(); // Кнопка "Закрити"
    void on_btnChangePrice_clicked();
    void on_btnDelete_clicked();

private:
    Ui::WarehouseDialog *ui;
    WarehouseController& controller; // Зберігаємо посилання на контролер
    void loadTableData(); // Наша функція для заповнення таблиці
};