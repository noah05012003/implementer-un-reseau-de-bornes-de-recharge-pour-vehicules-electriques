/**
 * \file Algorithmes.cpp
 * \brief Implémentation des algorithmes de graphe (Dijkstra, Bellman-Ford)
 *        À COMPLÉTER : utiliser les conteneurs vus en cours (vector/list).
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 */

#include "Algorithmes.h"
#include <vector>
#include <queue>     // file de priorité pour Dijkstra
#include <limits>    // std::numeric_limits
#include <algorithm> // std::find, std::reverse
#include <ostream>
#include <iostream>
#include <map>
using namespace std;

bool Algorithmes::dijkstra(const ReseauBorne& p_reseau,
                           const std::string& p_origine,
                           const std::string& p_destination,
                           const CritereRecherche& p_critere,
                           std::vector<std::string>& p_chemin,
                           double& p_coutTotal)
{
    unordered_map<string, double> distance;
    unordered_map<string, string> precedent;
    auto compare = [](pair<double, string> a, pair<double, string> b) {
        return a.first > b.first;
    };
    priority_queue<pair<double, string>, vector<pair<double, string>>, decltype(compare)> file(compare);

    vector<Borne> bornes = p_reseau.reqBornes();
    for (const auto& borne : bornes) {
        distance[borne.reqNom()] = numeric_limits<double>::infinity();
    }

    distance[p_origine] = 0.0;
    file.push({0.0, p_origine});

    while (!file.empty()) {
        auto [coutCourant, sommetCourant] = file.top();
        file.pop();

        if (sommetCourant == p_destination)
            break;

        vector<Trajet> trajets = p_reseau.reqTrajetsDepuis(sommetCourant);
        for (const auto& trajet : trajets) {
            string voisin = trajet.reqDestination();
            double cout = 0.0;

            if (p_critere.type == 1) { // Distance
                cout = trajet.reqDistance();
            } else if (p_critere.type == 2) { // Temps
                cout = trajet.reqTemps();
            } else if (p_critere.type == 3) { // Coût
                cout = trajet.reqCout();
            }

            double nouveauCout = distance[sommetCourant] + cout;

            if (nouveauCout < distance[voisin]) {
                distance[voisin] = nouveauCout;
                precedent[voisin] = sommetCourant;
                file.push({nouveauCout, voisin});
            }
        }
    }

    if (distance[p_destination] == numeric_limits<double>::infinity())
        return false;

    p_coutTotal = distance[p_destination];
    p_chemin.clear();

    for (string v = p_destination; v != p_origine; v = precedent[v]) {
        p_chemin.push_back(v);
    }
    p_chemin.push_back(p_origine);
    reverse(p_chemin.begin(), p_chemin.end());

    return true;
}

bool Algorithmes::bellmanFord(const ReseauBorne& p_reseau,
                              const std::string& p_origine,
                              const std::string& p_destination,
                              const CritereRecherche& p_critere,
                              std::vector<std::string>& p_chemin,
                              double& p_coutTotal)
{
    const auto bornes = p_reseau.reqBornes();
    const auto trajets = p_reseau.reqTrajets();
    const double INF = std::numeric_limits<double>::infinity();

    std::map<std::string, double> distance;
    std::map<std::string, std::string> precedent;

    // Initialisation
    for (const auto& borne : bornes) {
        distance[borne.reqNom()] = INF;
        precedent[borne.reqNom()] = "";
    }
    distance[p_origine] = 0.0;

    // Relaxation des arêtes (|V| - 1 fois)
    for (size_t i = 1; i < bornes.size(); ++i) {
        for (const auto& trajet : trajets) {
            const std::string& u = trajet.reqOrigine();
            const std::string& v = trajet.reqDestination();
            double cout = 0.0;

            if (p_critere.type == 1)      cout = trajet.reqDistance();
            else if (p_critere.type == 2) cout = trajet.reqTemps();
            else if (p_critere.type == 3) cout = trajet.reqCout();

            if (distance[u] + cout < distance[v]) {
                distance[v] = distance[u] + cout;
                precedent[v] = u;
            }
        }
    }

    for (const auto& trajet : trajets) {
        const std::string& u = trajet.reqOrigine();
        const std::string& v = trajet.reqDestination();
        double cout = 0.0;

        if (p_critere.type == 1)      cout = trajet.reqDistance();
        else if (p_critere.type == 2) cout = trajet.reqTemps();
        else if (p_critere.type == 3) cout = trajet.reqCout();

        if (distance[u] + cout < distance[v]) {
            std::cerr << "[ERREUR] Cycle de poids négatif détecté." << std::endl;
            return false;
        }
    }

    if (distance[p_destination] == INF)
        return false;

    p_chemin.clear();
    for (std::string v = p_destination; !v.empty(); v = precedent[v]) {
        p_chemin.push_back(v);
    }
    std::reverse(p_chemin.begin(), p_chemin.end());
    p_coutTotal = distance[p_destination];

    return true;
}
