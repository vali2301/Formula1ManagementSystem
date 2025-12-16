#include "StatisticiCampionat.h"
#include <iostream>
#include <iomanip>

StatisticiCampionat& StatisticiCampionat::getInstanta() {
    static StatisticiCampionat instanta;
    return instanta;
}



void StatisticiCampionat::inregistreazaPilotPePodium(const std::string& numePilot, int pozitie) {
    if (pozitie == 1)
        totalVictoriiPerPilot[numePilot]++;

    if (pozitie >= 1 && pozitie <= 3)
        totalPodiumuriPerPilot[numePilot]++;
}

void StatisticiCampionat::inregistreazaPolePosition(const std::string& numePilot) {
    int& pole = totalPolePositionsPerPilot[numePilot];
    pole++;

    if (pole > maxPolePositions) {
        maxPolePositions = pole;
        pilotCuCeleMaiMultePole = numePilot;
    }
}

void StatisticiCampionat::inregistreazaAbandon(const std::string& numePilot) {
    totalDNFsPerPilot[numePilot]++;
}

void StatisticiCampionat::afiseazaStatisticiSezon() const {

    std::cout << "Pilot cu cele mai multe pole positions: "
              << pilotCuCeleMaiMultePole << " (" << maxPolePositions << ")\n\n";

    std::cout << std::left << std::setw(20) << "Pilot"
              << std::setw(12) << "Victorii"
              << std::setw(12) << "Podiumuri"
              << "DNF\n";
    std::cout << std::string(50, '-') << "\n";

    for (const auto& [pilot, victorii] : totalVictoriiPerPilot) {
        int podiumuri = totalPodiumuriPerPilot.count(pilot)
                        ? totalPodiumuriPerPilot.at(pilot)
                        : 0;
        int dnf = totalDNFsPerPilot.count(pilot)
                  ? totalDNFsPerPilot.at(pilot)
                  : 0;

        std::cout << std::left << std::setw(20) << pilot
                  << std::setw(12) << victorii
                  << std::setw(12) << podiumuri
                  << dnf << "\n";
    }

    if (totalVictoriiPerPilot.empty()) {
        std::cout << "Nu exista date statistice.\n";
    }

    std::cout << "==============================================\n";
}
