#define NOMINMAX            // 🔧 fix: prevent Windows macro conflict
#include <windows.h>        // must come before iostream
#include "Jeu.h"
#include <iostream>
#include <limits>

// === ANSI Color Codes ===
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[37m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string BRIGHT_BLUE = "\033[94m";
const std::string BRIGHT_RED = "\033[91m";
const std::string BOLD = "\033[1m";

int main() {
    // === Enable ANSI color support ===
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // === Intro Screen ===
    std::cout << RED << "=============================\n";
    std::cout << "      SOVIET AGENT ++ v1.0\n";
    std::cout << "=============================\n" << RESET;
    std::cout << "You are a French spy in Soviet travel control.\n";
    std::cout << "Approve or deny 4 permits per day.\n";
    std::cout << "Follow official policy... unless the West sends a secret Morse.\n";
    std::cout << "Survive as many days as possible.\n\n";

    // === Quick sound test ===
    std::cout << CYAN << "Testing audio... " << RESET;
    Beep(880, 150);
    Sleep(100);
    Beep(880, 150);
    Sleep(100);
    Beep(880, 150);
    std::cout << GREEN << "OK!\n\n" << RESET;

    Jeu game;
    game.generateDay();

    bool alive = true;

    while (alive) {
        game.showState();

        const auto& permits = game.getPermits();
        for (size_t i = 0; i < permits.size(); ++i) {
            std::cout << CYAN << "\nPermit #" << (i + 1) << ": " << RESET
                << permits[i].getName() << " | "
                << motiveToString(permits[i].getMotive()) << "\n";

            int input = 0;
            std::cout << "1 = Approve, 2 = Deny: ";
            std::cin >> input;
            if (std::cin.fail() || (input != 1 && input != 2)) {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');  // 👈 note les parenthèses
                std::cout << RED << "Invalid input.\n" << RESET;
                --i;
                continue;
            }

            bool decision = (input == 1);
            game.applyDecision((int)i, decision);
        }

        std::cout << "\nDay summary:\n";
        std::cout << "  Score: " << YELLOW << game.getDayScore() << RESET
            << " | Threshold: " << YELLOW << game.getDayThreshold() << RESET << "\n";

        if (game.getDayScore() < game.getDayThreshold()) {
            alive = game.runInvestigation();
            if (!alive) break;
        }

        std::cout << "\nPress Enter to continue to the next day...";
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cin.get();

        game.nextDay();
    }

    // === End screen ===
    std::cout << "\n" << RED << "=============================\n";
    std::cout << "          GAME OVER\n";
    std::cout << "=============================\n" << RESET;
    std::cout << GREEN << "Days survived: " << (game.getCurrentDay() - 1) << "\n";
    std::cout << "Final score: " << game.getTotalScore() << RESET << "\n";
    std::cout << YELLOW << "Thanks for playing Soviet Agent ++\n" << RESET;

    Beep(440, 200);
    Beep(349, 250);
    Beep(294, 300);

    return 0;
}
