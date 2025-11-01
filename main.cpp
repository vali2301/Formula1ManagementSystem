#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <limits>
#include <map>
 class Pilot {
     private:
     std::string nume;
     int puncte;

     public:
     explicit Pilot(std::string n) : nume(n), puncte(0) {}
     Pilot(const Pilot&) = default;
     Pilot& operator=(const Pilot&) = default;

    const std::string& getNume() const { return nume; }
     //int getPuncte() const { return puncte; }
     void adaugaPuncte(int p) { puncte += p; }
     //void setPuncte(int p) { puncte = p; }
     void afisare() const {
    std::cout<<"Pilot: "<<nume<<", Puncte: "<<puncte<<std::endl;
     }

     friend std::ostream& operator<<(std::ostream& os, const Pilot& p) {
         os << "Pilot: " << p.nume << " (" << p.puncte << " puncte)";
         return os;
     }

 };


class Echipa {
    private:
    std::string nume;
    std::vector<Pilot> piloti;
    public:
    Echipa(const std::string& n, std::vector<std::string> numePiloti) : nume(n) {
        for(auto &p : numePiloti)
            piloti.emplace_back(p);

    }
    Echipa(const Echipa &e) : nume(e.nume), piloti(e.piloti) {}
    Echipa &operator=(const Echipa &e) {
        if (this != &e) {
            nume = e.nume;
            piloti = e.piloti;
        }
        return *this;
    }


    ~Echipa() {}


    const std::string& getNume() const { return nume; }
    std::vector<Pilot>& getPiloti() { return piloti; }

    void afisare() const {
        std::cout<< "Echipa: "<<nume<<std::endl;
        for( const auto &p : piloti)
            p.afisare();
    }


