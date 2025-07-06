/**
 * \file ReseauBorne.cpp
 * \brief Implémentation de la classe ReseauBorne (graphe de bornes et trajets)
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 */

#include "ReseauBorne.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


ReseauBorne::ReseauBorne() 
{
    // Constructeur par défaut, initialise un réseau vide
}

/* ReseauBorne::ReseauBorne(const ReseauBorne& p_autre) {} */

ReseauBorne& ReseauBorne::operator=(const ReseauBorne& p_autre)
{
    if (this != &p_autre) {
        m_adjacence = p_autre.m_adjacence;
        m_trajets = p_autre.m_trajets;
    }
    return *this;
}

void ReseauBorne::ajouterBorne(const std::string& p_nom)
{
    PRECONDITION(!p_nom.empty());
    if (!existeBorne(p_nom)) {
        m_adjacence.emplace_back(Borne(p_nom), std::list<Borne>{});
    }
    POSTCONDITION(existeBorne(p_nom));
    INVARIANTS();
}

void ReseauBorne::ajouterTrajet(const std::string& p_origine, const std::string& p_destination,
                                double p_distance, double p_temps, double p_cout)
{
    PRECONDITION(existeBorne(p_origine));
    PRECONDITION(existeBorne(p_destination));
    PRECONDITION(!p_origine.empty());
    PRECONDITION(p_distance > 0);
    PRECONDITION(p_temps > 0);

    m_trajets.emplace_back(p_origine, p_destination, p_distance, p_temps, p_cout);

    for (auto& [borne, voisins] : m_adjacence) {
        if (borne.reqNom() == p_origine) {
            voisins.push_back(Borne(p_destination));
            break;
        }
    }
    INVARIANTS();
}

std::vector<Borne> ReseauBorne::reqBornes() const
{
    std::vector<Borne> bornes;
    for (const auto& [borne, _] : m_adjacence) {
        bornes.push_back(borne);
    }
    return bornes;
}

std::vector<Trajet> ReseauBorne::reqTrajets() const
{
    return m_trajets;
}

std::vector<Trajet> ReseauBorne::reqTrajetsDepuis(const std::string& p_origine) const
{
    // TODO: Retourner les trajets depuis une borne
    std::vector<Trajet> trajets;
    for (const auto& trajet : m_trajets) {
        if (trajet.reqOrigine() == p_origine) {
            trajets.push_back(trajet);
        }
    }
    return trajets;
}

bool ReseauBorne::existeBorne(const std::string& p_nom) const
{
    return std::any_of(m_adjacence.begin(), m_adjacence.end(), [&](const auto& pair) {
        return pair.first.reqNom() == p_nom;
    });
}

void ReseauBorne::afficherReseau() const
{
    // -------------------------------------------------------------------
    // NOTE AUX ÉTUDIANT·E·S :
    // Cette fonction d'affichage est fournie afin de faciliter le débogage
    // et la visualisation de votre graphe. NE LA MODIFIEZ PAS.
    // Les autres méthodes marquées TODO demeurent à compléter.
    // -------------------------------------------------------------------

     std::cout << "\n========== TOPOLOGIE DU RÉSEAU ==========" << std::endl;
    for (const auto& elem : m_adjacence) {
        const std::string& nom = elem.first.reqNom();
        std::cout << "Borne : " << nom << std::endl;
        
        // Chercher les trajets depuis cette borne directement dans m_trajets
        std::vector<const Trajet*> trajetsDepuisBorne;
        for (const auto& trajet : m_trajets) {
            if (trajet.reqOrigine() == nom) {
                trajetsDepuisBorne.push_back(&trajet);
            }
        }
        
        if (!trajetsDepuisBorne.empty()) {
            for (const Trajet* t : trajetsDepuisBorne) {
                if (t != nullptr) {
                    try {
                        std::cout << "    → "
                                  << std::left << t->reqDestination()
                                  << " | Distance : " << t->reqDistance() << " km"
                                  << " | Temps : " << t->reqTemps() << " min"
                                  << " | Coût : " << t->reqCout() << " $" << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << "    → [ERREUR] : " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "    → [ERREUR] : Pointeur de trajet null" << std::endl;
                }
            }
        } else {
            std::cout << "    (aucun trajet sortant)" << std::endl;
        }
    }
    std::cout << "==========================================\n" << std::endl;
}

void ReseauBorne::verifieInvariant() const
{
    for (size_t i = 0; i < m_adjacence.size(); ++i) {
        for (size_t j = i + 1; j < m_adjacence.size(); ++j) {
            INVARIANT(m_adjacence[i].first.reqNom() != m_adjacence[j].first.reqNom());
        }
    }
}
