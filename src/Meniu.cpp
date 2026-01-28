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
#include "StatisticiCampionat.h"
#include <fstream>
#include "FileManager.h"
#include "SprintRace.h"
#include "EvenimentFactory.h"
#include "ManagerPerformanta.h"

void Meniu::ruleaza() {
    Campionat campionat;

    auto echipe = FileManager::citesteEchipe();
    auto circuite = FileManager::citesteCircuite();

    int indexEchipa = alegeEchipa(echipe);
    Echipa echipaSelectata = echipe[indexEchipa];
    std::string pilotAles = alegePilot(echipaSelectata);

    std::cout << "Ai ales pilotul: " << pilotAles << "\n";

    std::map<std::string, int> scoruri;

    ManagerPerformanta<double> istoricTimpi("Analiza Timpi Calificari");
    ManagerPerformanta<int> istoricPuncte("Evolutie Puncte Pilot");

    std::unique_ptr<EvenimentFactory> factoryRec = std::make_unique<FactoryRecunoastere>();
    std::unique_ptr<EvenimentFactory> factoryCal = std::make_unique<FactoryCalificari>();
    std::unique_ptr<EvenimentFactory> factorySpr = std::make_unique<FactorySprint>();
    std::unique_ptr<EvenimentFactory> factoryCur = std::make_unique<FactoryCursa>();

    for (size_t i = 0; i < circuite.size(); ++i) {
        std::string numeCircuit = circuite[i];
        std::vector<std::unique_ptr<Eveniment>> weekend;

        weekend.push_back(factoryRec->creeazaEveniment(numeCircuit, echipe, campionat));
        weekend.push_back(factoryCal->creeazaEveniment(numeCircuit, echipe, campionat));

        if (numeCircuit == "Austria" || numeCircuit == "Interlagos" || numeCircuit == "China" ||
            numeCircuit == "Miami" || numeCircuit == "SUA") {
            weekend.push_back(factorySpr->creeazaEveniment(numeCircuit, echipe, campionat));
        }

        std::cout << "\n\n************************************************\n";
        std::cout << " INCEPE WEEKEND-UL DE CURSE: " << numeCircuit << "\n";
        std::cout << "************************************************\n";

        for (const auto &ev : weekend) {
            ev->afiseazaDetaliiEveniment();
            ev->simuleazaEveniment();

            if (auto *sprintPtr = dynamic_cast<SprintRace *>(ev.get())) {
                sprintPtr->acordaPuncteSprint(scoruri);
            }

            if (const auto *calif = dynamic_cast<Calificari *>(ev.get())) {
                calif->afiseazaGrilaStart();
                double timpPole = 71.0 + (rand() % 2000 / 1000.0);
                istoricTimpi.adaugaRezultat(timpPole);
                comparaRezultate<double>(71.200, timpPole, "Timp Referinta vs Pole Actual");
            }
        }

        std::cout << "\n--- START CURSA PRINCIPALA ---\n";
        auto cursaObj = factoryCur->creeazaEveniment(numeCircuit, echipe, campionat);
        cursaObj->simuleazaEveniment();

        int puncteRunda = dynamic_cast<CursaF1*>(cursaObj.get())->punctePilotCursa(pilotAles, scoruri);
        istoricPuncte.adaugaRezultat(puncteRunda);

        comparaRezultate<int>(25, puncteRunda, "Maxim Puncte vs Puncte Pilot");

        Campionat::incrementeazaCurseTotal();
        Campionat::afiseazaStatisticaCampionat();

        if (i < circuite.size() - 1) {
            bool continua = false;
            while (!continua) {
                try {
                    int opt = Campionat::meniuCampionat();
                    if (opt == 1) continua = true;
                    else if (opt == 2) Campionat::afiseazaClasamentGeneral(scoruri);
                    else if (opt == 3) Campionat::afisareRegulament();
                    else if (opt == 4) Campionat::afisareCircuitInfo();
                    else if (opt == 5) Campionat::simularePitStop();
                    else if (opt == 6) Campionat::simulareSafetyCar();
                    else if (opt == 7) return;
                } catch (const EroareOptiuneMeniu &e) {
                    return;
                } catch (const std::exception &e) {
                    std::cout << "\n[EROARE] " << e.what() << "\n";
                }
            }
        }
    }

    istoricTimpi.afiseazaRaport();
    istoricPuncte.afiseazaRaport();

    std::cout << "\n\n======== CLASAMENT FINAL CAMPIONAT ========\n";
    Campionat::afiseazaClasamentGeneral(scoruri);
    Campionat::afiseazaClasamentEchipe(scoruri);
    StatisticiCampionat::getInstanta().afiseazaStatisticiSezon();
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
        throw EroarePilotInvalid("Selectia echipei este invalida.");
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
        throw EroarePilotInvalid("Selectia pilotului este invalida.");
    }
    return piloti[alegere - 1].getNume();
}