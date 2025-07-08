#include <iostream>
#include <string>
#include <limits>
#include "User.h"
#include "MealLogger.h"
#include "SymptomChecker.h"
#include "HealthLogger.h"

using namespace std;

// Function Prototypes
void logMeal(const string& userName);
void logSymptom(const string& userName);

void logHealthData(const string& userName);
void showHealthBar(const User& user);  // Pass User object instead of string

// Intro Screen
void showIntro() {
    cout << R"(============================================
      Welcome to Health CV , Your Life Ally
============================================

This isn't just tracking. It's your health, simplified.
With this assistant, you can:
 - Log meals and see what fuels your day
 - Track sleep, hydration, and movement
 - Get clear feedback and health insights
 - Check symptoms and get smarter about your body

>> Hit ENTER to begin your health journey.)";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// logMeal Implementation 
void logMeal(const string& userName) {
    MealLogger* logger = new MealLogger();
    logger->loadMeals(userName);
    logger->logMeal(userName);
    delete logger;
}

// logSymptom Implementation 
void logSymptom(const string& userName) {
    SymptomChecker* checker = new SymptomChecker();
    checker->checkSymptom(userName);
    delete checker;
}

// logHealthData Implementation 
void logHealthData(const string& userName) {
    HealthLogger* logger = new HealthLogger();
    logger->loadData(userName);
    logger->logHealthData(userName);
    delete logger;
}

// showHealthBar Implementation 
void showHealthBar(const User& user) {  // Pass User object as reference
    // Create HealthLogger object and load the data
    HealthLogger* logger = new HealthLogger();
    logger->loadData(user.getName());  // Load today's health data

    // Get data
    double sleep = logger->getSleepHours();
    double water = logger->getWaterLiters();
    int steps = logger->getSteps();

    // Get calories consumed today (from MealLogger)
    MealLogger* mealLogger = new MealLogger();
    mealLogger->loadMeals(user.getName());
    int caloriesConsumed = mealLogger->getTotalCalories();
    delete mealLogger;

    // Calculate health bar score (out of 100)
    int score = 40;  // Base score is always 40%

    // Sleep (20% for 7+ hours)
    if (sleep >= 7) score += 20;

    // Water (20% for 2+ liters)
    if (water >= 2) score += 20;

    // Steps (20% for 6000+ steps)
    if (steps >= 6000) score += 20;

    // Calories (20% for staying within ideal caloric range)
    int idealCalories = user.calculateCalories();  // Use user data for ideal calories
    if (caloriesConsumed >= idealCalories - 200 && caloriesConsumed <= idealCalories + 200) {
        score += 20;
    }

    // Display health bar percentage
    cout << "Health Bar: " << score << "%\n";

    // Provide feedback based on score
    if (score < 50)
        cout << "You're running low. Time to recharge!\n";
    else if (score < 80)
        cout << "Not bad! Keep it up.\n";
    else
        cout << "You're doing great! \n";

    // Clean up
    delete logger;
}

// Function to validate the user's name
bool isValidName(const string& name) {
    // Check if each character is either alphabetic or a space
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;  // Invalid character found
        }
    }
    return true;  // All characters are valid
}

// Function to validate positive numeric input
template <typename T>
bool isValidPositiveInput(T& value) {
    if (value <= 0) {
        return false;  // Invalid input if it's negative or zero
    }
    return true;  // Valid positive input
}

// ====== Main Function ======
int main() {
    showIntro();

    User user;
    string userName;
    bool validName = false;

    // Input validation for the user's name
    while (!validName) {
        cout << "\nPlease enter your name: ";
        getline(cin, userName);

        // Check if the name is valid (only alphabetic characters and spaces)
        if (isValidName(userName)) {
            validName = true;  // Name is valid
        } else {
            cout << "Invalid name. Please enter a valid name using alphabetic characters only.\n";
        }
    }

    user.setName(userName);

    double weight, height;
    int age;
    string gender;

    // Input validation for weight
    bool validWeight = false;
    while (!validWeight) {
        cout << "Enter your weight (kg): ";
        cin >> weight;

        if (!isValidPositiveInput(weight)) {
            cout << "Invalid weight. Please enter a positive value for weight.\n";
        } else {
            validWeight = true;
            user.setWeight(weight);
        }
    }

    // Input validation for height
    bool validHeight = false;
    while (!validHeight) {
        cout << "Enter your height (cm): ";
        cin >> height;

        if (!isValidPositiveInput(height)) {
            cout << "Invalid height. Please enter a positive value for height.\n";
        } else {
            validHeight = true;
            user.setHeight(height);
        }
    }

    // Input validation for age
    bool validAge = false;
    while (!validAge) {
        cout << "Enter your age (years): ";
        cin >> age;

        if (!isValidPositiveInput(age)) {
            cout << "Invalid age. Please enter a positive value for age.\n";
        } else {
            validAge = true;
            user.setAge(age);
        }
    }

    // Input validation for gender
    cout << "Enter your gender (male/female): ";
    cin >> gender;
    user.setGender(gender);

    user.loadProfile();

    int choice;
    do {
        cout << "\n===== Main Menu =====\n";
        cout << "1. Log a Meal\n";
        cout << "2. Log a Symptom\n";
        cout << "3. Log Sleep/Water/Steps\n";
        cout << "4. View Health Bar\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                logMeal(user.getName());
                break;
            case 2:
                logSymptom(user.getName());
                break;
            case 3:
                logHealthData(user.getName());
                break;
            case 4:
                showHealthBar(user);  // Pass the entire User object
                break;
            case 5:
                cout << ">> Exiting. Stay healthy, " << user.getName() << "!\n";
                user.saveProfile();
                break;
            default:
                cout << ">> Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
