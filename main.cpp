#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "HRSR04/HRSR04.h"
#include "LM35/LM35.h"

// Clear screen based on OS
#ifdef _WIN32
#define CLEAR std::system("cls")
#else
#define CLEAR std::system("clear")
#endif

// Number of each sensor
#define SENSOR_COUNT 4

// Sensor thresholds
#define TEMP_HIGH 24    
#define TEMP_LOW 18     
#define DIST_HIGH 5.0   
#define DIST_LOW 0.2   

// Test Values
const double TEST_TEMPS[SENSOR_COUNT] = {20.0, 40.0, 50.0, 70.0};
const double TEST_DISTS[SENSOR_COUNT] = {10.0, 100.0, 200.0, 300.0};

// Print sensor values
void printSensors(LM35 temp[], HRSR04 dist[]);
// Print light, vent and heater status
void printOutputs(LM35 temp[], HRSR04 dist[], bool testMode = false);

// Simulation modes
void simulateNormal();
void simulateTest();

// Check if temperature equal in all zones
void checkTempEqual(LM35 temp[]);

int main(){
    srand(time(0)); // Set random seed for sensor value generation
    
    int choice;

    do {
        // Menu
        std::cout << "\nSelect simulation mode:\n";
        std::cout << "\t1. Normal Simulation\n";
        std::cout << "\t2. Test Simulation\n";
        std::cout << "\t3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1: simulateNormal(); break;
            case 2: simulateTest(); break;
            case 3: break;
            default: std::cout << "Invalid choice.\n";
        }

        // Wait for user input before clearing screen
        std::cin.ignore();
        std::cout << "\nPress Enter to continue ...";
        std::cin.get();
        CLEAR;
    } while (choice != 3);

    return 0;
}

// Display temperature and distance readings
void printSensors(LM35 temp[], HRSR04 dist[]){
    std::cout << "\n|    Zone    | Temperature |  Distance  |\n";
    std::cout << "-----------------------------------------\n";

    for (int i = 0; i < SENSOR_COUNT; i++){
        std::cout << std::fixed << "|     " << i + 1 << "      |    ";
        std::cout << std::setprecision(2) << temp[i].getTemp() << "    |    ";
        std::cout << std::setprecision(2) << dist[i].getDist() << "    |\n";
    }
}

// Determine outputs for each zone
void printOutputs(LM35 temp[], HRSR04 dist[], bool testMode){
    double tempVal, distVal;

    // Check sensor readings against thresholds
    for (int i = 0; i < SENSOR_COUNT; i++){
        tempVal = temp[i].getTemp();
        distVal = dist[i].getDist();

        std::cout << "Zone " << i + 1 << ": ";

        // Temperature control: vent if too hot, heater if too cold
        if (tempVal > TEMP_HIGH) std::cout << "Vent open. ";
        else if (tempVal < TEMP_LOW) std::cout << "Heater on. ";
        else std::cout << "Temp in Range. ";

        // Light control: off lights if distance out of range
        if (distVal > DIST_HIGH || distVal < DIST_LOW) std::cout << (testMode ? "Zone Inactive. " : "Lights off. ");
        else std::cout << (testMode ? "Zone Active. " : "Lights on. ");

        std::cout << "\n";
    }
}

// Normal mode - generates random sensor values and displays results
void simulateNormal(){
    LM35 tempSensors[SENSOR_COUNT];      // Temperature sensor array
    HRSR04 distSensors[SENSOR_COUNT];    // Distance sensor array

    // Generate random values for sensors
    for (int i = 0; i < SENSOR_COUNT; i++){
        tempSensors[i].genRandTemp();
        distSensors[i].genRandDist();
    }

    // Display sensor readings and outputs
    printSensors(tempSensors, distSensors);
    printOutputs(tempSensors, distSensors);
    checkTempEqual(tempSensors);
}

// Test mode - uses fixed sensor values
void simulateTest(){
    LM35 tempSensors[SENSOR_COUNT] = {LM35(TEST_TEMPS[0]), LM35(TEST_TEMPS[1]), LM35(TEST_TEMPS[2]), LM35(TEST_TEMPS[3])};      // Temperature sensor array
    HRSR04 distSensors[SENSOR_COUNT] = {HRSR04(TEST_DISTS[0]), HRSR04(TEST_DISTS[1]), HRSR04(TEST_DISTS[2]), HRSR04(TEST_DISTS[3])};    // Distance sensor array

    // Display sensor readings and outputs
    printSensors(tempSensors, distSensors);
    printOutputs(tempSensors, distSensors, true);
    checkTempEqual(tempSensors);
}

// Check if all temperature readings are equal
void checkTempEqual(LM35 temp[]){
    double firstTemp = temp[0].getTemp();
    bool equal = true;

    for (int i = 1; i < SENSOR_COUNT; i++){
        if (temp[i].getTemp() != firstTemp){
            equal = false;
            break;
        }
    }

    std::cout << (equal ? "\nAll temperature readings are equal.\n" : "\nTemperature readings are not equal.\n");
}