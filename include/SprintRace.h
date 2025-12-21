#ifndef SPRINT_RACE_H
#define SPRINT_RACE_H

#include "Eveniment.h"
#include "Echipa.h"
#include <vector>
#include <string>
#include <map>

class SprintRace : public Eveniment {
private:
    std::vector<Echipa> echipe;
    std::vector<int> puncteSprint;
    int agresivitatePiloti;

public:
    SprintRace(const std::string &locatie, std::vector<Echipa> e, int agresivitate);

    void simuleazaEveniment() override;

    [[nodiscard]] Eveniment *clone() const override;

    void afisareVirtuala() const override;

    [[nodiscard]] double calculeazaRiscAbandon() const override;

    void acordaPuncteSprint(std::map<std::string, int> &scoruri);
};

#endif
