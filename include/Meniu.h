#ifndef MENIU_H
#define MENIU_H

#include <vector>
#include <string>
#include "Echipa.h"

class Meniu {
public:
    Meniu() = default;

    static void ruleaza();

private:
    static int alegeEchipa(const std::vector<Echipa>& echipe);

    static std::string alegePilot(Echipa& echipa);
};

#endif
