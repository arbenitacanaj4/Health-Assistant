#include "SymptomChecker.h"
#include <iostream>
#include <algorithm>

using namespace std;

SymptomChecker::SymptomChecker() {
    symptomMap = {
        {"headache", "Possible causes: dehydration, stress, eye strain"},
        {"fatigue", "Possible causes: lack of sleep, poor nutrition"},
        {"nausea", "Possible causes: digestive issue, stress"},
        {"cough", "Possible causes: cold, flu, irritation"},
        {"sore throat", "Possible causes: viral infection, dry air"},
        {"dizziness", "Possible causes: low blood sugar, dehydration"},
        {"stomachache", "Possible causes: indigestion, food intolerance"},
        {"back pain", "Possible causes: poor posture, muscle strain"},
        {"dry skin", "Possible causes: dehydration or cold weather"},
        {"shortness of breath", "Possible causes: overexertion, respiratory issue"},
        {"Insomnia", "Possible causes: stress, depression, noise caffeine."}
    };
}

string SymptomChecker::normalize(const string& str) const {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void SymptomChecker::checkSymptom(const string& userName) {
    string input;
    cout << "\nHi " << userName << ", enter a symptom (e.g., headache): ";
    getline(cin, input);

    string key = normalize(input);
    auto it = symptomMap.find(key);

    if (it != symptomMap.end()) {
        cout << "\n" << it->second << endl;
    } else {
        cout << "\nSorry, I don't have suggestions for that symptom.\n";
    }
}
