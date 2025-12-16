#include "ConditiiMeteo.h"
#include <iostream>
#include <random>
#include <string>

ConditiiMeteo::ConditiiMeteo(const std::string &circuit)
    : vremeActuala(Soare),
      coeficientAderenta(1.0),
      numeCircuit(circuit)
{
    schimbaVremea();
}


void ConditiiMeteo::schimbaVremea() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 9);

    int alegere = dist(gen);

    if (alegere <= 1) {
        vremeActuala = PloaieUsoara;
        coeficientAderenta = 0.95;
    } else if (alegere == 0) {
        vremeActuala = PloaieTorentiala;
        coeficientAderenta = 0.88;
    } else if (alegere <= 3) {
        vremeActuala = Nori;
        coeficientAderenta = 1.0;
    } else {
        vremeActuala = Soare;
        coeficientAderenta = 1.02;
    }
}

std::string ConditiiMeteo::getNumeVreme() const {
    switch (vremeActuala) {
        case Soare: return "Soare si uscat";
        case Nori: return "Acoperit, uscat";
        case PloaieUsoara: return "Ploaie usoara (circuit umed)";
        case PloaieTorentiala: return "Ploaie torentiala (conditii extreme)";
    }
    return "Necunoscut";
}

std::ostream& operator<<(std::ostream& os, const ConditiiMeteo& cm) {
    os << "Vreme: " << cm.getNumeVreme() << "\n";
    if (cm.coeficientAderenta < 1.0) {
        os << "  -> Aderenta scazuta! (Risc crescut)\n";
    } else if (cm.coeficientAderenta > 1.0) {
        os << "  -> Aderenta optima! (Performanta usor crescuta)\n";
    }
    return os;
}