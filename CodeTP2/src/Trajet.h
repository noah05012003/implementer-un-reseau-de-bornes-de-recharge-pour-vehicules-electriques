#ifndef TRAJET_H
#define TRAJET_H

#include <string>

class Trajet {
public:
    Trajet(const std::string& p_origine,
           const std::string& p_destination,
           double p_distance,
           double p_temps,
           double p_cout);

    bool operator==(const Trajet& p_autre) const;

    // Accesseurs
    std::string reqOrigine() const;
    std::string reqDestination() const;
    double reqDistance() const;
    double reqTemps() const;
    double reqCout() const;

private:
    std::string m_origine;
    std::string m_destination;
    double m_distance;
    double m_temps;
    double m_cout;
};

#endif // TRAJET_H
