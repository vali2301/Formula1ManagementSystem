#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
 class Pilot {
     private:
     std:: string nume;
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
};
class Cursa {
    private:
    std::string locatie;
    std::vector<Echipa> echipe;
    std::vector<int> puncteF1 = {25, 18, 15, 12, 10 ,8 ,6, 4, 2, 1};
    public:
    Cursa(std::string l, std::vector<Echipa> e) : locatie(l), echipe(e) {}

    void simuleaza(std::string pilotAles) {
        std::cout<<"Cursa din "<<locatie<<" a inceput!\n";
        std::vector<Pilot> totiPiloti;

        for(auto &echipa : echipe)
            for(auto &p : echipa.getPiloti())
                totiPiloti.push_back(p);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(totiPiloti.begin(), totiPiloti.end(), gen);
        std::cout<<"\n Clasamentul final: \n";
        for(size_t i = 0; i < totiPiloti.size(); ++i) {
            int puncte = (i < puncteF1.size()) ? puncteF1[i] : 0;
            totiPiloti[i].adaugaPuncte(puncte);
            totiPiloti[i].afisare();
             if(totiPiloti[i].getNume() == pilotAles)
                 std::cout<<"Pilotul tau ( "<<pilotAles<<" ) a terminat pe locul "<<i+1<<" si a obtinut "<<puncte<<" puncte!\n";
        }
        }
    void afisareEchipe() const {
            std::cout<<"\n Echipe participante:\n";
            for(auto &e : echipe)
                e.afisare();
        }

    };

int main() {
    std::vector<Echipa> echipe ={

        Echipa("Red Bull" , {"Verstappen" , "Tsunoda"}),
        Echipa("Ferrari" , {"Leclerc" , "Hamilton"}),
        Echipa("Mercedes" , {"Russell", "Antonelli"}),
        Echipa("Mclaren" , {"Norris", "Piastri"})

    };
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
    Cursa monaco("Monaco", echipe);
    monaco.simuleaza(pilotAles);
    return 0;
}