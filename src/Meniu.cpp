#include "Meniu.h"
#include <iostream>
#include <limits>
#include "Cursa.h"


void Meniu::ruleaza() {
    Campionat campionat;

    std::vector<Echipa> echipe = {
        Echipa("Red Bull", {"Verstappen", "Tsunoda"}),
        Echipa("Ferrari", {"Leclerc", "Hamilton"}),
        Echipa("Mercedes", {"Russell", "Antonelli"}),
        Echipa("Mclaren", {"Norris", "Piastri"})
    };

    int indexEchipa = alegeEchipa(echipe);
    Echipa echipaSelectata = echipe[indexEchipa];

    std::string pilotAles = alegePilot(echipaSelectata);

    std::cout << "Ai ales pilotul: " << pilotAles << "\n";

    std::vector<std::string> circuite = {"Monaco", "Silverstone", "Spa"};
    std::map<std::string, int> scoruri;

    for (size_t i = 0; i < circuite.size(); ++i) {
        Cursa cursa(circuite[i], echipe, campionat);

        cursa.punctePilotCursa(pilotAles, scoruri);

        if (i < circuite.size() - 1) {
            int opt = campionat.meniuCampionat();
            if (opt == 2) campionat.afiseazaClasamentGeneral(scoruri);
            if (opt == 3) campionat.afisareRegulament();
            if (opt == 4) campionat.afisareCircuitInfo();
            if (opt == 5) campionat.simularePitStop();
            if (opt == 6) campionat.simulareSafetyCar();
            if (opt == 7) {
                std::cout << "Campionatul s-a incheiat!\n";
                return;
            }
        }
    }

    campionat.afiseazaClasamentGeneral(scoruri);
    campionat.afiseazaClasamentEchipe(scoruri);
}

int Meniu::alegeEchipa(const std::vector<Echipa>& echipe) {
    std::cout << "Alege o echipa:\n";

    for (size_t i = 0; i < echipe.size(); ++i)
        std::cout << i + 1 << ". " << echipe[i].getNume() << "\n";

    int alegere;
    std::cin >> alegere;

    while (alegere < 1 || alegere > (int)echipe.size()) {
        std::cout << "Optiune invalida. Reincearca: ";
        std::cin >> alegere;
    }

    return alegere - 1;
}

std::string Meniu::alegePilot(Echipa& echipa) {
    auto piloti = echipa.getPiloti();

    std::cout << "Alege un pilot:\n";
    for (size_t i = 0; i < piloti.size(); ++i)
        std::cout << i + 1 << ". " << piloti[i].getNume() << "\n";

    int alegere;
    std::cin >> alegere;

    while (alegere < 1 || alegere > (int)piloti.size()) {
        std::cout << "Optiune invalida. Reincearca: ";
        std::cin >> alegere;
    }

    return piloti[alegere - 1].getNume();
}
