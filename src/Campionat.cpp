#include "Campionat.h"
#include "Exceptii.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <random>
#include <limits>
#include <fstream>

int Campionat::curseTotalDesfasurate = 0;

void Campionat::afiseazaClasamentEchipe(const std::map<std::string, int> &scoruri) {
    std::map<std::string, std::string> pilotEchipa = {
        {"Verstappen", "Red Bull"}, {"Tsunoda", "Red Bull"},
        {"Leclerc", "Ferrari"}, {"Hamilton", "Ferrari"},
        {"Russell", "Mercedes"}, {"Antonelli", "Mercedes"},
        {"Norris", "Mclaren"}, {"Piastri", "Mclaren"},
        {"Alonso", "Aston Martin"}, {"Stroll", "Aston Martin"},
        {"Colapinto", "Alpine"}, {"Gasly", "Alpine"},
        {"Albon", "Williams"}, {"Sainz", "Williams"},
        {"Lawson", "RB"}, {"Hadjar", "RB"},
        {"Hulkenberg", "Kick Sauber"}, {"Bortoleto", "Kick Sauber"},
        {"Ocon", "Haas"}, {"Bearman", "Haas"}
    };

    std::map<std::string, int> puncteEchipe;
    for (const auto &p: scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    std::vector<std::pair<std::string, int> > clasamentEchipe(puncteEchipe.begin(), puncteEchipe.end());
    std::sort(clasamentEchipe.begin(), clasamentEchipe.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });

    std::cout << "\n===== CLASAMENT ECHIPE =====\n";
    int poz = 1;
    for (const auto &e: clasamentEchipe)
        std::cout << poz++ << ". " << e.first << " - " << e.second << " puncte\n";
}

void Campionat::afiseazaCelMaiConstantPilot(const std::map<std::string, int> &scoruri, int curseTotale) {
    std::string pilotConstant;
    double ceaMaiMareMedie = 0.0;

    for (const auto &[nume, puncte]: scoruri) {
        double medie = static_cast<double>(puncte) / curseTotale;
        if (medie > ceaMaiMareMedie) {
            ceaMaiMareMedie = medie;
            pilotConstant = nume;
        }
    }

    if (!pilotConstant.empty())
        std::cout << "Cel mai constant pilot: " << pilotConstant
                << " (medie " << ceaMaiMareMedie << " pct/cursa)\n";
    else
        std::cout << "Nu s-a putut determina un pilot constant.\n";
}

int Campionat::meniuCampionat() {
    std::cout << "\nCampionatul continua:\n";
    std::cout << "1. Urmatoarea cursa\n";
    std::cout << "2. Vezi clasamentul general\n";
    std::cout << "3. Regulament\n";
    std::cout << "4. Detalii circuite\n";
    std::cout << "5. Simulare Pitstop\n";
    std::cout << "6. Simulare Safety Car\n";
    std::cout << "7. Iesi din campionat\n";
    std::cout << "Alege o optiune: ";
    int opt;
    int incercari = 0;
    while (incercari < 3) {
        if (std::cin >> opt && opt >= 1 && opt <= 7)
            return opt;

        std::cout << "Optiune invalida! Alege 1 - 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        incercari++;
    }
    throw EroareOptiuneMeniu("Prea multe incercari esuate la selectarea optiunii din meniu.");
}

void Campionat::incrementeazaCurseTotal() {
    curseTotalDesfasurate++;
}

void Campionat::afiseazaStatisticaCampionat() {
    std::cout << "\n[STATISTICI GLOBALE CAMPIONAT]\n";
    std::cout << "Curse de Grand Prix finalizate pana acum: " << curseTotalDesfasurate << "\n";
}

void Campionat::afiseazaClasamentGeneral(const std::map<std::string, int> &scoruriExistente) {
    std::map<std::string, int> scoruri = scoruriExistente;

    std::vector<std::string> totiPiloti = {
        "Verstappen", "Tsunoda", "Leclerc", "Hamilton",
        "Russell", "Antonelli", "Norris", "Piastri",
        "Alonso", "Stroll", "Colapinto", "Gasly",
        "Albon", "Sainz", "Lawson", "Hadjar",
        "Hulkenberg", "Bortoleto", "Ocon", "Bearman"
    };

    for (const auto &nume: totiPiloti)
        if (!scoruri.contains(nume))
            scoruri[nume] = 0;

    std::vector<std::pair<std::string, int> > clasament(scoruri.begin(), scoruri.end());
    std::sort(clasament.begin(), clasament.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });

    std::cout << "\n===== CLASAMENT GENERAL PILOTI =====\n";
    int poz = 1;
    for (const auto &p: clasament)
        std::cout << poz++ << ". " << p.first << " - " << p.second << " puncte\n";
}

void Campionat::afisareRegulament() {
    std::cout << "\n===== REGULAMENT FORMULA 1 =====\n";
    std::cout << "Locul 1 - 25 puncte\n";
    std::cout << "Locul 2 - 18 puncte\n";
    std::cout << "Locul 3 - 15 puncte\n";
    std::cout << "Locul 4 - 12 puncte\n";
    std::cout << "Locul 5 - 10 puncte\n";
    std::cout << "Locul 6 - 8 puncte\n";
    std::cout << "Locul 7 - 6 puncte\n";
    std::cout << "Locul 8 - 4 puncte\n";
    std::cout << "Locul 9 - 2 puncte\n";
    std::cout << "Locul 10 - 1 punct\n";
}

