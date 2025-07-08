#ifndef HEALTHLOGGER_H
#define HEALTHLOGGER_H

#include <string>

class HealthLogger {
private:
    double sleepHours;  // Hours of sleep
    double waterLiters; // Liters of water consumed
    int steps;          // Number of steps walked

public:
    HealthLogger();

    // Log health data: sleep, water, and steps
    void logHealthData(const std::string& userName);

    // Load health data from the user's file
    void loadData(const std::string& userName);

    // Save today's health data to a file
    void saveData(const std::string& userName) const;

    // Getters for health data
    double getSleepHours() const;
    double getWaterLiters() const;
    int getSteps() const;
};

#endif
