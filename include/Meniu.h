#ifndef MENIU_H
#define MENIU_H

#include <vector>
#include <string>
#include "Echipa.h"
#include "Campionat.h"

class Meniu {
public:
    Meniu() = default;
    void ruleaza();

private:
    int alegeEchipa(const std::vector<Echipa>& echipe);
    std::string alegePilot(Echipa& echipa);
};

#endif
