#include "User.h"
#include <fstream>
#include <iostream>

using namespace std;

User::User() : name("Unknown"), weight(0), height(0), age(0), gender("unknown") {}

User::User(const string& userName) : name(userName), weight(0), height(0), age(0), gender("unknown") {}

void User::setWeight(double weight) { this->weight = weight; }
void User::setHeight(double height) { this->height = height; }
void User::setAge(int age) { this->age = age; }
void User::setGender(const string& gender) { this->gender = gender; }

double User::getWeight() const { return weight; }
double User::getHeight() const { return height; }
int User::getAge() const { return age; }
string User::getGender() const { return gender; }

void User::setName(const string& userName) { name = userName; }
string User::getName() const { return name; }

bool User::loadProfile() {
    ifstream inFile(name + "_profile.txt");
    if (!inFile) {
        cout << "No existing profile found for " << name << ". Starting fresh.\n";
        
        // Create a new profile if none exists
        saveProfile();  // Save the current profile data
        return false;   // Return false since it's a new profile
    }
    
    // Load existing profile data
    getline(inFile, name);
    inFile >> weight >> height >> age >> gender;
    inFile.close();
    return true;
}


bool User::saveProfile() const {
    try {
        ofstream outFile(name + "_profile.txt");
        if (!outFile) {
            throw runtime_error("Error saving profile file for " + name);  // Throw exception if file doesn't open
        }

        outFile << name << endl;
        outFile << weight << " " << height << " " << age << " " << gender << endl;
        outFile.close();
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;  // Print error message
        return false;
    }
    return true;
}

double User::calculateCalories() const {
    double bmr = 0;

    if (gender == "male") {
        bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
    } else if (gender == "female") {
        bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
    }

    return bmr;  // Return Basic Metabolic Rate (BMR)
}
