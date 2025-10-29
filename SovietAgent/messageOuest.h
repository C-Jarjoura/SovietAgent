#pragma once
#include <set>
#include <string>
#include "Motive.h"

class MessageOuest {
private:
    std::set<MotiveType> forcedAllow;
    bool active;

    // morseCode = le signal en morse (.- .. etc)
    std::string morseCode;

    // plainText = traduction humaine de l'ordre
    std::string plainText;

public:
    MessageOuest();

    // probability = chance per day to receive message (1.0 = always)
    void generateForDay(double probability);

    // does WEST force this motive to be allowed?
    bool overrides(MotiveType m) const;

    bool isActive() const { return active; }

    // Play actual morse with Beep()
    void playMorse() const;

    // Display the secret order as text for the player
    void showDebug() const;
};
