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
     Pilot(std::string n) : nume(n), puncte(0) {}
     Pilot(const Pilot &p) {
         nume = p.nume;
         puncte = p.puncte;
     }
     std::string getNume() const { return nume; }
     int getPuncte() const { return puncte; }
     void adaugaPuncte(int p) { puncte += p; }
     void setPuncte(int p) { puncte = p; }
     void afisare() const {
    std::cout<<"Pilot: "<<nume<<", Puncte: "<<puncte<<std::endl;
     }
 };

class Echipa {
    private:
    std::string nume;
    std::vector<Pilot> piloti;
    public:
    Echipa(std::string n, std::vector<std::string> numePiloti) : nume(n) {
        for(auto &p : numePiloti)
            piloti.emplace_back(p);

    }
    Echipa(const Echipa &e) : nume(e.nume), piloti(e.piloti) {}
    std::string getNume() const { return nume; }
    std::vector<Pilot>& getPiloti() { return piloti; }

    void afisare() const {
        std::cout<< "Echipa: "<<nume<<std::endl;
        for(auto &p : piloti)
            p.afisare();
    }
    friend std::ostream& operator<<(std::ostream& os, const Echipa& e) {
        os << "Echipa: " << e.nume << " (" << e.piloti.size() << " piloti)";
        return os;
    }
};
class Cursa {
    private:
    std::string locatie;
    std::vector<Echipa> echipe;
    std::vector<int> puncteF1 = {25, 18, 15, 12, 10 ,8 ,6, 4, 2, 1};
    public:
    Cursa(std::string l, std::vector<Echipa> e) : locatie(l), echipe(e) {}

    int punctePilotCursa(const std::string& pilotAles, std::map<std::string, int>& scoruri) {
        std::vector<Pilot> totiPiloti;
        for (auto &echipa : echipe)
            for (auto &p : echipa.getPiloti())
                totiPiloti.push_back(p);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);

        std::cout << "\nCursa din " << locatie << " a inceput!\n\n";


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
            for (auto &nume : abandonuri)
                std::cout << "- " << nume << " (DNF)\n";
        }



        std::cout << "\nCel mai rapid tur: " << pilotBonus << " (+1 punct bonus)\n";

        auto it = std::find_if(rezultate.begin(), rezultate.end(),
                               [&](auto &x){ return x.first == pilotAles; });
        if (it != rezultate.end())
            std::cout << "\nPilotul tau (" << pilotAles << ") a terminat pe locul "
                      << (it - rezultate.begin() + 1)
                      << " si a obtinut " << punctePilot << " puncte.\n";

        return punctePilot;
    }

    };

void afiseazaClasamentEchipe(const std::map<std::string, int> &scoruri) {
    std::map<std::string, std::string> pilotEchipa = {
        {"Verstappen", "Red Bull"}, {"Tsunoda", "Red Bull"},
        {"Leclerc", "Ferrari"}, {"Hamilton", "Ferrari"},
        {"Russell", "Mercedes"}, {"Antonelli", "Mercedes"},
        {"Norris", "Mclaren"}, {"Piastri", "Mclaren"}};

    std::map<std::string, int> puncteEchipe;
    for (auto &p : scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    std::vector<std::pair<std::string, int>> clasamentEchipe(puncteEchipe.begin(), puncteEchipe.end());
    std::sort(clasamentEchipe.begin(), clasamentEchipe.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    std::cout << "\n===== CLASAMENT ECHIPE =====\n";
    int poz = 1;
    for (auto &e : clasamentEchipe)
        std::cout << poz++ << ". " << e.first << " - " << e.second << " puncte\n";
}


    int meniuCampionat() {
        std::cout << "\nCampionatul continua:\n";
        std::cout << "1. Urmatoarea cursa\n";
        std::cout << "2. Vezi clasamentul general\n";
        std::cout << "3. Regulament\n";
        std::cout << "4. Iesi din campionat\n";
        std::cout << "Alege o optiune: ";
        int opt;
        while (true) {
            if (std::cin >> opt && opt >= 1 && opt <= 3)
                return opt;
            std::cout << "Optiune invalida! Alege 1 - 3: ";
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
    scoruri[nume]=0;
}

        std::vector<std::pair<std::string, int>> clasament(scoruri.begin(), scoruri.end());
        std::sort(clasament.begin(), clasament.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });

        std::cout << "\n===== CLASAMENT GENERAL PILOTI =====\n";
        int poz = 1;
        for (auto &p : clasament)
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




int main() {
    std::vector<Echipa> echipe ={

        Echipa("Red Bull" , {"Verstappen" , "Tsunoda"}),
        Echipa("Ferrari" , {"Leclerc" , "Hamilton"}),
        Echipa("Mercedes" , {"Russell", "Antonelli"}),
        Echipa("Mclaren" , {"Norris", "Piastri"})

    };

        std::vector<std::string> circuite = {"Monaco", "Silverstone", "Spa"};
        int puncteTotale = 0;
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
            Cursa cursa(circuite[i], echipe);
            int puncteCursa = cursa.punctePilotCursa(pilotAles, scoruri);
            puncteTotale += puncteCursa;

            if (i < circuite.size() - 1) {
                int opt;
                do {
                    opt = meniuCampionat();
                    if (opt == 2) {
                        afiseazaClasamentGeneral(scoruri);
                        afiseazaClasamentEchipe(scoruri);
                    }
                    else if (opt == 3) {
                        afisareRegulament();
                    }

                    else if (opt == 4) {
                        std::cout << "\nCampionatul s-a incheiat mai devreme!\n";
                        afiseazaClasamentGeneral(scoruri);
                        return 0;
                    }
                } while (opt != 1);
            }
        }

        afiseazaClasamentGeneral(scoruri);
    afiseazaClasamentEchipe(scoruri);


    std::vector<std::pair<std::string, int>> clasamentFinal(scoruri.begin(), scoruri.end());
    std::sort(clasamentFinal.begin(), clasamentFinal.end(), [](auto &a, auto &b) {
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
    for (auto &p : scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    auto echipaCampioana = std::max_element(puncteEchipe.begin(), puncteEchipe.end(),
        [](auto &a, auto &b) { return a.second < b.second; });

    std::cout << "\nCampion mondial: " << campionPilot << " (" << pilotEchipa[campionPilot]
              << ") - " << punctePilotCampion << " puncte\n";
    std::cout << "Campioana la constructori: " << echipaCampioana->first
              << " - " << echipaCampioana->second << " puncte\n";

    std::cout << "\nFelicitari! Ai terminat intregul campionat de Formula 1!\n";
    return 0;

}