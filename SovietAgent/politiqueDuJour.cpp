#include "PolitiqueDuJour.h"
#include <iostream>
#include <random>

PolitiqueDuJour::PolitiqueDuJour() {}

void PolitiqueDuJour::generateRandomPolicy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution coin(0.5);

    allowed[MotiveType::Tourism] = coin(gen);
    allowed[MotiveType::Family] = coin(gen);
    allowed[MotiveType::Business] = coin(gen);
    allowed[MotiveType::Diplomat] = coin(gen);
}

bool PolitiqueDuJour::isAllowed(MotiveType m) const {
    std::map<MotiveType, bool>::const_iterator it = allowed.find(m);
    if (it == allowed.end()) return false;
    return it->second;
}

// --- FIXED: no structured bindings, no 'afficherDebug' ---
void PolitiqueDuJour::showDebug() const {
    std::cout << "OFFICIAL POLICY TODAY\n";
    std::cout << "----------------------\n";

    for (std::map<MotiveType, bool>::const_iterator it = allowed.begin(); it != allowed.end(); ++it) {
        MotiveType motive = it->first;
        bool val = it->second;
        std::cout << motiveToString(motive)
            << ": " << (val ? "ALLOW" : "DENY") << "\n";
    }
}
