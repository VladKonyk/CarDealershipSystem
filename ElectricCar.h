#pragma once
#include "Vehicle.h"

using namespace std;

class ElectricCar : public Vehicle {
private:
    int batteryCapacityKWh;
    int rangeKm;

public:
    ElectricCar(int id, string make, string model, int year, double price, int battery, int range)
        : Vehicle(id, make, model, year, price), batteryCapacityKWh(battery), rangeKm(range) {}

    string getVehicleType() const override { return "Electric"; }

    void printDetails() const override {
        cout << "[Електро] ID: " << id << " | " << make << " " << model << " (" << year << ") | "
             << "Ціна: $" << price << " | Батарея: " << batteryCapacityKWh << " кВт-год | Запас: " << rangeKm << " км\n";
    }

    void saveToFile(ofstream& out) const override {
        out << "Electric " << id << " " << make << " " << model << " " 
            << year << " " << price << " " << batteryCapacityKWh << " " << rangeKm << "\n";
    }
};