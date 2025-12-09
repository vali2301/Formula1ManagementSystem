#include "Campionat.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <random>
#include <limits>

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
    while (true) {
        if (std::cin >> opt && opt >= 1 && opt <= 7)
            return opt;
        std::cout << "Optiune invalida! Alege 1 - 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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
    std::cout << "Locul 1 – 25 puncte\n";
    std::cout << "Locul 2 – 18 puncte\n";
    std::cout << "Locul 3 – 15 puncte\n";
    std::cout << "Locul 4 – 12 puncte\n";
    std::cout << "Locul 5 – 10 puncte\n";
    std::cout << "Locul 6 – 8 puncte\n";
    std::cout << "Locul 7 – 6 puncte\n";
    std::cout << "Locul 8 – 4 puncte\n";
    std::cout << "Locul 9 – 2 puncte\n";
    std::cout << "Locul 10 – 1 punct\n";
}

void Campionat::simulareVreme() {
    std::vector<std::string> conditii = {"Soare", "Ploaie", "Nori", "Ceata"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d(0, 3);
    std::string vreme = conditii[d(gen)];

    std::cout << "\nConditii meteo: " << vreme << "\n";
}

void Campionat::afisareCircuitInfo() {
    std::map<std::string, std::string> info = {
        {"Australia", "Circuit semi-stradal in Melbourne, faimos pentru sectiunile rapide si aderenta scazuta."},
        {"China", "Circuit cu design unic, notabil pentru virajele 1 si 2 in spirala."},
        {"Japonia", "Suzuka: Circuit tehnic, celebru pentru S-uri si cursa in stil traditional F1."},
        {"Bahrain", "Circuit in desert, renumit pentru franele puternice si cursa nocturna."},
        {"Arabia Saudita", "Jeddah: Cel mai rapid circuit stradal din lume, cu vizibilitate redusa."},
        {"Miami", "Circuit stradal nou, construit in jurul stadionului Hard Rock."},
        {"Imola", "Circuit istoric in Italia, cu sectiuni inguste si traditionale."},
        {"Monaco", "Circuit urban, cel mai lent si tehnic din calendar."},
        {"Spania", "Circuit near Barcelona, adesea folosit pentru teste, cu aerodinamica solicitanta."},
        {"Canada", "Circuit semi-stradal rapid, celebru pentru 'Zidul Campionilor'."},
        {"Austria", "Red Bull Ring: Circuit scurt si rapid, cu multe schimbari de nivel."},
        {"Silverstone", "Marea Britanie: Circuit rapid, cu viraje faimoase (Copse, Maggotts)."},
        {"Spa", "Belgia: Cel mai lung circuit – 7 km, faimos pentru virajul Eau Rouge."},
        {"Hungaroring", "Circuit lent si virajat, comparat cu unul de karting, dificil pentru depasiri."},
        {"Olanda", "Zandvoort: Circuit retro pe dune, cu viraje inclinate (banking) solicitante."},
        {"Monza", "Italia: 'Templul Vitezei', circuit cu cea mai mare viteza medie."},
        {"Azerbaijan", "Circuit stradal in Baku, cu o sectiune de castel ingusta si o linie dreapta lunga."},
        {"Singapore", "Circuit stradal nocturn, extrem de solicitant fizic datorita caldurii si umiditatii."},
        {"SUA", "COTA: Circuit modern in Texas, cu o combinatie de viraje rapide si tehnice."},
        {"Mexic", "Autodromo Hermanos Rodriguez: Altitudine mare, aer rarefiat si intrarea spectaculoasa prin stadion."},
        {"Interlagos", "Brazilia: Circuit clasic, cu tururi scurte si sectiuni in urcare/coborare."},
        {"Las Vegas", "Circuit stradal nocturn, cu o sectiune de lungime mare pe 'Strip'."},
        {"Qatar", "Lusail: Circuit relativ nou, cu vizibilitate redusa si temperaturi ridicate."},
        {"Abu Dhabi", "Yas Marina: Finala sezonului, cu un hotel impresionant si sectiuni lente si rapide."}
    };

    std::cout << "\n===== CIRCUITE =====\n";
    for (const auto &c: info)
        std::cout << c.first << ": " << c.second << "\n";
}

void Campionat::simularePitStop() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(2.0, 4.5);
    double timp = dist(gen);

    std::cout << "\nPitstop: " << timp << " secunde.\n";
}

void Campionat::simulareSafetyCar() {
    std::cout << "\nSafety Car pe circuit pentru cateva tururi!\n";
}
