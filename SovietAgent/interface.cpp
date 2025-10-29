#include "Interface.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>

// === ANSI Color Codes ===
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";

using namespace std;

Interface::Interface(Jeu& j)
    : jeu(j), choice(-1), day(1), actions(0), score(0) {
    srand(static_cast<unsigned>(time(0)));
}

// === Display menu ===
void Interface::showMenu() const {
    cout << "=========================\n";
    cout << "        MAIN MENU\n";
    cout << "=========================\n";
    cout << "1. Approve Permit\n";
    cout << "2. Deny Permit\n";
    cout << "0. Quit\n";
    cout << "=========================\n";
    cout << "Your choice: ";
}

// === Display the policy of the day ===
void Interface::showPolicy() const {
    cout << CYAN << "Today's official policy:" << RESET << endl;
    jeu.getPolicy().showDebug();  // ✅ fixed: no afficherDebug
    cout << endl;

    if (jeu.getMessage().isActive()) {
        cout << YELLOW << "Morse message received!" << RESET << endl;
        jeu.getMessage().showDebug();  // ✅ fixed: no getMorse/getInstructions
    }
    cout << endl;
}

// === Display a permit ===
void Interface::showPermit(const Permis& p) const {
    cout << "Permit under review: "
        << CYAN << p.getName() << RESET
        << " (" << motiveToString(p.getMotive()) << ")";
    if (p.hasWestOverride())
        cout << " - " << YELLOW << "Morse order applies" << RESET;
    cout << endl << endl;
}

// === Validate user input ===
bool Interface::validInput(const string& input) const {
    if (input.empty()) return false;
    for (char c : input)
        if (!isdigit(c)) return false;
    int val = stoi(input);
    return (val == 0 || val == 1 || val == 2);
}

// === Display day summary ===
void Interface::showDaySummary() {
    cout << "\n============================" << endl;
    cout << YELLOW << "Summary of Day " << day << RESET << endl;
    cout << CYAN << "Current total score: " << score << RESET << endl;
    cout << "============================" << endl << endl;
}

// === Main game loop ===
void Interface::run() {
    while (choice != 0) {
        cout << YELLOW << "=== DAY " << day << " ===" << RESET << endl;

        // Generate daily policy and permits
        jeu.generateDay();
        showPolicy();

        const auto& dailyPermits = jeu.getPermits();

        for (size_t i = 0; i < dailyPermits.size(); ++i) {
            const Permis& p = dailyPermits[i];
            showPermit(p);

            string input;
            showMenu();
            getline(cin, input);

            if (!validInput(input)) {
                cout << RED << "Invalid input! Please enter 0, 1, or 2." << RESET << endl;
                --i; // repeat the same permit
                continue;
            }

            choice = stoi(input);
            if (choice == 0) break;

            bool decision = (choice == 1);
            jeu.applyDecision(static_cast<int>(i), decision);
            actions++;

            cout << (decision ? GREEN + string("Permit approved.") : RED + string("Permit denied.")) << RESET << endl;
            cout << CYAN << "Current score: " << jeu.getTotalScore() << RESET << endl << endl;
        }

        if (choice == 0) break;

        // Calculate daily points
        int pointsDay = jeu.calculateDayScore();
        score = jeu.getTotalScore();

        cout << GREEN << "Points earned today: " << pointsDay << RESET << endl;
        showDaySummary();

        // Move to next day
        day++;
        jeu.nextDay();

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
    }

    cout << GREEN << "\nGame over! Final score: " << score << " points." << RESET << endl;
    if (score >= 10)
        cout << GREEN << "Excellent work! You are a true political strategist!" << RESET << endl;
    else if (score >= 5)
        cout << YELLOW << "Not bad, keep improving!" << RESET << endl;
    else
        cout << RED << "You should pay more attention to daily policies..." << RESET << endl;
}