    friend std::ostream& operator<<(std::ostream& os, const Echipa& e) {
        os << "Echipa: " << e.nume << "\n";
        os << "   Piloti:\n";
        for (const auto& p : e.piloti)
            os << "      " << p << "\n";
        return os;
    }


};

    class Campionat{
public:

void afiseazaClasamentEchipe(const std::map<std::string, int> &scoruri) {
    std::map<std::string, std::string> pilotEchipa = {
        {"Verstappen", "Red Bull"}, {"Tsunoda", "Red Bull"},
        {"Leclerc", "Ferrari"}, {"Hamilton", "Ferrari"},
        {"Russell", "Mercedes"}, {"Antonelli", "Mercedes"},
        {"Norris", "Mclaren"}, {"Piastri", "Mclaren"}};

    std::map<std::string, int> puncteEchipe;
    for ( const auto &p : scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    std::vector<std::pair<std::string, int>> clasamentEchipe(puncteEchipe.begin(), puncteEchipe.end());
    std::sort(clasamentEchipe.begin(), clasamentEchipe.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    std::cout << "\n===== CLASAMENT ECHIPE =====\n";
    int poz = 1;
    for (const auto &e : clasamentEchipe)
        std::cout << poz++ << ". " << e.first << " - " << e.second << " puncte\n";
}


    int meniuCampionat() {
        std::cout << "\nCampionatul continua:\n";
        std::cout << "1. Urmatoarea cursa\n";
        std::cout << "2. Vezi clasamentul general\n";
        std::cout << "3. Regulament\n";
        std::cout << "4. Detalii circuite\n";
        std::cout<<"5. Simulare Pitstop\n";
        std::cout<<"6. Simulare Safety Car\n";
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

    void afiseazaClasamentGeneral(const std::map<std::string, int>& scoruriExistente) {
std::map<std::string, int> scoruri=scoruriExistente;
        std::vector<std::string> totiPiloti  = {
            "Verstappen", "Tsunoda", "Leclerc", "Hamilton",
            "Russell", "Antonelli", "Norris", "Piastri"
        };
for (const auto &nume : totiPiloti) {
if (scoruri.find(nume)==scoruri.end())
    scoruri.try_emplace(nume, 0);
}

        std::vector<std::pair<std::string, int>> clasament(scoruri.begin(), scoruri.end());
        std::sort(clasament.begin(), clasament.end(), [](const auto &a, const auto &b) {
            return a.second > b.second;
        });

        std::cout << "\n===== CLASAMENT GENERAL PILOTI =====\n";
        int poz = 1;
        for (const auto &p : clasament)
            std::cout << poz++ << ". " << p.first << " - " << p.second << " puncte\n";

    }

void afisareRegulament() {
    std::cout << "\n===== REGULAMENT FORMULA 1 =====\n";
    std::cout << "SISTEM DE PUNCTAJ:\n";
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
    std::cout << "\nPunct bonus: Cel mai rapid tur (+1p)\n";
    std::cout << "Sanse de abandon: 10%\n";
}

void simulareVreme() {
    std::vector<std::string> conditii = {"Soare", "Ploaie", "Nori", "Ceata"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, conditii.size() - 1);
    std::string vreme = conditii[dist(gen)];

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

void afisareCircuitInfo() {
    std::map<std::string, std::string> info = {
        {"Monaco", "Circuit urban de 3.3 km, 78 tururi. Cele mai inguste viraje din F1."},
        {"Silverstone", "Circuit din Marea Britanie, 5.8 km. Faimos pentru virajele rapide Maggots-Becketts."},
        {"Spa", "Circuit belgian de 7 km, include celebra urcare Eau Rouge-Raidillon."}
    };

    std::cout << "\n===== DETALII CIRCUITE =====\n";
    for (const auto &c : info)
        std::cout << c.first << ": " << c.second << "\n";

}
//////momentan doar 3 circuite pentru demo


void simularePitStop() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(2.0, 4.5);
    double timp = dist(gen);

    std::cout << "\n Pit stop in curs...\n";
    std::cout << "Mecanici se grabesc sa schimbe rotile...\n";
    std::cout << "Verificare presiune, alimentare, ajustare aripa spate...\n";
    std::cout << "Timp total: " << timp << " secunde.\n";

    if (timp < 2.5)
        std::cout << "Echipa ta a fost fantastica!  Pit stop ultra rapid!\n";
    else if (timp < 3.5)
        std::cout << "Pit stop decent, fara greseli majore.\n";
    else
        std::cout << "Pit stop lent! Ai pierdut timp pretios!\n";
}


void simulareSafetyCar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distCauza(1, 4);
    std::uniform_real_distribution<> distDurata(2, 6);

    int cauza = distCauza(gen);
    int durata = distDurata(gen);

    std::cout << "\n Safety Car pe circuit!\n";

    switch (cauza) {
        case 1:
            std::cout << "Un pilot a iesit in decor si masina trebuie indepartata de pe pista.\n";
            break;
        case 2:
            std::cout << "Resturi pe circuit dupa un mic contact intre doua masini.\n";
            break;
        case 3:
            std::cout << "Conditii meteo periculoase - ploaie puternica in virajul 3.\n";
            break;
        case 4:
            std::cout << "Incident la boxe, un mecanic a alunecat - Safety Car temporar!\n";
            break;
    }

    std::cout << "Safety Car va ramane pe pista pentru aproximativ "
              << durata << " tururi.\n";

    std::cout << "Pilotii trebuie sa pastreze o distanta minima si sa nu depaseasca.\n";
    std::cout << "Dupa " << durata << " tururi, Safety Car se retrage si cursa continua!\n";
}

};

class Cursa {
    private:
    std::string locatie;
    std::vector<Echipa> echipe;
    std::vector<int> puncteF1 = {25, 18, 15, 12, 10 ,8 ,6, 4, 2, 1};
    Campionat &campionat;
    public:
    Cursa(std::string l, std::vector<Echipa> e, Campionat &c)
    : locatie(l), echipe(e), campionat(c) {}

    int punctePilotCursa(const std::string& pilotAles, std::map<std::string, int>& scoruri) {
        std::vector<Pilot> totiPiloti;
        for (auto &echipa : echipe)
            for (const auto &p : echipa.getPiloti())
                totiPiloti.push_back(p);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);

        std::cout << "\nCursa din " << locatie << " a inceput!\n\n";
        campionat.simulareVreme();

        std::uniform_int_distribution<> distAbandon(0, 9); //10%
        std::vector<std::string> abandonuri;

        for (auto it = totiPiloti.begin(); it != totiPiloti.end();) {
            if (distAbandon(gen) == 0) {
                abandonuri.push_back(it->getNume());
                it = totiPiloti.erase(it);
            } else {
                ++it;
            }
        }


        std::cout << "Clasament final pentru " << locatie << ":\n";

        std::uniform_real_distribution<> distTimp(75.0, 80.0);
        std::vector<double> timpi;
        for (size_t i = 0; i < totiPiloti.size(); ++i)
            timpi.push_back(distTimp(gen) + i * 0.5);


        std::sort(timpi.begin(), timpi.end());
        double timpPrimul = timpi[0];

        int punctePilot = 0;
        std::vector<std::pair<std::string, double>> rezultate;

        for (size_t i = 0; i < totiPiloti.size(); ++i) {
            int puncte = (i < puncteF1.size()) ? puncteF1[i] : 0;
            totiPiloti[i].adaugaPuncte(puncte);
            scoruri[totiPiloti[i].getNume()] += puncte;
            rezultate.push_back({totiPiloti[i].getNume(), timpi[i]});
            if (totiPiloti[i].getNume() == pilotAles)
                punctePilot = puncte;
        }


        int randomBonus = gen() % totiPiloti.size();
        std::string pilotBonus = totiPiloti[randomBonus].getNume();
        scoruri[pilotBonus] += 1;

        for (size_t i = 0; i < rezultate.size(); ++i) {
            double diferenta = rezultate[i].second - timpPrimul;
            std::cout << i + 1 << ". " << rezultate[i].first
                      << " - " << puncteF1[std::min(i, puncteF1.size() - 1)]
                      << " pct | Timp: " << rezultate[i].second
                      << " min | +" << diferenta << "s\n";
        }

        if (!abandonuri.empty()) {
            std::cout << "\nAbandonuri (DNF):\n";
            for (const auto &nume : abandonuri)
                std::cout << "- " << nume << " (DNF)\n";
        }



        std::cout << "\nCel mai rapid tur: " << pilotBonus << " (+1 punct bonus)\n";

        auto it = std::find_if(rezultate.begin(), rezultate.end(),
                               [&](const auto &x){ return x.first == pilotAles; });
        if (it != rezultate.end())
            std::cout << "\nPilotul tau (" << pilotAles << ") a terminat pe locul "
                      << (it - rezultate.begin() + 1)
                      << " si a obtinut " << punctePilot << " puncte.\n";

        return punctePilot;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cursa& c) {
        os << "Cursa: " << c.locatie << "\n";
        os << "Echipe participante:\n";
        for (const auto& e : c.echipe)
            os << e << "\n";
        return os;
    }

    };




int main() {
       Campionat campionat;
    std::vector<Echipa> echipe ={

        Echipa("Red Bull" , {"Verstappen" , "Tsunoda"}),
        Echipa("Ferrari" , {"Leclerc" , "Hamilton"}),
        Echipa("Mercedes" , {"Russell", "Antonelli"}),
        Echipa("Mclaren" , {"Norris", "Piastri"})

    };

        std::vector<std::string> circuite = {"Monaco", "Silverstone", "Spa"};
//int puncteTotale=0;
        std::map<std::string, int> scoruri;

    std::cout<<"Bine ai venit la Formula 1 Monaco Grand Prix!\n";
    std::cout<<"Alege o echipa:\n";
    for (size_t i = 0; i < echipe.size(); ++i)
        std::cout << i + 1 << ". " << echipe[i].getNume() << "\n";
    int alegereEchipa;
    std::cin >> alegereEchipa;
    alegereEchipa--;
    if(alegereEchipa < 0 || alegereEchipa >= static_cast<int>(echipe.size())) {
        std::cout<<"Echipa non valida!\n";
        return 0;
    }
    auto echipaSelectata = echipe[alegereEchipa];
    std::cout<<"Ai ales echipa: "<<echipaSelectata.getNume()<<std::endl;
    std::cout<<"Alege pilotul: \n";
    auto piloti = echipaSelectata.getPiloti();
    for (size_t i = 0; i < piloti.size(); ++i)
        std::cout << i + 1 << ". " << piloti[i].getNume() << "\n";

    int alegerePilot;
    std::cin >> alegerePilot;
    alegerePilot--;
    if(alegerePilot >= static_cast<int>(piloti.size())) {
        std::cout<<"Pilot invalid!\n";
        return 0;
    }
std:: string pilotAles = piloti[alegerePilot].getNume();
    std::cout<<"\n Ai ales sa concurezi cu "<<pilotAles<<"!\n";

        for (size_t i = 0; i < circuite.size(); ++i) {
            Cursa cursa(circuite[i], echipe, campionat);
           cursa.punctePilotCursa(pilotAles, scoruri);
            //puncteTotale += puncteCursa;
            if (i < circuite.size() - 1) {
                int opt;
                do {
                    opt = campionat.meniuCampionat();
                    if (opt == 2) {
                        campionat.afiseazaClasamentGeneral(scoruri);
                        campionat.afiseazaClasamentEchipe(scoruri);
                    }
                    else if (opt == 3) {
                        campionat.afisareRegulament();
                    }
                    else if (opt == 4){
                        campionat.afisareCircuitInfo();
                    }
                    else if (opt == 5){
                        campionat.simularePitStop();
                    }
                       else if (opt == 6){
                        campionat.simulareSafetyCar();
                    }
                    else if (opt == 7) {
                        std::cout << "\nCampionatul s-a incheiat mai devreme!\n";
                        campionat.afiseazaClasamentGeneral(scoruri);
                        return 0;
                    }
                } while (opt != 1);
            }
        }

        campionat.afiseazaClasamentGeneral(scoruri);
    campionat.afiseazaClasamentEchipe(scoruri);


    std::vector<std::pair<std::string, int>> clasamentFinal(scoruri.begin(), scoruri.end());
    std::sort(clasamentFinal.begin(), clasamentFinal.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    std::string campionPilot = clasamentFinal.front().first;
    int punctePilotCampion = clasamentFinal.front().second;

    std::map<std::string, std::string> pilotEchipa = {
        {"Verstappen", "Red Bull"}, {"Tsunoda", "Red Bull"},
        {"Leclerc", "Ferrari"}, {"Hamilton", "Ferrari"},
        {"Russell", "Mercedes"}, {"Antonelli", "Mercedes"},
        {"Norris", "Mclaren"}, {"Piastri", "Mclaren"}};

    std::map<std::string, int> puncteEchipe;
    for (const auto &p : scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    auto echipaCampioana = std::max_element(puncteEchipe.begin(), puncteEchipe.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; });

    std::cout << "\nCampion mondial: " << campionPilot << " (" << pilotEchipa[campionPilot]
              << ") - " << punctePilotCampion << " puncte\n";
    std::cout << "Campioana la constructori: " << echipaCampioana->first
              << " - " << echipaCampioana->second << " puncte\n";

    std::cout << "\nFelicitari! Ai terminat intregul campionat de Formula 1!\n";
    return 0;

}