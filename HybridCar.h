#pragma once
#include "Vehicle.h"

using namespace std;

class HybridCar : public Vehicle {
private:
    double engineVolumeLiters;
    int batteryCapacityKWh;
    int electricRangeKm;

public:
    HybridCar(int id, string make, string model, int year, double price, double engineVol, int battery, int range)
        : Vehicle(id, make, model, year, price), engineVolumeLiters(engineVol), batteryCapacityKWh(battery), electricRangeKm(range) {}

    string getVehicleType() const override { return "Hybrid"; }

    void printDetails() const override {
        cout << "[Гібрид]  ID: " << id << " | " << make << " " << model << " (" << year << ") | "
             << "Ціна: $" << price << " | Двигун: " << engineVolumeLiters 
             << " л | Батарея: " << batteryCapacityKWh << " кВт-год | Запас (електро): " << electricRangeKm << " км\n";
    }

    void saveToFile(ofstream& out) const override {
        out << "Hybrid " << id << " " << make << " " << model << " " 
            << year << " " << price << " " << engineVolumeLiters << " " 
            << batteryCapacityKWh << " " << electricRangeKm << "\n";
    }
};