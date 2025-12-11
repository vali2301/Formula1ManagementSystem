#include "CursaF1.h"
#include <iostream>
#include <algorithm>
#include <random>

CursaF1::CursaF1(std::string locatie, std::vector<Echipa> e, Campionat &c)
    : Eveniment(locatie), echipe(e), puncteF1{25,18,15,12,10,8,6,4,2,1}, campionat(c)
{}

CursaF1::CursaF1(const CursaF1& other)
    : Eveniment(other), echipe(other.echipe), puncteF1(other.puncteF1), campionat(other.campionat) {}

CursaF1& CursaF1::operator=(const CursaF1& other) {
    if (this != &other) {
        Eveniment::operator=(other);
        echipe = other.echipe;
        puncteF1 = other.puncteF1;
    }
    return *this;
}

void CursaF1::simuleazaEveniment() {
    std::cout << "\n[SIMULARE] Cursa F1 din " << getNume() << " a inceput!\n";
    campionat.simulareVreme();
}

int CursaF1::punctePilotCursa(const std::string &pilotAles, std::map<std::string, int> &scoruri) {
    std::vector<Pilot> totiPiloti;
    for (auto &echipa: echipe)
        for (const auto &p: echipa.getPiloti())
            totiPiloti.push_back(p);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);

    std::uniform_int_distribution<> distAbandon(0, 9);
    std::vector<std::string> abandonuri;

    for (auto it = totiPiloti.begin(); it != totiPiloti.end();) {
        if (distAbandon(gen) == 0) {
            abandonuri.push_back(it->getNume());
            it = totiPiloti.erase(it);
        } else {
            ++it;
        }
    }

    std::cout << "Clasament final pentru " << getNume() << ":\n";

    std::uniform_real_distribution<> distTimp(75.0, 80.0);
    std::vector<double> timpi;
    for (size_t i = 0; i < totiPiloti.size(); ++i)
        timpi.push_back(distTimp(gen) + i * 0.5);

    std::sort(timpi.begin(), timpi.end());
    double timpPrimul = timpi[0];

    int punctePilot = 0;
    std::vector<std::pair<std::string, double> > rezultate;
    clasamentFinal.clear();

    for (size_t i = 0; i < totiPiloti.size(); ++i) {
        int puncte = (i < puncteF1.size()) ? puncteF1[i] : 0;
        totiPiloti[i].adaugaPuncte(puncte);
        scoruri[totiPiloti[i].getNume()] += puncte;
        rezultate.push_back({totiPiloti[i].getNume(), timpi[i]});
        clasamentFinal.push_back({totiPiloti[i].getNume(), puncte});

        if (totiPiloti[i].getNume() == pilotAles)
            punctePilot = puncte;
    }

    int randomBonus = gen() % totiPiloti.size();
    std::string pilotBonus = totiPiloti[randomBonus].getNume();
    scoruri[pilotBonus] += 1;

    for (size_t i = 0; i < rezultate.size(); ++i) {
        double diferenta = rezultate[i].second - timpPrimul;
        std::cout << i + 1 << ". " << rezultate[i].first
                << " - " << puncteF1[std::min(i, puncteF1.size() - 1)]
                << " pct | Timp: " << rezultate[i].second
                << " min | +" << diferenta << "s\n";
    }

    if (!abandonuri.empty()) {
        std::cout << "\nAbandonuri (DNF):\n";
        for (const auto &nume: abandonuri)
            std::cout << "- " << nume << " (DNF)\n";
    }

    std::cout << "\nCel mai rapid tur: " << pilotBonus << " (+1 punct bonus)\n";

    auto itFinal = std::find_if(rezultate.begin(), rezultate.end(),
                                [&](const auto &x) { return x.first == pilotAles; });

    if (itFinal != rezultate.end())
        std::cout << "\nPilotul tau (" << pilotAles << ") a terminat pe locul "
                << (itFinal - rezultate.begin() + 1)
                << " si a obtinut " << punctePilot << " puncte.\n";

    return punctePilot;
}


Eveniment* CursaF1::clone() const {
    return new CursaF1(*this);
}

void CursaF1::afisareVirtuala() const {
    std::cout << "Tip: Cursa Principala F1\n";
    std::cout << "Locatie: " << getNume() << "\n";
    std::cout << "Echipe: " << echipe.size() << "\n";
}

std::ostream &operator<<(std::ostream &os, const CursaF1 &c) {
    os << "Cursa: " << c.getNume() << "\n";
    os << "Echipe participante:\n";
    for (const auto &e: c.echipe)
        os << e << "\n";
    return os;
}

double CursaF1::calculeazaRiscAbandon() const {
    double riscBaza = 0.10;
    double riscSuplimentar = 0.0;

    if (getNume().find("Monaco") != std::string::npos ||
        getNume().find("Spa") != std::string::npos ||
        getNume().find("Las Vegas") != std::string::npos) {

        riscSuplimentar += 0.05;
        std::cout << "[Risc Cursa] +5% risc pentru viraje stradale/periculoase.\n";

        } else if (getNume().find("Monza") != std::string::npos) {

            riscSuplimentar += 0.03; // Solicitare mare a motorului
            std::cout << "[Risc Cursa]+ 3% risc pentru solicitare mare a motorului.\n";
        }

    if (rand() % 100 < 20) {
        riscSuplimentar += 0.08;
        std::cout << "[Risc Cursa] +8% risc din cauza conditiilor meteo precare.\n";
    }

    double riscFinal = riscBaza + riscSuplimentar;
    return std::min(riscFinal, 0.50);
}