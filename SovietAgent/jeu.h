#pragma once
#include <vector>
#include "Permis.h"
#include "PolitiqueDuJour.h"
#include "MessageOuest.h"

class Jeu {
private:
    int jourActuel;
    int scoreTotal;
    std::vector<Permis> permisDuJour;
    PolitiqueDuJour politique;
    MessageOuest message;

public:
    Jeu();
    void genererJournee();
    int calculerScoreJournee() const;
    int getScoreTotal() const;

    void afficherEtat() const;
};
