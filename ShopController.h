#pragma once
#include "InventoryManager.h"
#include "FinancialEngine.h"

using namespace std;

class ShopController {
private:
    InventoryManager& manager;

public:
    ShopController(InventoryManager& invManager) : manager(invManager) {}

    const vector<shared_ptr<Vehicle>>& getInventory() const { return manager.getInventory(); }

    void showCatalog() const {
        manager.displayAllVehicles();
    }

    void findCarsForClient(double min, double max) const {
        manager.searchByPriceRange(min, max);
    }

    void processSale(int id) {
        if (manager.findVehicleById(id)) {
            manager.removeVehicle(id);
            cout << "Угода успішно закрита!\n";
        } else {
            cout << "[Помилка] Автомобіль не знайдено.\n";
        }
    }

    void calculateClientLoan(int id, double downPayment, double rate, int months) {
        auto vehicle = manager.findVehicleById(id);
        if (vehicle) {
            cout << "Ціна обраного авто: $" << vehicle->getPrice() << "\n";
            FinancialEngine::calculateAmortization(vehicle->getPrice(), downPayment, rate, months);
        } else {
            cout << "[Помилка] Автомобіль з ID " << id << " не знайдено.\n";
        }
    }
};