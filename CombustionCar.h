#pragma once
#include "Vehicle.h"

using namespace std;

class CombustionCar : public Vehicle {
private:
    double engineVolumeLiters;
    string fuelType; 

public:
    CombustionCar(int id, string make, string model, int year, double price, double engineVol, string fuel)
        : Vehicle(id, make, model, year, price), engineVolumeLiters(engineVol), fuelType(fuel) {}

    string getVehicleType() const override { return "Combustion"; }

    void printDetails() const override {
        cout << "[ДВЗ]     ID: " << id << " | " << make << " " << model << " (" << year << ") | "
             << "Ціна: $" << price << " | Двигун: " << engineVolumeLiters << " л (" << fuelType << ")\n";
    }

    void saveToFile(ofstream& out) const override {
        out << "Combustion " << id << " " << make << " " << model << " " 
            << year << " " << price << " " << engineVolumeLiters << " " << fuelType << "\n";
    }
};