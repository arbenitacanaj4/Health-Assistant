#include "HealthLogger.h"
#include <iostream>
#include <fstream>

using namespace std;

HealthLogger::HealthLogger() : sleepHours(0), waterLiters(0), steps(0) {}

void HealthLogger::logHealthData(const string& userName) {
    try {
        cout << "\nEnter hours of sleep: ";
        cin >> sleepHours;
        if (sleepHours < 0) throw runtime_error("Sleep hours cannot be negative.");

        cout << "Enter water intake (liters): ";
        cin >> waterLiters;
        if (waterLiters < 0) throw runtime_error("Water intake cannot be negative.");

        cout << "Enter number of steps walked: ";
        cin >> steps;
        if (steps < 0) throw runtime_error("Steps cannot be negative.");

        cin.ignore(); // Clear buffer after numeric input

        // Feedback
        cout << "\n=== Health Feedback ===\n";
        if (sleepHours < 7)
            cout << "- Try to get at least 7 to 9 hours of sleep.\n";
        else
            cout << "- Great sleep!\n";

        if (waterLiters < 2)
            cout << "- Aim for at least 2L of water per day.\n";
        else
            cout << "- Nice hydration!\n";

        if (steps < 6000)
            cout << "- Try to reach at least 6000 steps.\n";
        else
            cout << "- Good activity level!\n";

        saveData(userName);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Handle invalid inputs (e.g., negative values)
    }
}

void HealthLogger::saveData(const string& userName) const {
    try {
        ofstream outFile(userName + "_health.txt");
        if (!outFile) {
            throw runtime_error("Error opening the file to save health data: " + userName + "_health.txt");
        }

        outFile << sleepHours << " " << waterLiters << " " << steps << "\n";
        outFile.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Handle file saving errors
    }
}

void HealthLogger::loadData(const string& userName) {
    try {
        ifstream inFile(userName + "_health.txt");
        if (!inFile) {
            throw runtime_error("Error opening file: " + userName + "_health.txt");
        }

        inFile >> sleepHours >> waterLiters >> steps;
        inFile.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Handle file reading errors
    }
}

double HealthLogger::getSleepHours() const {
    return sleepHours;
}

double HealthLogger::getWaterLiters() const {
    return waterLiters;
}

int HealthLogger::getSteps() const {
    return steps;
}
