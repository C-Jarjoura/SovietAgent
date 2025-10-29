#pragma once
#include <map>
#include "Motive.h"

class PolitiqueDuJour {
private:
    std::map<MotiveType, bool> allowed;

public:
    PolitiqueDuJour();
    void generateRandomPolicy();
    bool isAllowed(MotiveType m) const;
    void showDebug() const;
};
