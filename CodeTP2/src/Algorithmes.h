#ifndef ALGORITHMES_H
#define ALGORITHMES_H

#include "ReseauBorne.h"
#include <vector>
#include <string>
#include "GestionnaireReseau.h" // pour CritereRecherche

class Algorithmes {
public:
    static bool dijkstra(const ReseauBorne& p_reseau,
                         const std::string& p_origine,
                         const std::string& p_destination,
                         const CritereRecherche& p_critere,
                         std::vector<std::string>& p_chemin,
                         double& p_coutTotal);

    static bool bellmanFord(const ReseauBorne& p_reseau,
                            const std::string& p_origine,
                            const std::string& p_destination,
                            const CritereRecherche& p_critere,
                            std::vector<std::string>& p_chemin,
                            double& p_coutTotal);
};

#endif // ALGORITHMES_H
