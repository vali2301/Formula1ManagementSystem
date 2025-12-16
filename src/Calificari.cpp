#include "Calificari.h"
#include <iostream>
#include <algorithm>
#include <random>

Calificari::Calificari(const std::string &n, Campionat &c, const std::vector<Echipa> &echipe)
    : Eveniment(n), campionat(c) {
    for (const auto &echipa: echipe) {
        for (const auto &pilot: echipa.getPiloti()) {
            listaPiloti.push_back(pilot.getNume());
        }
    }
}

Calificari::~Calificari() = default;

Calificari::Calificari(const Calificari &other)
    : Eveniment(other), campionat(other.campionat), listaPiloti(other.listaPiloti),
      timpiCalificari(other.timpiCalificari), grilaStart(other.grilaStart) {
}

Calificari &Calificari::operator=(const Calificari &other) {
    if (this != &other) {
        Eveniment::operator=(other);
        listaPiloti = other.listaPiloti;
        timpiCalificari = other.timpiCalificari;
        grilaStart = other.grilaStart;
    }
    return *this;
}

void Calificari::simuleazaEveniment() {
    std::cout << "\n[SIMULARE] Calificari (" << getNume() << ")\n";
    //campionat.simulareVreme();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distTimp(70.0, 75.0);

    timpiCalificari.clear();
    for (const auto &numePilot: listaPiloti) {
        timpiCalificari[numePilot] = distTimp(gen);
    }

    std::vector<std::pair<std::string, double> > clasament(timpiCalificari.begin(), timpiCalificari.end());
    std::sort(clasament.begin(), clasament.end(),
              [](const auto &a, const auto &b) { return a.second < b.second; });

    grilaStart.clear();
    std::cout << "Clasament Calificari:\n";
    for (size_t i = 0; i < clasament.size(); ++i) {
        grilaStart.push_back(clasament[i].first);
        std::cout << i + 1 << ". " << clasament[i].first << " (" << clasament[i].second << "s)\n";
    }
}

Eveniment *Calificari::clone() const {
    return new Calificari(*this);
}

void Calificari::afisareVirtuala() const {
    std::cout << "Tip: Calificari\n";
    std::cout << "Sesiune: " << getNume() << "\n";
}

const std::vector<std::string> &Calificari::getGrilaStart() const {
    return grilaStart;
}

void Calificari::afiseazaGrilaStart() const {
    if (grilaStart.empty()) {
        std::cout << "Grila de start nu a fost inca stabilita.\n";
        return;
    }
    std::cout << "\n--- Grila de Start ---\n";
    for (size_t i = 0; i < grilaStart.size(); ++i) {
        std::cout << i + 1 << ". " << grilaStart[i] << "\n";
    }
}

double Calificari::calculeazaRiscAbandon() const {
    double riscBaza = 0.05;
    double riscSuplimentar = 0.0;

    if (getNume().find("Japonia") != std::string::npos ||
        getNume().find("Silverstone") != std::string::npos  || getNume().find("Monaco") != std::string::npos
        || getNume().find("Singapore") != std::string::npos || getNume().find("Azerbaijan") != std::string::npos
        || getNume().find("Las Vegas") != std::string::npos) {

        riscSuplimentar += 0.04; //
        std::cout << "+4% risc pentru erori de pilotaj pe circuite rapide.\n";
        }

    if (rand() % 10 == 0) {
        riscSuplimentar += 0.05;
        std::cout << "+5% risc, pilotul forteaza peste limita.\n";
    }

    return riscBaza + riscSuplimentar;
}