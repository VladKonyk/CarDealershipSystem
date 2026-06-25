#pragma once
#include "Vehicle.h"
#include "ElectricCar.h"
#include "CombustionCar.h"
#include "HybridCar.h"
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>

using namespace std;

class InventoryManager {
private:
    vector<shared_ptr<Vehicle>> inventory;
    string databaseFile = "inventory.txt";

public:
    const vector<shared_ptr<Vehicle>>& getInventory() const { return inventory; }

    void addVehicle(shared_ptr<Vehicle> v) {
        inventory.push_back(v);
        cout << "Автомобіль успішно додано до системи.\n";
    }

    void displayAllVehicles() const {
        if (inventory.empty()) {
            cout << "Склад порожній.\n";
            return;
        }
        for (const auto& v : inventory) {
            v->printDetails();
        }
    }

    void updateVehiclePrice(int id, double newPrice) {
        for (auto& v : inventory) {
            if (v->getId() == id) {
                v->setPrice(newPrice);
                cout << "Ціну автомобіля з ID " << id << " успішно оновлено до $" << newPrice << ".\n";
                return;
            }
        }
        cout << "[Помилка] Автомобіль з ID " << id << " не знайдено.\n";
    }

    void removeVehicle(int id) {
        auto it = remove_if(inventory.begin(), inventory.end(), [id](const shared_ptr<Vehicle>& v) {
            return v->getId() == id;
        });
        if (it != inventory.end()) {
            inventory.erase(it, inventory.end());
            cout << "Автомобіль з ID " << id << " успішно видалено зі складу.\n";
        } else {
            cout << "[Помилка] Автомобіль з ID " << id << " не знайдено.\n";
        }
    }

    void searchByPriceRange(double minPrice, double maxPrice) const {
        bool found = false;
        cout << "\n--- Результати пошуку в діапазоні $" << minPrice << " - $" << maxPrice << " ---\n";
        for (const auto& v : inventory) {
            if (v->getPrice() >= minPrice && v->getPrice() <= maxPrice) {
                v->printDetails();
                found = true;
            }
        }
        if (!found) cout << "Не знайдено автомобілів у цьому ціновому діапазоні.\n";
    }

    shared_ptr<Vehicle> findVehicleById(int id) const {
        for (const auto& v : inventory) {
            if (v->getId() == id) return v;
        }
        return nullptr;
    }

    void saveInventory() const {
        ofstream outFile(databaseFile);
        if (!outFile) {
            cerr << "Помилка відкриття файлу для запису!\n";
            return;
        }
        for (const auto& v : inventory) {
            v->saveToFile(outFile);
        }
        outFile.close();
        cout << "Дані успішно збережено.\n";
    }

    void loadInventory() {
        ifstream inFile(databaseFile);
        if (!inFile) return; 

        inventory.clear();
        string type;
        
        while (inFile >> type) {
            int id, year;
            string make, model;
            double price;

            inFile >> id >> make >> model >> year >> price;

            if (type == "Electric") {
                int battery, range;
                inFile >> battery >> range;
                inventory.push_back(make_shared<ElectricCar>(id, make, model, year, price, battery, range));
            } 
            else if (type == "Combustion") {
                double engineVol;
                string fuel;
                inFile >> engineVol >> fuel;
                inventory.push_back(make_shared<CombustionCar>(id, make, model, year, price, engineVol, fuel));
            }
            else if (type == "Hybrid") {
                double engineVol;
                int battery, range;
                inFile >> engineVol >> battery >> range;
                inventory.push_back(make_shared<HybridCar>(id, make, model, year, price, engineVol, battery, range));
            }
        }
        inFile.close();
        cout << "Дані успішно завантажено з файлу.\n";
    }
};