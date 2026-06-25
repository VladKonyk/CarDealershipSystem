#pragma once
#include <QDialog>
#include "SupplierController.h"

namespace Ui {
class SupplierDialog;
}

class SupplierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierDialog(SupplierController& ctrl, QWidget *parent = nullptr);
    ~SupplierDialog();

private slots:
    void on_btnAdd_clicked();
    void on_btnClose_clicked();

private:
    Ui::SupplierDialog *ui;
    SupplierController& controller;
};