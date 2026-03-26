#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HRSR04/HRSR04.h"
#include "LM35/LM35.h"

void simulateNormal();
void simulateTest();

int main(){
    int choice;

    do {
        // Menu for selecting simulation mode
        std::cout << "\nSelect simulation mode:\n";
        std::cout << "\t1. Normal Simulation\n";
        std::cout << "\t2. Test Simulation\n";
        std::cout << "\t3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: simulateNormal(); break;
            case 2: simulateTest(); break;
            case 3: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}

void simulateNormal(){

}

void simulateTest(){

}