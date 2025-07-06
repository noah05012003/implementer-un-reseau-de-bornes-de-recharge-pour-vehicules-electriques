#ifndef RESEAUBORNE_H
#define RESEAUBORNE_H

#include <string>
#include <vector>
#include <list>
#include <utility>
#include "ContratException.h"
#include "Borne.h"
#include "Trajet.h"

class ReseauBorne {
public:
    ReseauBorne();
    ReseauBorne(const ReseauBorne& p_autre);
    ReseauBorne& operator=(const ReseauBorne& p_autre);

    void ajouterBorne(const std::string& p_nom);
    void ajouterTrajet(const std::string& p_origine, const std::string& p_destination,
                       double p_distance, double p_temps, double p_cout);

    // Accesseurs
    std::vector<Borne> reqBornes() const;
    std::vector<Trajet> reqTrajets() const;
    std::vector<Trajet> reqTrajetsDepuis(const std::string& p_origine) const;
    bool existeBorne(const std::string& p_nom) const;
    void afficherReseau() const;

private:
    std::vector<std::pair<Borne, std::list<Borne>>> m_adjacence;

    // Contient tous les trajets du réseau
    std::vector<Trajet> m_trajets;

    void verifieInvariant() const;
};

#endif // RESEAUBORNE_H
