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

private:
    Ui::SupplierDialog *ui;
    SupplierController& controller;

    // Явні методи-обробники подій (без автоматичного префіксу on_)
    void handleTypeChanged(int index);
    void handleAddClicked();
    void handleCloseClicked();
};