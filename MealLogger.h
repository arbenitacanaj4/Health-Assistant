#ifndef MEALLOGGER_H
#define MEALLOGGER_H

#include <string>
#include <vector>

struct FoodItem {
    std::string name;
    int calories;
};

class MealLogger {
private:
    std::vector<FoodItem> foodDatabase;
    std::vector<FoodItem> mealsToday;

    std::string normalize(const std::string& str) const;

public:
    MealLogger();

    void logMeal(const std::string& userName);
    void showDailyTotal() const;

    void loadMeals(const std::string& userName);
    void saveMeals(const std::string& userName) const;

    // Added function to get total calories consumed today
    int getTotalCalories() const;  
};

#endif
