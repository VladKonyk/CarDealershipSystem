#pragma once
#include <QDialog>
#include "ShopController.h"

namespace Ui {
class ShopDialog;
}

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(ShopController& ctrl, QWidget *parent = nullptr);
    ~ShopDialog();

private slots:
    void on_btnFilter_clicked();
    void on_btnReset_clicked();
    void on_btnCalculate_clicked();
    void on_btnSell_clicked();
    void on_btnClose_clicked();

private:
    Ui::ShopDialog *ui;
    ShopController& controller;

    // Функція має параметри за замовчуванням для фільтрації
    void loadTableData(double minPrice = 0.0, double maxPrice = 99999999.0);
};