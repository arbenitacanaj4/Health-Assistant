#ifndef SYMPTOMCHECKER_H
#define SYMPTOMCHECKER_H

#include <string>
#include <map>

class SymptomChecker {
private:
    std::map<std::string, std::string> symptomMap;

    std::string normalize(const std::string& str) const;

public:
    SymptomChecker();

    void checkSymptom(const std::string& userName);
};

#endif
