#include "MealLogger.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

MealLogger::MealLogger() {
    try {
        ifstream file("food_db.txt");
        if (!file) {
            throw runtime_error("Food database file 'food_db.txt' is missing or cannot be opened.");
        }

        string name;
        int cal;

        while (file >> name >> cal) {
            foodDatabase.push_back({name, cal});
        }

        if (foodDatabase.empty()) {
            cerr << "⚠️ Warning: food_db.txt is empty.\n";
        }

        file.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Display error message if file can't be opened
    }
}

string MealLogger::normalize(const string& str) const {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void MealLogger::logMeal(const string& userName) {
    try {
        string input;
        cout << "\nEnter food name (type 'done' to finish): ";

        while (getline(cin, input)) {
            if (normalize(input) == "done") break;

            bool found = false;
            for (const auto& food : foodDatabase) {
                if (normalize(input) == normalize(food.name)) {
                    mealsToday.push_back(food);
                    cout << food.name << " added (" << food.calories << " cal)\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw runtime_error("Food not found in database: " + input);  // Throw exception if food not found
            } else {
                cout << "Enter next food (or 'done'): ";
            }
        }

        saveMeals(userName);
        showDailyTotal();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Display error message
    }
}

void MealLogger::showDailyTotal() const {
    int total = 0;
    cout << "\nToday's meals:\n";
    for (const auto& food : mealsToday) {
        cout << " - " << food.name << ": " << food.calories << " cal\n";
        total += food.calories;
    }
    cout << "Total calories: " << total << " cal\n";
}

void MealLogger::saveMeals(const string& userName) const {
    try {
        ofstream outFile(userName + "_meals.txt");
        if (!outFile) {
            throw runtime_error("Error opening the file to save meals: " + userName + "_meals.txt");
        }

        for (const auto& food : mealsToday) {
            outFile << food.name << " " << food.calories << "\n";
        }
        outFile.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Handle file saving errors
    }
}

void MealLogger::loadMeals(const string& userName) {
    mealsToday.clear();
    try {
        ifstream inFile(userName + "_meals.txt");
        if (!inFile) {
            throw runtime_error("Error opening file: " + userName + "_meals.txt");
        }

        string name;
        int cal;
        while (inFile >> name >> cal) {
            mealsToday.push_back({name, cal});
        }
        inFile.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Handle file reading errors
    }
}

// New function to calculate the total calories for the day
int MealLogger::getTotalCalories() const {
    int totalCalories = 0;
    for (const auto& food : mealsToday) {
        totalCalories += food.calories;  // Sum up the calories of all meals logged today
    }
    return totalCalories;  // Return the total
}
