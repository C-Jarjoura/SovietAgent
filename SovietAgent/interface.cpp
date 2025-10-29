#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// Codes ANSI pour les couleurs
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";

// === Classe Permis ===
class Permis {
public:
    string nom;
    string politique;

    Permis(string n, string p) : nom(n), politique(p) {}
};

// === Fonction d'affichage du menu ===
void afficherMenu() {
    cout << "=========================\n";
    cout << "   MENU PRINCIPAL\n";
    cout << "=========================\n";
    cout << "1. Valider\n";
    cout << "2. Refuser\n";
    cout << "0. Quitter\n";
    cout << "=========================\n";
    cout << "Votre choix : ";
}

int main() {
    srand(time(0));

    int choix = -1;
    int jour = 1;
    int actions = 0;
    int score = 0;

    // Compteurs du jour
    int validesJour = 0;
    int refusesJour = 0;
    int pointsJour = 0;

    // Liste des politiques et descriptions
    vector<string> politiques = {
        "Famille",
        "Voyage",
        "Business",
        "Je ne sais pas",
        "Campagne de jeux"
    };

    vector<string> descriptions = {
        "Priorité aux familles et à la stabilité du foyer.",
        "Encourager les découvertes et la mobilité.",
        "Promouvoir l'entrepreneuriat et le commerce.",
        "Indécision totale : tout peut arriver aujourd'hui.",
        "Soutenir le divertissement et les activités ludiques."
    };

    // Liste de permis existants
    vector<Permis> permisList = {
        Permis("Alice", "Famille"),
        Permis("Bob", "Voyage"),
        Permis("Charlie", "Business"),
        Permis("Diana", "Campagne de jeux"),
        Permis("Eli", "Je ne sais pas")
    };

    // Fonction pour choisir 1 ou 2 politiques aléatoirement
    auto choisirPolitiques = [&](string& p1, string& p2, bool& deuxPolitiques) {
        deuxPolitiques = (rand() % 2 == 0); // 50% chance pour 2 politiques
        int index1 = rand() % politiques.size();
        p1 = politiques[index1];
        p2 = "";
        if (deuxPolitiques) {
            int index2 = rand() % politiques.size();
            while (index2 == index1) index2 = rand() % politiques.size();
            p2 = politiques[index2];
        }
        };

    bool deuxPolitiques = false;
    string politiqueJour1, politiqueJour2;
    choisirPolitiques(politiqueJour1, politiqueJour2, deuxPolitiques);

    // Boucle principale du jeu
    while (choix != 0) {
        cout << YELLOW << "=== Jour " << jour << " ===" << RESET << endl;

        // Affichage des politiques du jour
        cout << CYAN << "Politique(s) du jour :" << RESET << endl;

        int index1 = -1, index2 = -1;
        for (int i = 0; i < politiques.size(); i++) {
            if (politiques[i] == politiqueJour1) index1 = i;
            if (deuxPolitiques && politiques[i] == politiqueJour2) index2 = i;
        }

        cout << "  1. " << CYAN << politiqueJour1 << RESET
            << " - " << descriptions[index1] << endl;

        if (deuxPolitiques)
            cout << "  2. " << CYAN << politiqueJour2 << RESET
            << " - " << descriptions[index2] << endl;

        cout << endl;

        // Tirage d'un permis aléatoire
        Permis p = permisList[rand() % permisList.size()];
        cout << "Permis en examen : " << p.nom
            << " (" << p.politique << ")" << endl << endl;

        afficherMenu();
        cin >> choix;

        switch (choix) {
        case 1: // Valider
            actions++;
            validesJour++;
            if (p.politique == politiqueJour1 || (deuxPolitiques && p.politique == politiqueJour2)) {
                score += 2;
                pointsJour += 2;
                cout << GREEN << "Bonne validation ! +2 points." << RESET << endl;
            }
            else {
                score -= 1;
                pointsJour -= 1;
                cout << RED << "Mauvaise validation ! -1 point." << RESET << endl;
            }
            break;

        case 2: // Refuser
            actions++;
            refusesJour++;
            if (p.politique != politiqueJour1 && (!deuxPolitiques || p.politique != politiqueJour2)) {
                score += 2;
                pointsJour += 2;
                cout << GREEN << "Bon refus ! +2 points." << RESET << endl;
            }
            else {
                cout << YELLOW << "Refus discutable (le permis était conforme à une politique du jour)." << RESET << endl;
            }
            break;

        case 0:
            cout << "Au revoir !" << endl;
            break;

        default:
            cout << RED << "Choix invalide, réessayez." << RESET << endl;
            break;
        }

        // Passage au jour suivant après 4 actions
        if (actions >= 4) {
            cout << "\n============================" << endl;
            cout << YELLOW << "Résumé du Jour " << jour << RESET << endl;
            cout << GREEN << "Validés : " << validesJour << RESET << endl;
            cout << RED << "Refusés : " << refusesJour << RESET << endl;
            cout << CYAN << "Points du jour : " << pointsJour << RESET << endl;
            cout << CYAN << "Score total : " << score << RESET << endl;
            cout << "============================" << endl;

            // Réinitialiser les compteurs du jour
            jour++;
            actions = 0;
            validesJour = 0;
            refusesJour = 0;
            pointsJour = 0;

            // Nouveau tirage de politiques
            choisirPolitiques(politiqueJour1, politiqueJour2, deuxPolitiques);
            cout << YELLOW << "\nNouveau jour : Jour " << jour << RESET << endl;
        }

        // Afficher le score actuel
        cout << CYAN << "\nScore actuel : " << score << RESET << endl;

        if (choix != 0) {
            cout << "\nAppuyez sur Entrée pour continuer...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            cout << endl;
        }
    }

    // Fin du jeu
    cout << GREEN << "\nPartie terminée ! Score final : " << score << " points." << RESET << endl;

    if (score >= 10)
        cout << GREEN << "Excellent travail ! Tu es un vrai stratège politique !" << RESET << endl;
    else if (score >= 5)
        cout << YELLOW << "Pas mal du tout, tu progresses bien." << RESET << endl;
    else
        cout << RED << "Tu devrais être plus attentif aux politiques du jour..." << RESET << endl;
}
