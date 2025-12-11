#include "RecunoastereCircuit.h"
#include "Echipa.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <map>


RecunoastereCircuit::RecunoastereCircuit(const std::string &n, const std::string &d, const std::vector<Echipa> &echipe)
    : Eveniment(n), detalii(d) {
    for (const auto &echipa: echipe) {
        for (const auto &pilot: echipa.getPiloti()) {
            listaPiloti.push_back(pilot.getNume());
        }
    }
}

RecunoastereCircuit::RecunoastereCircuit(const RecunoastereCircuit &other)
    : Eveniment(other), detalii(other.detalii), listaPiloti(other.listaPiloti),
      timpiRecunoastere(other.timpiRecunoastere) {
}

RecunoastereCircuit &RecunoastereCircuit::operator=(const RecunoastereCircuit &other) {
    if (this != &other) {
        Eveniment::operator=(other);
        detalii = other.detalii;
        listaPiloti = other.listaPiloti;
        timpiRecunoastere = other.timpiRecunoastere;
    }
    return *this;
}

void RecunoastereCircuit::simuleazaEveniment() {
    std::cout << "\n[SIMULARE] Sesiune de Recunoastere a Circuitului (" << getNume() << ")\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distTimp(120.0, 150.0);

    timpiRecunoastere.clear();
    for (const auto &numePilot: listaPiloti) {
        timpiRecunoastere[numePilot] = distTimp(gen);
    }

    std::vector<std::pair<std::string, double> > clasament(timpiRecunoastere.begin(), timpiRecunoastere.end());
    std::sort(clasament.begin(), clasament.end(),
              [](const auto &a, const auto &b) { return a.second < b.second; });

    std::cout << "\nCei mai buni timpi din Recunoastere (Top 5):\n";
    for (size_t i = 0; i < std::min((size_t) 5, clasament.size()); ++i) {
        std::cout << i + 1 << ". " << clasament[i].first << " - " << clasament[i].second << " secunde\n";
    }

    std::cout << "Aceasta sesiune nu influenteaza grila de start.\n";
}


Eveniment *RecunoastereCircuit::clone() const {
    return new RecunoastereCircuit(*this);
}

void RecunoastereCircuit::afisareVirtuala() const {
    std::cout << "Tip: Recunoastere Circuit\n";
    std::cout << "Circuit: " << getNume() << "\n";
    std::cout << "Scurta descriere: " << detalii << "\n";
}

double RecunoastereCircuit::calculeazaRiscAbandon() const {
    double riscBaza = 0.01;
    double riscSuplimentar = 0.0;

    if (getNume().find("Las Vegas") != std::string::npos ||
        getNume().find("Qatar") != std::string::npos) {

        riscSuplimentar += 0.02;
        std::cout << "[Risc Recunoastere] +2% risc din cauza unor probleme de setup pe circuit nou.\n";
        }

    if (rand() % 100 < 15) {
        riscSuplimentar += 0.02;
        std::cout << "[Risc Recunoastere] +2% risc din cauza unor probleme tehnice de inceput de weekend.\n";
    }

    return riscBaza + riscSuplimentar;
}