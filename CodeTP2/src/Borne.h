#ifndef BORNE_H
#define BORNE_H

#include <string>

class Borne {
public:
    Borne();
    explicit Borne(const std::string& p_nom);

    bool operator==(const Borne& p_autre) const;

    std::string reqNom() const;

private:
    std::string m_nom;
};

#endif // BORNE_H
