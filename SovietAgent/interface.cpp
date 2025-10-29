#include "Interface.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>

// === ANSI Color Codes ===
const std::string RESET  = "\033[0m";
const std::string RED    = "\033[31m";
const std::string GREEN  = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN   = "\033[36m";

using namespace std;

Interface::Interface(Jeu& j)
    : jeu(j), choix(-1), jour(1), actions(0), score(0) {
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
    cout << CYAN << "Today's policy:" << RESET << endl;
    jeu.getPolitique().afficherDebug();
    cout << endl;

    if (!jeu.getMessage().getMessageMorse().empty()) {
        cout << YELLOW << "Morse message detected: "
             << jeu.getMessage().getMessageMorse() << RESET << endl;
        cout << "→ " << jeu.getMessage().getInstructions() << endl;
    }
    cout << endl;
}

// === Display a permit ===
void Interface::showPermit(const Permis& p) const {
    cout << "Permit under review: "
         << CYAN << p.getNom() << RESET
         << " (" << p.getMotif() << ")";
    if (!p.getMessageMorse().empty())
        cout << " - " << YELLOW << "Morse message received" << RESET;
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
    cout << YELLOW << "Summary of Day " << jour << RESET << endl;
    cout << CYAN << "Current total score: " << score << RESET << endl;
    cout << "============================" << endl << endl;
}

// === Main game loop ===
void Interface::run() {
    while (choix != 0) {
        cout << YELLOW << "=== DAY " << jour << " ===" << RESET << endl;

        // Generate daily policy and permits
        jeu.genererJournee();
        showPolicy();

        const auto& permisDuJour = jeu.getPermisDuJour();

        for (size_t i = 0; i < permisDuJour.size(); ++i) {
            const Permis& p = permisDuJour[i];
            showPermit(p);

            string input;
            showMenu();
            getline(cin, input);

            if (!validInput(input)) {
                cout << RED << "Invalid input! Please enter 0, 1, or 2." << RESET << endl;
                --i; // repeat the same permit
                continue;
            }

            choix = stoi(input);
            if (choix == 0) break;

            bool decision = (choix == 1);
            jeu.appliquerDecision(static_cast<int>(i), decision);
            actions++;

            cout << (decision ? GREEN + string("Permit approved.") : RED + string("Permit denied.")) << RESET << endl;
            cout << CYAN << "Current score: " << jeu.getScoreTotal() << RESET << endl << endl;
        }

        if (choix == 0) break;

        // Calculate daily points
        int pointsDay = jeu.calculerScoreJournee();
        score = jeu.getScoreTotal();

        cout << GREEN << "Points earned today: " << pointsDay << RESET << endl;
        showDaySummary();

        // Move to next day
        jour++;
        jeu.jourSuivant();

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
