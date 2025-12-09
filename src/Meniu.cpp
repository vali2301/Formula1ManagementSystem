#include "Meniu.h"
#include <iostream>
#include <limits>
#include <memory>
#include "CursaF1.h"
#include "Calificari.h"
#include "RecunoastereCircuit.h"


void Meniu::ruleaza() {
    Campionat campionat;

    std::vector<Echipa> echipe = {
        Echipa("Red Bull", {"Verstappen", "Tsunoda"}),
        Echipa("Ferrari", {"Leclerc", "Hamilton"}),
        Echipa("Mercedes", {"Russell", "Antonelli"}),
        Echipa("Mclaren", {"Norris", "Piastri"}),
        Echipa("Aston Martin", {"Alonso", "Stroll"}),
        Echipa("Alpine", {"Colapinto", "Gasly"}),
        Echipa("Williams", {"Albon", "Sainz"}),
        Echipa("RB", {"Lawson", "Hadjar"}),
        Echipa("Kick Sauber", {"Hulkenberg", "Bortoleto"}),
        Echipa("Haas", {"Ocon", "Bearman"})
    };

    int indexEchipa = alegeEchipa(echipe);
    Echipa echipaSelectata = echipe[indexEchipa];

    std::string pilotAles = alegePilot(echipaSelectata);

    std::cout << "Ai ales pilotul: " << pilotAles << "\n";

    std::vector<std::string> circuite = {
        "Australia", "China", "Japonia", "Bahrain", "Arabia Saudita", "Miami", "Imola", "Monaco", "Spania",
        "Canada", "Austria", "Silverstone", "Spa", "Hungaroring", "Olanda", "Monza", "Azerbaijan", "Singapore", "SUA",
        "Mexic", "interlagos",
        "Las Vegas", "Qatar", "Abu Dhabi"
    };
    std::map<std::string, int> scoruri;

    for (size_t i = 0; i < circuite.size(); ++i) {
        std::string numeCircuit = circuite[i];

        std::vector<std::unique_ptr<Eveniment> > weekend;

        weekend.push_back(
            std::make_unique<RecunoastereCircuit>(numeCircuit, "Sesiune de orientare (Viteza redusa).", echipe));

        weekend.push_back(std::make_unique<Calificari>(numeCircuit, campionat, echipe));

        CursaF1 cursa(numeCircuit, echipe, campionat);


        std::cout << "\n\n************************************************\n";
        std::cout << " INCEPE WEEKEND-UL DE CURSE: " << numeCircuit << "\n";
        std::cout << "************************************************\n";

        for (const auto &ev: weekend) {
            ev->afiseazaDetaliiEveniment();
            ev->simuleazaEveniment();

            if (auto *calif = dynamic_cast<Calificari *>(ev.get())) {
                calif->afiseazaGrilaStart();
            }
        }

        std::cout << "\n--- START CURSA PRINCIPALA ---\n";
        cursa.simuleazaEveniment();
        cursa.punctePilotCursa(pilotAles, scoruri);

        if (i < circuite.size() - 1) {
            bool continua = false;
            while (!continua) {
                int opt = campionat.meniuCampionat();

                if (opt == 1) {
                    continua = true;
                } else if (opt == 2) campionat.afiseazaClasamentGeneral(scoruri);
                else if (opt == 3) campionat.afisareRegulament();
                else if (opt == 4) campionat.afisareCircuitInfo();
                else if (opt == 5) campionat.simularePitStop();
                else if (opt == 6) campionat.simulareSafetyCar();
                else if (opt == 7) {
                    std::cout << "Campionatul s-a incheiat!\n";
                    return;
                }
            }
        }
    }

    campionat.afiseazaClasamentGeneral(scoruri);
    campionat.afiseazaClasamentEchipe(scoruri);

    campionat.afiseazaCelMaiConstantPilot(scoruri, circuite.size());
}

int Meniu::alegeEchipa(const std::vector<Echipa> &echipe) {
    std::cout << "Alege o echipa:\n";

    for (size_t i = 0; i < echipe.size(); ++i)
        std::cout << i + 1 << ". " << echipe[i].getNume() << "\n";

    int alegere;
    std::cin >> alegere;

    while (alegere < 1 || alegere > (int) echipe.size()) {
        std::cout << "Optiune invalida. Reincearca: ";
        std::cin >> alegere;
    }

    return alegere - 1;
}

std::string Meniu::alegePilot(Echipa &echipa) {
    auto piloti = echipa.getPiloti();

    std::cout << "Alege un pilot:\n";
    for (size_t i = 0; i < piloti.size(); ++i)
        std::cout << i + 1 << ". " << piloti[i].getNume() << "\n";

    int alegere;
    std::cin >> alegere;

    while (alegere < 1 || alegere > (int) piloti.size()) {
        std::cout << "Optiune invalida. Reincearca: ";
        std::cin >> alegere;
    }

    return piloti[alegere - 1].getNume();
}
