/**
 * \file Trajet.cpp
 * \brief Implémentation de la classe Trajet (arc orienté pondéré)
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 */

#include "Trajet.h"

#include "ContratException.h"

Trajet::Trajet(const std::string& p_origine,
               const std::string& p_destination,
               double p_distance,
               double p_temps,
               double p_cout)
    : m_origine(p_origine),
      m_destination(p_destination),
      m_distance(p_distance),
      m_temps(p_temps),
      m_cout(p_cout) {
    PRECONDITION(!p_origine.empty());
    PRECONDITION(p_distance >= 0);
    PRECONDITION(p_temps >= 0);
}

// TODO: Vérifier les préconditions

bool Trajet::operator==(const Trajet& p_autre) const {
    // TODO: Comparer deux trajets
    return m_origine == p_autre.m_origine &&
            m_destination == p_autre.m_destination &&
            m_distance == p_autre.m_distance &&
            m_temps == p_autre.m_temps &&
            m_cout == p_autre.m_cout;
}

std::string Trajet::reqOrigine() const {
    // TODO: Retourner l'origine
    return m_origine;
}

std::string Trajet::reqDestination() const {
    // TODO: Retourner la destination
    return m_destination;
}

double Trajet::reqDistance() const {
    // TODO: Retourner la distance
    return m_distance;
}

double Trajet::reqTemps() const {
    // TODO: Retourner le temps
    return m_temps;
}

double Trajet::reqCout() const {
    // TODO: Retourner le coût
    return m_cout;
}
