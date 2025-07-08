#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;
    double weight; // kg
    double height; // cm
    int age;       // years
    std::string gender; // "male" or "female"

public:
    User();  // Default constructor
    User(const std::string& userName);

    // Setters for the new data fields
    void setWeight(double weight);
    void setHeight(double height);
    void setAge(int age);
    void setGender(const std::string& gender);

    // Getters for the new data fields
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    std::string getGender() const;

    void setName(const std::string& userName);
    std::string getName() const;

    bool loadProfile();   // Loads user data from file
    bool saveProfile() const; // Saves user data to file
    
    double calculateCalories() const;
};

#endif // USER_H
