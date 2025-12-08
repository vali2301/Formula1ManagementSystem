#include "Cursa.h"
#include <iostream>
#include <algorithm>
#include <random>

Cursa::Cursa(std::string l, std::vector<Echipa> e, Campionat &c)
    : locatie(l), echipe(e), campionat(c), puncteF1{25, 18, 15, 12, 10, 8, 6, 4, 2, 1} {
}


int Cursa::punctePilotCursa(const std::string &pilotAles, std::map<std::string, int> &scoruri) {
    std::vector<Pilot> totiPiloti;
    for (auto &echipa: echipe)
        for (const auto &p: echipa.getPiloti())
            totiPiloti.push_back(p);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);

    std::cout << "\nCursa din " << locatie << " a inceput!\n\n";
    campionat.simulareVreme();

    std::uniform_int_distribution<> distAbandon(0, 9); //10%
    std::vector<std::string> abandonuri;

    for (auto it = totiPiloti.begin(); it != totiPiloti.end();) {
        if (distAbandon(gen) == 0) {
            abandonuri.push_back(it->getNume());
            it = totiPiloti.erase(it);
        } else {
            ++it;
        }
    }

    std::cout << "Clasament final pentru " << locatie << ":\n";

    std::uniform_real_distribution<> distTimp(75.0, 80.0);
    std::vector<double> timpi;
    for (size_t i = 0; i < totiPiloti.size(); ++i)
        timpi.push_back(distTimp(gen) + i * 0.5);

    std::sort(timpi.begin(), timpi.end());
    double timpPrimul = timpi[0];

    int punctePilot = 0;
    std::vector<std::pair<std::string, double> > rezultate;

    for (size_t i = 0; i < totiPiloti.size(); ++i) {
        int puncte = (i < puncteF1.size()) ? puncteF1[i] : 0;
        totiPiloti[i].adaugaPuncte(puncte);
        scoruri[totiPiloti[i].getNume()] += puncte;
        rezultate.push_back({totiPiloti[i].getNume(), timpi[i]});

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


std::ostream &operator<<(std::ostream &os, const Cursa &c) {
    os << "Cursa: " << c.locatie << "\n";
    os << "Echipe participante:\n";
    for (const auto &e: c.echipe)
        os << e << "\n";
    return os;
}
