#pragma once
#include <vector>
#include "Permis.h"
#include "PolitiqueDuJour.h"
#include "MessageOuest.h"

class Jeu {
private:
    int currentDay;
    int totalScore;
    int resistance;
    int dayScore;
    int dayThreshold;

    std::vector<Permis> permitsToday;
    PolitiqueDuJour policy;
    MessageOuest message;

public:
    Jeu();

    void generateDay();
    void applyDecision(int index, bool decision);
    bool runInvestigation();
    void nextDay();

    int calculateDayScore() const;
    int getTotalScore() const { return totalScore; }
    int getDayScore() const { return dayScore; }
    int getResistance() const { return resistance; }
    int getDayThreshold() const { return dayThreshold; }
    int getCurrentDay() const { return currentDay; }

    const std::vector<Permis>& getPermits() const { return permitsToday; }
    const PolitiqueDuJour& getPolicy() const { return policy; }
    const MessageOuest& getMessage() const { return message; }

    void showState() const;
};
