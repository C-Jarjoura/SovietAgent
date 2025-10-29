#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <cctype>
using namespace std;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";

// === Fonction pour obtenir un code Morse aléatoire ===
string randomMorse() {
    vector<string> morseList = {
        "... --- ...",          // SOS
        ".- .-.. .. -.-. .",    // ALICE
        "-... --- -...",        // BOB
        "-.-. .... .- .-. .-.. .. .", // CHARLIE
        "-.. .. .- -. .-",      // DIANA
        ". .-.. ..",            // ELI
        "-- --- .-. ... .",     // MORSE
        ".--. . .-. -- .. -",   // PERMIT
        "-.-. --- -.. .",       // CODE
        "... . -.-. .-. . -"    // SECRET
    };
    return morseList[rand() % morseList.size()];
}

// === Permit class ===
class Permit {
public:
    string name;
    string policy;
    bool hasMorseCode;

    Permit(string n, string p, bool m = false)
        : name(n), policy(p), hasMorseCode(m) {
    }
};

// === Display menu ===
void showMenu() {
    cout << "=========================\n";
    cout << "      MAIN MENU\n";
    cout << "=========================\n";
    cout << "1. Approve\n";
    cout << "2. Deny\n";
    cout << "0. Quit\n";
    cout << "=========================\n";
    cout << "Your choice: ";
}

