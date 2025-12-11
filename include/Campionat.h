#ifndef CAMPIONAT_H
#define CAMPIONAT_H

#include <map>
#include <string>

class Campionat {
private:
    static int curseTotalDesfasurate;

public:
    static void afiseazaClasamentEchipe(const std::map<std::string, int> &scoruri);

    static void afiseazaCelMaiConstantPilot(const std::map<std::string, int> &scoruri, int curseTotale);

    static void incrementeazaCurseTotal();

    static void afiseazaStatisticaCampionat();

    static int meniuCampionat();

    static void afiseazaClasamentGeneral(const std::map<std::string, int> &scoruriExistente);

    static void afisareRegulament();

    static void simulareVreme();

    static void afisareCircuitInfo();

    static void simularePitStop();

    static void simulareSafetyCar();
};

#endif
