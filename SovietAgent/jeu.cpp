#include "Jeu.h"
#include <iostream>
#include <random>
#include <ctime>

Jeu::Jeu() : currentDay(1), totalScore(0), resistance(0), dayScore(0), dayThreshold(6) {}

void Jeu::generateDay() {
    policy.generateRandomPolicy();
    message.generateForDay(1.0);

    permitsToday.clear();

    std::vector<std::string> names = { "Nikita", "Olga", "Vladimir", "Anya", "Dmitri", "Ivan", "Svetlana" };
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> nameDist(0, (int)names.size() - 1);
    std::uniform_int_distribution<int> motiveDist(0, 3);

    for (int i = 0; i < 4; ++i) {
        MotiveType motive = static_cast<MotiveType>(motiveDist(gen));
        Permis p(names[nameDist(gen)], motive);

        if (message.overrides(motive)) {
            p.setWestOverride(true);
        }
        permitsToday.push_back(p);
    }

    dayScore = 0;
    dayThreshold = 6 + (currentDay - 1);
}

void Jeu::applyDecision(int index, bool decision) {
    if (index < 0 || index >= (int)permitsToday.size()) return;

    Permis& p = permitsToday[index];
    p.setDecision(decision);

    bool policyAllow = policy.isAllowed(p.getMotive());
    bool westAllow = message.overrides(p.getMotive());
    int points = 0;

    if (!westAllow) {
        if (decision == policyAllow) points += 2;
    }
    else {
        if (decision == true) {
            points += 2;
            if (policyAllow == false) {
                resistance++;
                p.setProWest(true);
            }
        }
    }

    dayScore += points;
    totalScore += points;
}

// --- FIXED: runInvestigation defined here ---
bool Jeu::runInvestigation() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d20(1, 20);

    int roll = d20(gen);
    int mod = resistance / 3;
    int total = roll + mod;

    std::cout << "\n!!! INVESTIGATION ALERT !!!\n";
    std::cout << "Your day score (" << dayScore << ") is below the threshold (" << dayThreshold << ").\n";
    std::cout << "Rolling d20 (" << roll << ") + bonus (" << mod << ") = " << total << "\n";

    if (total >= 14) {
        std::cout << "You escaped suspicion for now.\n";
        return true;
    }
    else {
        std::cout << "You have been captured!\n";
        return false;
    }
}

void Jeu::nextDay() {
    currentDay++;
    generateDay();
}

void Jeu::showState() const {
    std::cout << "\n=== DAY " << currentDay << " ===\n";

    // 1. USSR official policy
    std::cout << "\nOFFICIAL POLICY TODAY\n";
    std::cout << "----------------------\n";
    policy.showDebug();

    // 2. WEST secret message (only if active)
    std::cout << "\n--- WEST MESSAGE ---\n";
    if (message.isActive()) {
        std::cout << "(Incoming secret transmission...)\n";
        message.playMorse(); // 🎧 play the Morse sound + show the morse code

        // After the Morse sound, show the decoded message
        std::cout << "\n[Decoded message from the West]\n";
        message.showDebug(); // show the textual decoded order
    }
    else {
        std::cout << "No Morse transmission today.\n";
    }

    // 3. Display today's permits
    std::cout << "\n--- PERMITS ---\n";
    for (size_t i = 0; i < permitsToday.size(); ++i) {
        const Permis& p = permitsToday[i];
        p.showDebug();
    }

    // 4. Display daily results
    std::cout << "\nCurrent day score: " << dayScore
        << " | Total score: " << totalScore
        << " | Resistance: " << resistance << "\n";
}

int Jeu::calculateDayScore() const {
    return dayScore;
}
