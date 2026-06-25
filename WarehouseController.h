#pragma once
#include "InventoryManager.h"

using namespace std;

class WarehouseController {
private:
    InventoryManager& manager;

public:
    WarehouseController(InventoryManager& invManager) : manager(invManager) {}

    const vector<shared_ptr<Vehicle>>& getInventory() const { return manager.getInventory(); }

    void showInventory() const {
        manager.displayAllVehicles();
    }

    void markDownPrice(int id, double newPrice) {
        manager.updateVehiclePrice(id, newPrice);
    }

    void writeOffVehicle(int id) {
        manager.removeVehicle(id);
    }
};