#include "SprintRace.h"
#include <iostream>
#include <algorithm>
#include <random>

SprintRace::SprintRace(const std::string &locatie, std::vector<Echipa> e, int agresivitate)
    : Eveniment("Sprint Race - " + locatie), echipe(std::move(e)),
      puncteSprint{8, 7, 6, 5, 4, 3, 2, 1}, agresivitatePiloti(agresivitate) {
}

void SprintRace::simuleazaEveniment() {
    std::cout << "\n[SIMULARE] " << getNume() << " incepe! (Distanta redusa: 100km)\n"; //100km aprox ca nr de lap uri depinde de circuit
    std::cout << "Nivel de agresivitate setat pentru piloti: " << agresivitatePiloti << "/10\n";
}

double SprintRace::calculeazaRiscAbandon() const {
    double riscBaza = 0.08;
    double riscAgresivitate = (agresivitatePiloti * 0.02);
    return std::min(riscBaza + riscAgresivitate, 0.40);
}

void SprintRace::acordaPuncteSprint(std::map<std::string, int> &scoruri) {
    std::cout << "--- Rezultate Sprint (Top 8 primesc puncte) ---\n";

    std::vector<std::string> totiPiloti;
    for (const auto &ech: echipe) {
        for (const auto &p: ech.getPiloti()) {
            totiPiloti.push_back(p.getNume());
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);

    for (size_t i = 0; i < puncteSprint.size() && i < totiPiloti.size(); ++i) {
        scoruri[totiPiloti[i]] += puncteSprint[i];
        std::cout << i + 1 << ". " << totiPiloti[i] << " + " << puncteSprint[i] << " pct\n";
    }
}

Eveniment *SprintRace::clone() const {
    return new SprintRace(*this);
}

void SprintRace::afisareVirtuala() const {
    std::cout << "Tip: Sprint Race (Format Scurt)\n";
}
