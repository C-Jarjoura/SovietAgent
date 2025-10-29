#include "PolitiqueDuJour.h"
#include <iostream>
#include <random>

PolitiqueDuJour::PolitiqueDuJour() {}

void PolitiqueDuJour::genererPolitiqueAleatoire() {
    motifsAutorises = { "travail", "santé" };
    motifsInterdits = { "tourisme" };
}

bool PolitiqueDuJour::estAutorise(const std::string& motif) const {
    for (const auto& interdit : motifsInterdits)
        if (motif == interdit) return false;
    return true;
}

void PolitiqueDuJour::afficherDebug() const {
    std::cout << "Motifs autorisés : ";
    for (auto& m : motifsAutorises) std::cout << m << " ";
    std::cout << "\nMotifs interdits : ";
    for (auto& m : motifsInterdits) std::cout << m << " ";
    std::cout << "\n";
}
