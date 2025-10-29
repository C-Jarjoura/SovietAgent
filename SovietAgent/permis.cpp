#include "Permis.h"
#include <iostream>

Permis::Permis() : nom("Inconnu"), motif(""), decision(false), messageMorse("") {}

Permis::Permis(const std::string& n, const std::string& m, const std::string& morse)
    : nom(n), motif(m), decision(false), messageMorse(morse) {
}

std::string Permis::getNom() const { return nom; }
std::string Permis::getMotif() const { return motif; }
bool Permis::getDecision() const { return decision; }
std::string Permis::getMessageMorse() const { return messageMorse; }

void Permis::setDecision(bool value) { decision = value; }

void Permis::afficherDebug() const {
    std::cout << "Permis de " << nom
        << " | Motif: " << motif
        << " | Morse: " << messageMorse
        << " | Decision: " << (decision ? "Accepté" : "Refusé") << "\n";
}
