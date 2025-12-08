
#ifndef OOP_CURSA_H
#define OOP_CURSA_H

#include <string>
#include <vector>
#include <map>
#include "Echipa.h"
#include "Campionat.h"

class Cursa {
private:
    std::string locatie;
    std::vector<Echipa> echipe;
    std::vector<int> puncteF1;
    Campionat &campionat;

public:
    Cursa(std::string locatie, std::vector<Echipa> echipe, Campionat &campionat);

    int punctePilotCursa(const std::string &pilotAles, std::map<std::string, int> &scoruri);

    friend std::ostream &operator<<(std::ostream &os, const Cursa &c);
};


#endif
