#include "MessageOuest.h"
#include <random>
#include <iostream>

MessageOuest::MessageOuest() : active(false) {}

void MessageOuest::generateForDay(double probability) {
    forcedAllow.clear();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution appear(probability);

    active = appear(gen);
    if (active) {
        std::uniform_int_distribution<int> pickMotive(0, 3);
        std::uniform_int_distribution<int> countDist(1, 2);
        int count = countDist(gen);

        for (int i = 0; i < count; ++i) {
            MotiveType m = static_cast<MotiveType>(pickMotive(gen));
            forcedAllow.insert(m);
        }
    }
}

bool MessageOuest::overrides(MotiveType m) const {
    return forcedAllow.find(m) != forcedAllow.end();
}

void MessageOuest::showDebug() const {
    if (!active) {
        std::cout << "Morse: (no message today)\n";
        return;
    }
    std::cout << "Morse: ... --- ...\n";
    std::cout << "SECRET WEST ORDER:\n";
    for (auto m : forcedAllow)
        std::cout << "  - Always ALLOW " << motiveToString(m) << "\n";
}
