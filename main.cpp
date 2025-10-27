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
        std::cout << "Clasament final pentru " << locatie << ":\n";

        int punctePilot = 0;
        for (size_t i = 0; i < totiPiloti.size(); ++i) {
            int puncte = (i < puncteF1.size()) ? puncteF1[i] : 0;
            totiPiloti[i].adaugaPuncte(puncte);
            std::cout << i + 1 << ". " << totiPiloti[i].getNume() << " - " << puncte << " puncte\n";
            scoruri[totiPiloti[i].getNume()] += puncte;
            if (totiPiloti[i].getNume() == pilotAles)
                punctePilot = puncte;
        }
        return punctePilot;
    }

    };

    int meniuCampionat() {
        std::cout << "\nCampionatul continua:\n";
        std::cout << "1. Urmatoarea cursa\n";
        std::cout << "2. Vezi clasamentul general\n";
        std::cout << "3. Iesi din campionat\n";
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

    void afiseazaClasamentGeneral(const std::map<std::string, int>& scoruri) {
        std::vector<std::pair<std::string, int>> clasament(scoruri.begin(), scoruri.end());
        std::sort(clasament.begin(), clasament.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });
        std::cout << "\n===== CLASAMENT GENERAL =====\n";
        int poz = 1;
        for (auto &p : clasament)
            std::cout << poz++ << ". " << p.first << " - " << p.second << " puncte\n";
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
                    if (opt == 2)
                        afiseazaClasamentGeneral(scoruri);
                    else if (opt == 3) {
                        std::cout << "\nCampionatul s-a incheiat mai devreme!\n";
                        afiseazaClasamentGeneral(scoruri);
                        return 0;
                    }
                } while (opt == 2);
            }
        }

        afiseazaClasamentGeneral(scoruri);
        std::cout << "\nFelicitari! Ai terminat intregul campionat de Formula 1!\n";
        return 0;
}