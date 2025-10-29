#pragma once
#include <set>
#include "Motive.h"

class MessageOuest {
private:
    std::set<MotiveType> forcedAllow;
    bool active;

public:
    MessageOuest();

    void generateForDay(double probability);
    bool overrides(MotiveType m) const;
    bool isActive() const { return active; }

    // Unified display method (replaces getMorse & getInstructions)
    void showDebug() const;
};
