#ifndef GESTIONNAIRERESEAU_H
#define GESTIONNAIRERESEAU_H

#include <string>
#include "ReseauBorne.h"

struct CritereRecherche {
    int type; // 1: distance, 2: temps, 3: coût
};

class GestionnaireReseau {
public:
    GestionnaireReseau();
    void chargerReseauDepuisFichier(const std::string& p_nomFichier);
    void afficherReseau() const;
    void plusCourtChemin(const std::string& p_origine,
                         const std::string& p_destination,
                         int p_critere,
                         int p_algorithme) const;

private:
    ReseauBorne m_reseau;
};

#endif // GESTIONNAIRERESEAU_H