int main() {
    srand(time(0));

    int choice = -1;
    int day = 1;
    int actions = 0;
    int score = 0;

    int approvedTotal = 0;  // Total approvals
    int deniedTotal = 0;    // Total denials
    int morseTotal = 0;     // Total actions pro-Ouest

    // Daily counters
    int approvedToday = 0;
    int deniedToday = 0;
    int pointsToday = 0;
    int cotaToday = 5 + rand() % 6; // cota initiale aléatoire entre 5 et 10

    // List of policies and their descriptions
    vector<string> policies = {
        "Family",
        "Travel",
        "Business",
        "Undecided",
        "Gaming Campaign"
    };

    vector<string> descriptions = {
        "Priority to families and home stability.",
        "Encourage discoveries and mobility.",
        "Promote entrepreneurship and trade.",
        "Total indecision: anything can happen today.",
        "Support entertainment and fun activities."
    };

    // Existing permit holders
    vector<Permit> permitList = {
        Permit("Alice", "Family"),
        Permit("Bob", "Travel"),
        Permit("Charlie", "Business"),
        Permit("Diana", "Gaming Campaign"),
        Permit("Eli", "Undecided")
    };

    // Function to randomly choose 1 or 2 policies for the day
    auto choosePolicies = [&](string& p1, string& p2, bool& twoPolicies) {
        twoPolicies = (rand() % 2 == 0);
        int index1 = rand() % policies.size();
        p1 = policies[index1];
        p2 = "";
        if (twoPolicies) {
            int index2 = rand() % policies.size();
            while (index2 == index1) index2 = rand() % policies.size();
            p2 = policies[index2];
        }
        };

    bool twoPolicies = false;
    string dailyPolicy1, dailyPolicy2;
    choosePolicies(dailyPolicy1, dailyPolicy2, twoPolicies);

    // === Main game loop ===
    while (choice != 0) {
        cout << YELLOW << "=== Day " << day << " ===" << RESET << endl;

        cout << CYAN << "Today's Policy(ies):" << RESET << endl;
        int index1 = -1, index2 = -1;
        for (int i = 0; i < policies.size(); i++) {
            if (policies[i] == dailyPolicy1) index1 = i;
            if (twoPolicies && policies[i] == dailyPolicy2) index2 = i;
        }

        cout << "  1. " << CYAN << dailyPolicy1 << RESET
            << " - " << descriptions[index1] << endl;
        if (twoPolicies)
            cout << "  2. " << CYAN << dailyPolicy2 << RESET
            << " - " << descriptions[index2] << endl;

        cout << endl;

        // Random permit selection
        Permit p = permitList[rand() % permitList.size()];

        // 20% chance for a Morse code permit
        p.hasMorseCode = (rand() % 5 == 0);

        cout << "Permit under review: " << p.name
            << " (" << p.policy << ")";
        if (p.hasMorseCode) {
            string code = randomMorse();
            cout << " - " << YELLOW << "Morse Code detected: " << code << RESET;
        }
        cout << endl << endl;

        // ======= SECURE INPUT SECTION =======
        string input;
        showMenu();
        getline(cin, input);

        if (input.empty()) {
            cout << RED << "Invalid input! Please enter a number (0, 1, or 2)." << RESET << endl;
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << RED << "Invalid input! Please enter a number (0, 1, or 2)." << RESET << endl;
            continue;
        }

        choice = stoi(input);
        // ====================================

        switch (choice) {
        case 1: // Approve
            actions++;
            approvedToday++;
            approvedTotal++;
            if (p.hasMorseCode) {
                score += 3;
                pointsToday += 3;
                morseTotal++;
                cout << GREEN << "Morse code verified! +3 points." << RESET << endl;
            }
            else if (p.policy == dailyPolicy1 || (twoPolicies && p.policy == dailyPolicy2)) {
                score += 2;
                pointsToday += 2;
                cout << GREEN << "Good approval! +2 points." << RESET << endl;
            }
            else {
                score -= 1;
                pointsToday -= 1;
                cout << RED << "Wrong approval! -1 point." << RESET << endl;
            }
            break;

        case 2: // Deny
            actions++;
            deniedToday++;
            deniedTotal++;
            if (!p.hasMorseCode &&
                p.policy != dailyPolicy1 &&
                (!twoPolicies || p.policy != dailyPolicy2)) {
                score += 2;
                pointsToday += 2;
                cout << GREEN << "Good denial! +2 points." << RESET << endl;
            }
            else {
                cout << YELLOW << "Questionable denial (permit matched today's policy or Morse code)." << RESET << endl;
            }
            break;

        case 0:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << RED << "Invalid choice, please try again." << RESET << endl;
            break;
        }

        // End of day summary
        if (actions >= 4) {
            cout << "\n============================" << endl;
            cout << YELLOW << "Summary of Day " << day << RESET << endl;
            cout << GREEN << "Approved: " << approvedToday << RESET << endl;
            cout << RED << "Denied: " << deniedToday << RESET << endl;
            cout << CYAN << "Points today: " << pointsToday << " / " << cotaToday << RESET << endl;
            cout << CYAN << "Total score: " << score << RESET << endl;
            cout << "============================" << endl;

            // Vérification du seuil
            if (pointsToday < cotaToday) {
                cout << RED << "Le score du jour est inferieur au cota ! Enquête..." << RESET << endl;

                // Calcul modificateur de résistance : nb de décisions pro-Ouest (Morse code)
                int resistanceMod = approvedToday / 3;

                int d20 = rand() % 20 + 1;
                int total = d20 + resistanceMod;
                cout << "Jet de d20: " << d20 << " + modificateur(" << resistanceMod << ") = " << total << endl;

                if (total >= 14) {
                    cout << GREEN << "=== Echappée belle ! Vous continuez le jeu ===" << RESET << endl;
                }
                else {
                    cout << RED << "=== Capture ! Fin de partie ===" << RESET << endl;
                    break; // fin de la boucle principale
                }
            }

            // Reset counters for next day
            day++;
            actions = 0;
            approvedToday = 0;
            deniedToday = 0;
            pointsToday = 0;

            // New cota for next day (never decreasing)
            int newCota = 5 + rand() % 6; // aléatoire
            cotaToday = max(cotaToday, newCota);

            // New policies for next day
            choosePolicies(dailyPolicy1, dailyPolicy2, twoPolicies);
            cout << YELLOW << "\nNew day: Day " << day << RESET << endl;
        }

        // Display score
        cout << CYAN << "\nCurrent score: " << score << RESET << endl;

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
    }

    // === End of game summary ===
    cout << GREEN << "\n=== Game Over ===" << RESET << endl;
    cout << "Days played: " << day - 1 << endl;
    cout << "Total score: " << score << endl;
    cout << "Total approved: " << approvedTotal << endl;
    cout << "Total denied: " << deniedTotal << endl;
    cout << "Total pro-Ouest actions (Morse code): " << morseTotal << endl;

    double obediencePercent = (double)morseTotal / max(1, approvedTotal) * 100.0;
    cout << "Obedience to Ouest / policy: " << obediencePercent << " %" << endl;

    if (score >= 10)
        cout << GREEN << "Excellent work! You are a true political strategist!" << RESET << endl;
    else if (score >= 5)
        cout << YELLOW << "Not bad at all, you're getting there." << RESET << endl;
    else
        cout << RED << "You should pay more attention to the daily policies..." << RESET << endl;
}
