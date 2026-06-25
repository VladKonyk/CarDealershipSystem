#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Vehicle {
protected:
    int id;
    string make;
    string model;
    int year;
    double price;

public:
    Vehicle(int id, string make, string model, int year, double price)
        : id(id), make(make), model(model), year(year), price(price) {}

    virtual ~Vehicle() = default;

    int getId() const { return id; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    double getPrice() const { return price; }
    int getYear() const { return year; }

    void setPrice(double newPrice) { price = newPrice; }

    virtual string getVehicleType() const = 0; 
    virtual void printDetails() const = 0; 
    virtual void saveToFile(ofstream& out) const = 0;
};