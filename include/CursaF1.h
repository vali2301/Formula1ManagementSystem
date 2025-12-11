#ifndef CURSA_F1_H
#define CURSA_F1_H

#include <string>
#include <vector>
#include <map>
#include "Echipa.h"
#include "Campionat.h"
#include "Eveniment.h"

class CursaF1 : public Eveniment {
private:
    std::vector<Echipa> echipe;
    std::vector<int> puncteF1;
    Campionat &campionat;

    std::vector<std::pair<std::string, int>> clasamentFinal;

public:
    CursaF1(std::string locatie, std::vector<Echipa> echipe, Campionat &campionat);

    virtual void simuleazaEveniment() override;
    virtual Eveniment* clone() const override;
    virtual void afisareVirtuala() const override;
    virtual double calculeazaRiscAbandon() const override;

    int punctePilotCursa(const std::string &pilotAles, std::map<std::string, int> &scoruri);

    CursaF1(const CursaF1& other);
    CursaF1& operator=(const CursaF1& other);

    friend std::ostream &operator<<(std::ostream &os, const CursaF1 &c);
};

#endif