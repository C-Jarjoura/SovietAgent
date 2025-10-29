#include "Jeu.h"
#include <iostream>
#include <limits>

int main() {
    std::cout << "=============================\n";
    std::cout << "   SOVIET AGENT ++ v1.0\n";
    std::cout << "=============================\n";
    std::cout << "You are a French spy in Soviet travel control.\n";
    std::cout << "Approve or deny 4 permits per day.\n";
    std::cout << "Follow official policy... unless the West sends a secret Morse.\n";
    std::cout << "Survive as many days as possible.\n\n";

    Jeu game;
    game.generateDay();

    bool alive = true;

    while (alive) {
        game.showState();

        const auto& permits = game.getPermits();
        for (size_t i = 0; i < permits.size(); ++i) {
            std::cout << "\nPermit #" << (i + 1) << ": "
                << permits[i].getName() << " | "
                << motiveToString(permits[i].getMotive()) << "\n";

            int input = 0;
            std::cout << "1 = Approve, 2 = Deny: ";
            std::cin >> input;
            if (std::cin.fail() || (input != 1 && input != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                --i;
                continue;
            }

            bool decision = (input == 1);
            game.applyDecision((int)i, decision);
        }

        std::cout << "\nEnd of day score: " << game.getDayScore()
            << " | Threshold: " << game.getDayThreshold() << "\n";

        if (game.getDayScore() < game.getDayThreshold()) {
            alive = game.runInvestigation();
            if (!alive) break;
        }

        std::cout << "\nPress Enter to continue to next day...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        game.nextDay();
    }

    std::cout << "\n=============================\n";
    std::cout << "GAME OVER\n";
    std::cout << "Days survived: " << game.getCurrentDay() - 1 << "\n";
    std::cout << "Final score: " << game.getTotalScore() << "\n";
    std::cout << "=============================\n";
    return 0;
}
