#include "EvenimentFactory.h"
#include "CursaF1.h"
#include "Calificari.h"
#include "SprintRace.h"
#include "RecunoastereCircuit.h"

std::unique_ptr<Eveniment> FactoryCursa::creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const {
    return std::make_unique<CursaF1>(locatie, echipe, camp);
}

std::unique_ptr<Eveniment> FactoryCalificari::creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const {
    return std::make_unique<Calificari>(locatie, camp, echipe);
}

std::unique_ptr<Eveniment> FactorySprint::creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& /*camp*/) const {
    return std::make_unique<SprintRace>(locatie, echipe, 5); // 5 este agresivitatea default
}

std::unique_ptr<Eveniment> FactoryRecunoastere::creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& /*camp*/) const {
    return std::make_unique<RecunoastereCircuit>(locatie, "Sesiune de recunoastere", echipe);
}