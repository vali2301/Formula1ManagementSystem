#ifndef ECHIPA_H
#define ECHIPA_H

#include <string>
#include <vector>
#include <iostream>
#include "Pilot.h"

class Echipa {
private:
    std::string nume;
    std::vector<Pilot> piloti;

public:
    Echipa(const std::string& n, std::vector<std::string> numePiloti);
    Echipa(const Echipa& e);
    Echipa& operator=(const Echipa& e);
    ~Echipa();

    const std::string& getNume() const;
    std::vector<Pilot>& getPiloti();

    friend std::ostream& operator<<(std::ostream& os, const Echipa& e);
};

#endif
