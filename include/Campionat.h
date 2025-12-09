#ifndef CAMPIONAT_H
#define CAMPIONAT_H

#include <map>
#include <string>

class Campionat {
private:
    static int curseTotalDesfasurate;

public:
    void afiseazaClasamentEchipe(const std::map<std::string, int> &scoruri);

    void afiseazaCelMaiConstantPilot(const std::map<std::string, int> &scoruri, int curseTotale);

    static void incrementeazaCurseTotal();

    static void afiseazaStatisticaCampionat();

    int meniuCampionat();

    void afiseazaClasamentGeneral(const std::map<std::string, int> &scoruriExistente);

    void afisareRegulament();

    void simulareVreme();

    void afisareCircuitInfo();

    void simularePitStop();

    void simulareSafetyCar();
};

#endif
