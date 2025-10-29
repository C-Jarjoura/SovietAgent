#pragma once
#include <string>

class Permis {
private:
    std::string nom;
    std::string motif;
    bool decision;            // true = accepté, false = refusé
    std::string messageMorse; // message reçu

public:
    // Constructeurs
    Permis();
    Permis(const std::string& nom, const std::string& motif, const std::string& morse);

    // Getters / Setters
    std::string getNom() const;
    std::string getMotif() const;
    bool getDecision() const;
    std::string getMessageMorse() const;

    void setDecision(bool value);

    // Méthodes utilitaires
    void afficherDebug() const; // pour tests
};
