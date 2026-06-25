#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

class FinancialEngine {
public:
    static void calculateAmortization(double carPrice, double downPayment, double annualRate, int months) {
        double principal = carPrice - downPayment;
        if (principal <= 0) {
            cout << "\n[Помилка] Авансовий внесок покриває вартість авто. Кредит не потрібен.\n";
            return;
        }

        double monthlyRate = (annualRate / 100.0) / 12.0;
        double monthlyPayment = (principal * monthlyRate * pow(1 + monthlyRate, months)) / (pow(1 + monthlyRate, months) - 1);

        cout << "\n======================================================\n";
        cout << "                 ГРАФІК АМОРТИЗАЦІЇ                   \n";
        cout << "======================================================\n";
        cout << "Вартість авто: $" << fixed << setprecision(2) << carPrice << "\n";
        cout << "Аванс: $" << downPayment << "\n";
        cout << "Сума кредиту: $" << principal << "\n";
        cout << "Відсоткова ставка: " << annualRate << "%\n";
        cout << "Термін: " << months << " міс.\n";
        cout << "Щомісячний платіж: $" << monthlyPayment << "\n";
        cout << "------------------------------------------------------\n";
        cout << left << setw(8) << "Місяць" << setw(15) << "Платіж ($)" << setw(15) << "Відсотки ($)" << setw(15) << "Тіло ($)" << "Залишок ($)\n";
        cout << "------------------------------------------------------\n";

        ofstream reportFile("financial_report.txt");
        if (reportFile.is_open()) {
            reportFile << "ГРАФІК АМОРТИЗАЦІЇ КРЕДИТУ\n";
            reportFile << "Сума кредиту: $" << fixed << setprecision(2) << principal << "\n";
            reportFile << "Щомісячний платіж: $" << monthlyPayment << "\n";
            reportFile << "------------------------------------------------------\n";
            reportFile << left << setw(8) << "Місяць" << setw(15) << "Платіж" << setw(15) << "Відсотки" << setw(15) << "Тіло" << "Залишок\n";
            reportFile << "------------------------------------------------------\n";
        }

        double balance = principal;
        for (int i = 1; i <= months; i++) {
            double interestPayment = balance * monthlyRate;
            double principalPayment = monthlyPayment - interestPayment;
            balance -= principalPayment;
            if (balance < 0) balance = 0; 

            cout << left << setw(8) << i << setw(15) << monthlyPayment << setw(15) << interestPayment << setw(15) << principalPayment << balance << "\n";
            if (reportFile.is_open()) {
                reportFile << left << setw(8) << i << setw(15) << monthlyPayment << setw(15) << interestPayment << setw(15) << principalPayment << balance << "\n";
            }
        }
        if (reportFile.is_open()) {
            reportFile.close();
            cout << "------------------------------------------------------\n";
            cout << "Детальний звіт збережено у файл 'financial_report.txt'.\n";
        }
    }
};