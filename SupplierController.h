#pragma once
#include "InventoryManager.h"
#include <memory>

using namespace std;

class SupplierController {
private:
    InventoryManager& manager;

public:
    SupplierController(InventoryManager& invManager) : manager(invManager) {}

    void registerNewVehicle(shared_ptr<Vehicle> newVehicle) {
        manager.addVehicle(newVehicle);
    }
};