#include <iostream>
#include "../include/scenarios.h"

using namespace std;

int main() {
    int choice = 0;

    while (true) {
        cout << "\n=========================================\n";
        cout << "  BIBLIOTEKA PRZETWARZANIA SYGNALOW\n";
        cout << "=========================================\n";
        cout << "Wybierz laboratorium do uruchomienia:\n";
        cout << "1. Uruchom Lab 1 (Generacja sygnalow podstawowych)\n";
        cout << "2. Uruchom Lab 2 (Dyskretna Transformata Fouriera - DFT)\n";
        cout << "3. Uruchom Lab 3 (Szeregi Fouriera i wlasnosci FFT)\n";
        cout << "4. Uruchom Lab 4 (Modulacje analogowe - parametry)\n";
        cout << "5. Uruchom Lab 5 (Modulacje analogowe (AM, PM, FM) i badanie pasma)\n";
        cout << "6. Uruchom Lab 6 (Modulacje cyfrowe na strumieniu binarnym)\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            run_lab01();
            break;
        case 2:
            run_lab02();
            break;
        case 3:
            run_lab03();
            break;
        case 4:
            run_lab04();
            break;
        case 5:
            run_lab05();
            break;
        case 6:
            run_lab06();
            break;
        case 0:
            cout << "Zamykanie programu...\n";
            return 0;
        default:
            cout << "Niepoprawny wybor! Sprobuj ponownie.\n";
        }
    }
    return 0;
}