/**
 * \file Principal.cpp
 * \brief Point d'entrée du simulateur de réseau de bornes de recharge
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 *
 * Ce fichier NE DOIT PAS être modifié par les étudiants.
 */

#include "ContratException.h"
#include "GestionnaireReseau.h"
#include <iostream>
#include <limits>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void afficherMenu() {
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║                MENU PRINCIPAL                  ║" << endl;    cout << "╠════════════════════════════════════════════════╣" << endl;
    cout << "║ 1. Charger le réseau depuis un fichier         ║" << endl;
    cout << "║ 2. Afficher le réseau                          ║" << endl;
    cout << "║ 3. Rechercher un plus court chemin (Dijkstra)  ║" << endl;
    cout << "║ 4. Rechercher un plus court chemin (Bellman)   ║" << endl;
    cout << "║ 0. Quitter                                     ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << "Votre choix : ";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string demanderBorne(const string& message) {
    string nom;
    cout << message;
    getline(cin, nom);
    cout << "  > Saisie : " << nom << endl;
    return nom;
}

int demanderCritere(bool coutAutorise) {
    cout << "Critère de recherche :" << endl;
    cout << "  1. Distance" << endl;
    cout << "  2. Temps de recharge" << endl;
    if (coutAutorise)
        cout << "  3. Coût énergétique" << endl;
    cout << "Votre choix : ";
    int critere = 0;
    cin >> critere;
    clearInput();
    cout << "  > Critère choisi : ";
    if (critere == 1) cout << "distance" << endl;
    else if (critere == 2) cout << "temps de recharge" << endl;
    else if (critere == 3 && coutAutorise) cout << "coût énergétique" << endl;
    else cout << "(invalide)" << endl;
    return critere;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Affichage d'en-tête
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║  SIMULATEUR DE RÉSEAU DE BORNES ÉLECTRIQUES  ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;


    GestionnaireReseau gestionnaire;
    int choix = -1;

    while (true) {
        afficherMenu();

        if (!(cin >> choix)) {
            clearInput();
            cout << "[Entrée invalide, veuillez entrer un numéro d'option.]" << endl;
            continue;
        }
        clearInput();

        cout << endl << "Option choisie : " << choix << endl;

        try {
            switch (choix) {
            case 1: {
                cout << endl << "[INITIALISATION]" << endl;
                std::string chemin = "data/ReseauBorne.txt"; 
                cout << "  > Fichier : " << chemin << endl;
                gestionnaire.chargerReseauDepuisFichier(chemin);
                cout << "Chargement du réseau effectué avec succès !" << endl;
                break;
            }
            case 2: {
                cout << "[AFFICHAGE] État actuel du réseau :" << endl;
                gestionnaire.afficherReseau();
                break;
            }
            case 3: {
                cout << "[RECHERCHE DIJKSTRA]" << endl;
                string origine = demanderBorne("Nom de la borne d'origine : ");
                string destination = demanderBorne("Nom de la borne de destination : ");
                int critere = demanderCritere(false); // Coût interdit
                if (critere != 1 && critere != 2) {
                    cout << "Critère invalide. (Distance=1, Temps=2)" << endl;
                    break;
                }
                gestionnaire.plusCourtChemin(origine, destination, critere, 1); // 1 = Dijkstra
                break;
            }
            case 4: {
                cout << "[RECHERCHE BELLMAN-FORD]" << endl;
                string origine = demanderBorne("Nom de la borne d'origine : ");
                string destination = demanderBorne("Nom de la borne de destination : ");
                int critere = demanderCritere(true); // Coût autorisé
                if (critere < 1 || critere > 3) {                cout << "Critère invalide. (Distance=1, Temps=2, Coût=3)" << endl;
                    break;
                }
                gestionnaire.plusCourtChemin(origine, destination, critere, 2); // 2 = Bellman-Ford
                break;
            }
            case 0: {
                cout << "Au revoir!" << endl;
                return 0;
            }
            default:
                cout << "[Option inconnue, veuillez réessayer.]" << endl;
                break;
            }
        } catch (const ContratException &e) {
            cout << "[ERREUR CONTRAT] : " << e.reqTexteException() << endl;
        } catch (const std::exception &e) {
            cout << "[ERREUR] : " << e.what() << endl;
        } catch (...) {
            cout << "[ERREUR inconnue]" << endl;
        }
    }

    return 0;
}
