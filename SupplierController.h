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

    // Отримання списку (якщо його ще немає)
    const std::vector<std::shared_ptr<Vehicle>>& getInventory() const {
        return manager.getInventory();
    }

    // Метод для автогенерації наступного ID
    int generateNextId() const {
        const auto& list = manager.getInventory();
        int maxId = 0;
        for (const auto& vehicle : list) {
            if (vehicle->getId() > maxId) {
                maxId = vehicle->getId();
            }
        }
        return maxId + 1; // Повертаємо найбільший існуючий ID + 1
    }
};