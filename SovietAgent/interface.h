#pragma once
#include "Jeu.h"
#include <string>

class Interface {
private:
    Jeu& jeu;
    int choix;
    int jour;
    int actions;
    int score;

    // Internal helpers
    void showMenu() const;
    void showPolicy() const;
    void showPermit(const Permis& p) const;
    bool validInput(const std::string& input) const;
    void showDaySummary();

public:
    Interface(Jeu& j);
    void run();
};
