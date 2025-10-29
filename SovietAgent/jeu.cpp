#include "Jeu.h"
#include <iostream>
#include <random>

Jeu::Jeu() : jourActuel(1), scoreTotal(0) {}

void Jeu::genererJournee() {
    politique.genererPolitiqueAleatoire();
    message.genererMessageAleatoire(0.4);

    permisDuJour.clear();
    permisDuJour.emplace_back("Alice", "travail", "");
    permisDuJour.emplace_back("Bob", "tourisme", "");
    permisDuJour.emplace_back("Charlie", "santé", "");

    for (auto& p : permisDuJour) {
        bool autorise = politique.estAutorise(p.getMotif());
        p.setDecision(autorise);
    }

    scoreTotal += calculerScoreJournee();
}

int Jeu::calculerScoreJournee() const {
    int score = 0;
    for (const auto& p : permisDuJour) {
        bool conforme = politique.estAutorise(p.getMotif());
        score += (p.getDecision() == conforme) ? 10 : -5;
    }
    return score;
}

int Jeu::getScoreTotal() const { return scoreTotal; }

void Jeu::afficherEtat() const {
    std::cout << "=== Jour " << jourActuel << " ===\n";
    politique.afficherDebug();
    message.afficherDebug();
    for (auto& p : permisDuJour) p.afficherDebug();
    std::cout << "Score total : " << scoreTotal << "\n";
}
