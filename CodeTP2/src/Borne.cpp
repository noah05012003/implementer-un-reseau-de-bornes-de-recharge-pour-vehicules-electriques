/**
 * \file Borne.cpp
 * \brief Implémentation de la classe Borne (borne de recharge)
 * \author Support pédagogique
 * \version 1.0
 * \date Juin 2025
 */

#include "Borne.h"

#include "ContratException.h"

Borne::Borne() : m_nom("") {}

Borne::Borne(const std::string& p_nom) : m_nom(p_nom) {
    // TODO: Vérifier la précondition
    PRECONDITION(!p_nom.empty());
}

bool Borne::operator==(const Borne& p_autre) const {
    // TODO: Comparer deux bornes
    return m_nom == p_autre.m_nom;
}

std::string Borne::reqNom() const {
    // TODO: Retourner le nom
    return m_nom;
}
