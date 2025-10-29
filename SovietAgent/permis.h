#pragma once
#include <string>

class Permis {
private:
    std::string nom;
    std::string motif;
    bool decision;            // true = accept�, false = refus�
    std::string messageMorse; // message re�u

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

    // M�thodes utilitaires
    void afficherDebug() const; // pour tests
};
