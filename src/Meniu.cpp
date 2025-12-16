#include "Meniu.h"
#include <iostream>
#include "Exceptii.h"
#include <limits>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "CursaF1.h"
#include "Calificari.h"
#include "RecunoastereCircuit.h"
#include  <StatisticiCampionat.h>
#include <fstream>
#include <FileManager.h>

void Meniu::ruleaza() {
    Campionat campionat;

    auto echipe = FileManager::citesteEchipe();
    auto circuite = FileManager::citesteCircuite();

    int indexEchipa = alegeEchipa(echipe);
    Echipa echipaSelectata = echipe[indexEchipa];

    std::string pilotAles = alegePilot(echipaSelectata);

    std::cout << "Ai ales pilotul: " << pilotAles << "\n";

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

            if (const auto *calif = dynamic_cast<Calificari *>(ev.get())) {
                calif->afiseazaGrilaStart();

                double riscAbandon = ev->calculeazaRiscAbandon();
                std::cout << ">>> RISC DINAMIC DE ABANDON (Calificari): " << (riscAbandon * 100) << "%\n";
            }

            if (dynamic_cast<RecunoastereCircuit *>(ev.get())) {
                double riscAbandon = ev->calculeazaRiscAbandon();
                std::cout << ">>> RISC DINAMIC DE ABANDON (Recunoastere): " << (riscAbandon * 100) << "%\n";
                std::cout << "------------------------------------------------\n";
            }
        }


        std::cout << "\n--- START CURSA PRINCIPALA ---\n";
        cursa.simuleazaEveniment();
        cursa.punctePilotCursa(pilotAles, scoruri);

        double riscAbandonCursa = cursa.calculeazaRiscAbandon();
        std::cout << "\n>>> RISC DINAMIC DE ABANDON (Cursa F1): " << (riscAbandonCursa * 100) << "%\n";
        std::cout << "------------------------------------------------\n";
        Campionat::incrementeazaCurseTotal();

        Campionat::afiseazaStatisticaCampionat();

        if (i < circuite.size() - 1) {
            bool continua = false;
            while (!continua) {
                try {
                    int opt = Campionat::meniuCampionat();
                    if (opt == 1) {
                        continua = true;
                    } else if (opt == 2) Campionat::afiseazaClasamentGeneral(scoruri);
                    else if (opt == 3) Campionat::afisareRegulament();
                    else if (opt == 4) Campionat::afisareCircuitInfo();
                    else if (opt == 5) Campionat::simularePitStop();
                    else if (opt == 6) Campionat::simulareSafetyCar();
                    else if (opt == 7) {
                        std::cout << "Campionatul s-a incheiat!\n";
                        return;
                    }
                } catch (const EroareOptiuneMeniu &e) {
                    std::cerr << "\n[EROARE MENIU] Exceptie: " << e.what() << ". Campionatul s-a terminat fortat.\n";
                    return;
                }
                catch (const std::exception &e) {
                    std::cout << "\n[EROARE CAMPIONAT] " << e.what() << "\n";
                }
            }
        }
    }

    std::cout << "\n\n======== CLASAMENT FINAL CAMPIONAT ========\n";
    Campionat::afiseazaClasamentGeneral(scoruri);
    Campionat::afiseazaClasamentEchipe(scoruri);
    Campionat::afiseazaStatisticaCampionat();
    Campionat::afiseazaCelMaiConstantPilot(scoruri, circuite.size());
    StatisticiCampionat::getInstanta()
    .afiseazaStatisticiSezon();
}

int Meniu::alegeEchipa(const std::vector<Echipa> &echipe) {
    std::cout << "\nAlege o echipa:\n";

    for (size_t i = 0; i < echipe.size(); ++i)
        std::cout << i + 1 << ". " << echipe[i].getNume() << "\n";

    int alegere;
    std::cout << "Alegere: ";

    if (!(std::cin >> alegere) || alegere < 1 || alegere > static_cast<int>(echipe.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw EroarePilotInvalid("Selectia echipei este invalida sau in afara intervalului.");
    }

    return alegere - 1;
}

std::string Meniu::alegePilot(Echipa &echipa) {
    auto piloti = echipa.getPiloti();

    std::cout << "\nAlege un pilot:\n";
    for (size_t i = 0; i < piloti.size(); ++i)
        std::cout << i + 1 << ". " << piloti[i].getNume() << "\n";

    int alegere;
    std::cout << "Alegere: ";

    if (!(std::cin >> alegere) || alegere < 1 || alegere > static_cast<int>(piloti.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw EroarePilotInvalid("Selectia pilotului este invalida sau in afara intervalului.");
    }

    return piloti[alegere - 1].getNume();
}