/*void Campionat::simulareVreme() {
    std::vector<std::string> conditii = {"Soare", "Ploaie", "Nori", "Ceata"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, conditii.size() - 1);
    const std::string vreme = conditii[dist(gen)];

    std::cout << "\nConditiile meteo pentru aceasta cursa: " << vreme << "\n";
    if (vreme == " Ploaie") {
        std::cout << "Ploaia poate duce la mai multe abandonuri si timpi mai mari!\n";
    } else if (vreme == " Soare") {
        std::cout << "Conditii perfecte de cursa, performante maxime!\n";
    } else if (vreme == " Ceata") {
        std::cout << "Vizibilitate redusa - risc de erori in viraje!\n";
    } else {
        std::cout << "Temperaturi moderate, performanta constanta.\n";
    }
}
*/

void Campionat::afisareCircuitInfo() {
    std::ifstream fin("../date/circuite_info.txt");
    if (!fin) {
        std::cout << "Nu pot deschide fisierul date/circuite_info.txt\n";
        return;
    }

    std::cout << "\n===== CIRCUITE =====\n";
    std::string linie;

    while (std::getline(fin, linie)) {
        auto pos = linie.find(';');
        if (pos != std::string::npos) {
            std::cout << linie.substr(0, pos)
                      << ": "
                      << linie.substr(pos + 1)
                      << "\n";
        }
    }
}

void Campionat::simularePitStop() {
    std::random_device rd;
    std::mt19937 gen(rd());


    std::uniform_real_distribution<> distTimp(2.0, 4.5);
    double timpFinal = distTimp(gen);

    std::uniform_int_distribution<> distEroare(1, 20);
    int codEroare = distEroare(gen);

    std::cout << "\n=======================================================\n";
    std::cout << "PIT STOP SIMULAT...\n";

    if (codEroare >= 19) {

        timpFinal += 6.0;
        std::cout << "EROARE CRITICA: Roata nu a fost fixata. Timp pierdut major (+6.0s)\n";
        std::cout << "Timp total (cu penalizare): " << timpFinal << " secunde.\n";


        throw EroareSimulareCursa("Pit Stop esuat din cauza unei erori mecanice majore.");

    } else if (codEroare >= 16) {
        timpFinal += 2.0;
        std::cout << "EROARE MEDIE: Schimb lent, probleme cu jack-ul. Timp pierdut (+2.0s)\n";
    }

    if (timpFinal < 2.3) {
        std::cout << "ULTRA RAPID: " << timpFinal << "Performanta mondiala, Echipa de top\n";
    } else if (timpFinal < 3.0) {
        std::cout << "EXCELENT: " << timpFinal << "Foarte rapid, fara greseli.\n";
    } else if (timpFinal < 3.8) {
        std::cout << "DECENT: " << timpFinal << "În media grilei.\n";
    } else {
        std::cout << "LENT: " << timpFinal << "S-a pierdut timp pretios!\n";
    }

    std::cout << "Rezultat simulare: " << timpFinal << " secunde.\n";
    std::cout << "=======================================================\n";
}

void Campionat::simulareSafetyCar() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distTipInterventie(1, 10);
    bool isVSC = (distTipInterventie(gen) <= 3);

    std::uniform_int_distribution<> distDurataSC(4, 8);
    std::uniform_int_distribution<> distDurataVSC(2, 4);
    int durata = isVSC ? distDurataVSC(gen) : distDurataSC(gen);

    std::uniform_int_distribution<> distCauza(1, 5);
    int cauza = distCauza(gen);

    std::cout << "\n=======================================================\n";
    if (isVSC) {
        std::cout << "VIRTUAL SAFETY CAR (VSC) ACTIVAT!\n";
    } else {
        std::cout << "SAFETY CAR (SC) PE CIRCUIT!\n";
    }
    std::cout << "=======================================================\n";

    switch (cauza) {
        case 1:
            std::cout << "Cauza: Un pilot (abandon) a iesit in decor si masina trebuie indepartata de pe pista.\n";
            break;
        case 2:
            std::cout << "Cauza: Resturi periculoase pe circuit (debris) in sectorul 3. Curatare urgenta.\n";
            break;
        case 3:
            std::cout << "Cauza: Conditii meteo periculoase - ploaie intensa in anumite viraje, vizibilitate redusa.\n";
            break;
        case 4:
            std::cout << "Cauza: Incident la boxe: personalul medical este chemat in zona standurilor.\n";
            break;
        case 5:
            std::cout << "Cauza: Eroare a unui sistem de semnalizare pe circuit. Verificare electronica necesara.\n";
            break;
    }

    if (isVSC) {
        std::cout << "\n[REGULAMENT VSC] Pilotii trebuie sa mentina un timp delta pozitiv (viteza redusa).\n";
        std::cout << "Pozitiile raman neschimbate. Pit stop-urile sunt permise, dar sunt penalizate de timpii VSC.\n";
        std::cout << "Durata: VSC va fi activ pentru " << durata << " tururi simulate (pana la indepartarea rapida a pericolului).\n";
    } else {
        std::cout << "\n[REGULAMENT SC] Safety Car aduna tot plutonul. Pilotii se pot dezvolta (unlap).\n";
        std::cout << ">>> FEREASTRA STRATEGICA! Echipele din spate si cele care au nevoie de pneuri noi ar putea intra la boxe (economie de timp majora).\n";
        std::cout << "Durata: SC va ramane pe pista pentru aproximativ " << durata << " tururi.\n";
    }

    std::cout << "\nPilotii trebuie sa mentina distanta. Depasirile sunt interzise pana la linia de start/sosire dupa retragerea SC.\n";

    std::cout << "\n>>> Dupa " << durata << " tururi simulate, "
              << (isVSC ? "cursa revine in ritm normal (GREEN FLAG!)" : "Safety Car se retrage in standuri (RESTART!)") << ".\n";
    std::cout << "=======================================================\n";
}
