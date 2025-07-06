/**
 * \file GestionnaireReseau.cpp
 * \brief Implémentation du gestionnaire principal du réseau de bornes
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 */

#include "GestionnaireReseau.h"
#include "Algorithmes.h"
#include "ContratException.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


GestionnaireReseau::GestionnaireReseau() : m_reseau() {}

void GestionnaireReseau::chargerReseauDepuisFichier(
    const std::string &p_nomFichier) {
    std::ifstream fichier(p_nomFichier);
    if (!fichier) {
        throw ContratException(__FILE__, __LINE__, "chargerReseauDepuisFichier",
                               "Impossible d'ouvrir le fichier réseau");
    }

    std::string ligne;

    // 1. Nom du réseau
    std::getline(fichier, ligne);

    // 2. Nombre de bornes
    std::getline(fichier, ligne);
    int nbBornes = std::stoi(ligne);

    // 3. Sauter "Liste des bornes:"
    std::getline(fichier, ligne);

    // 4. Bornes
    for (int i = 0; i < nbBornes; ++i) {
        std::getline(fichier, ligne);
        m_reseau.ajouterBorne(ligne);
    }

    // 5. Sauter "Liste des trajets:"
    std::getline(fichier, ligne);

    // 6. Trajets
    std::string origine, destination;
    double distance, temps, cout;
    while (true) {
        if (!std::getline(fichier, origine))
            break;
        if (origine.empty())
            break;
        if (!std::getline(fichier, destination))
            break;
        if (destination.empty())
            break;
        if (!std::getline(fichier, ligne))
            break;
        std::istringstream iss(ligne);
        if (!(iss >> distance >> temps >> cout))
            break;
        m_reseau.ajouterTrajet(origine, destination, distance, temps, cout);
    }
}

void GestionnaireReseau::afficherReseau() const { m_reseau.afficherReseau(); }

void GestionnaireReseau::plusCourtChemin(const std::string &p_origine,
                                         const std::string &p_destination,
                                         int p_critere, int p_algorithme) const {
    if (!m_reseau.existeBorne(p_origine) || !m_reseau.existeBorne(p_destination)) {
        std::cout << "[ERREUR] Borne(s) inexistante(s) dans le réseau."
                  << std::endl;
        return;
    }

    // Créer critère struct
    CritereRecherche critereRecherche{p_critere};

    std::vector<std::string> chemin;
    double coutTotal = 0.0;
    bool trouve = false;

    if (p_algorithme == 1) { // Dijkstra
        trouve = Algorithmes::dijkstra(m_reseau, p_origine, p_destination,
                                       critereRecherche, chemin, coutTotal);
    } else if (p_algorithme == 2) { // Bellman-Ford
        trouve = Algorithmes::bellmanFord(m_reseau, p_origine, p_destination,
                                          critereRecherche, chemin, coutTotal);
    } else {
        std::cout << "[ERREUR] Algorithme inconnu." << std::endl;
        return;
    }

    if (!trouve) {
        std::cout << "Aucun chemin trouvé entre " << p_origine << " et "
                  << p_destination << "." << std::endl;
        return;
    }
    std::cout << "Chemin trouvé : ";
    for (size_t i = 0; i < chemin.size(); ++i) {
        if (i > 0)
            std::cout << " -> ";
        std::cout << chemin[i];
    }
    std::cout << std::endl;

    // Ajouter les unités appropriées selon le critère
    std::string unite;
    switch (p_critere) {
    case 1:
        unite = " km";
        break; // Distance
    case 2:
        unite = " min";
        break; // Temps
    case 3:
        unite = " $";
        break; // Coût
    default:
        unite = "";
        break;
    }
    std::cout << "Coût total pour ce critère : " << coutTotal << unite
              << std::endl;
}
