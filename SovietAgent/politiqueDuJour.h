#pragma once
#include <string>
#include <vector>

class PolitiqueDuJour {
private:
    std::vector<std::string> motifsAutorises;
    std::vector<std::string> motifsInterdits;

public:
    PolitiqueDuJour();

    void genererPolitiqueAleatoire();
    bool estAutorise(const std::string& motif) const;

    void afficherDebug() const;
};
