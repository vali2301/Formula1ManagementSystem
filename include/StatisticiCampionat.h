#ifndef STATISTICI_CAMPIONAT_H
#define STATISTICI_CAMPIONAT_H

#include <string>
#include <map>

class StatisticiCampionat {
private:

    std::map<std::string, int> totalVictoriiPerPilot;
    std::map<std::string, int> totalPodiumuriPerPilot;
    std::map<std::string, int> totalDNFsPerPilot;
    std::map<std::string, int> totalPolePositionsPerPilot;

    std::string pilotCuCeleMaiMultePole = "N/A";
    int maxPolePositions = 0;

    StatisticiCampionat() = default;

public:
    static StatisticiCampionat &getInstanta();

    StatisticiCampionat(const StatisticiCampionat &) = delete;

    StatisticiCampionat &operator=(const StatisticiCampionat &) = delete;

    void inregistreazaPilotPePodium(const std::string &numePilot, int pozitie);

    void inregistreazaPolePosition(const std::string &numePilot);

    void inregistreazaAbandon(const std::string &numePilot);

    void afiseazaStatisticiSezon() const;
};

#endif
