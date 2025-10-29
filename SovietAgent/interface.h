#pragma once
#include "Jeu.h"
#include <string>

class Interface {
private:
    Jeu& jeu;         // reference to the main game logic
    int choice;       // player’s input
    int day;          // current day number
    int actions;      // number of actions taken
    int score;        // total score

public:
    // Constructor
    Interface(Jeu& j);

    // Main game loop
    void run();

    // Display functions
    void showMenu() const;
    void showPolicy() const;
    void showPermit(const Permis& p) const;
    void showDaySummary();

    // Input validation
    bool validInput(const std::string& input) const;
};
