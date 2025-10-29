#include "MessageOuest.h"
#include <iostream>
#include <random>

MessageOuest::MessageOuest() : messageMorse(""), instructions("") {}

MessageOuest::MessageOuest(const std::string& morse, const std::string& instr)
    : messageMorse(morse), instructions(instr) {
}

std::string MessageOuest::getMessageMorse() const { return messageMorse; }
std::string MessageOuest::getInstructions() const { return instructions; }

void MessageOuest::genererMessageAleatoire(double proba) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution dist(proba);

    if (dist(gen)) {
        messageMorse = "... --- ...";
        instructions = "Favorisez les permis médicaux.";
    }
    else {
        messageMorse = "";
        instructions = "";
    }
}

void MessageOuest::afficherDebug() const {
    std::cout << "Message Morse: " << messageMorse
        << " | Instructions: " << instructions << "\n";
}
