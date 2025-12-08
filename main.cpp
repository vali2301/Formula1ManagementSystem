
#include "include/Pilot.h"
#include "include/Echipa.h"
#include "include/Cursa.h"
#include "include/Campionat.h"


int main() {
    Campionat campionat;
    std::vector<Echipa> echipe = {

        Echipa("Red Bull", {"Verstappen", "Tsunoda"}),
        Echipa("Ferrari", {"Leclerc", "Hamilton"}),
        Echipa("Mercedes", {"Russell", "Antonelli"}),
        Echipa("Mclaren", {"Norris", "Piastri"})

    };

    std::vector<std::string> circuite = {"Monaco", "Silverstone", "Spa"};
    //int puncteTotale=0;
    std::map<std::string, int> scoruri;

    std::cout << "Bine ai venit la Formula 1 Monaco Grand Prix!\n";
    std::cout << "Alege o echipa:\n";
    for (size_t i = 0; i < echipe.size(); ++i)
        std::cout << i + 1 << ". " << echipe[i].getNume() << "\n";
    int alegereEchipa;
    std::cin >> alegereEchipa;
    alegereEchipa--;
    if (alegereEchipa < 0 || alegereEchipa >= static_cast<int>(echipe.size())) {
        std::cout << "Echipa non valida!\n";
        return 0;
    }
    auto echipaSelectata = echipe[alegereEchipa];
    std::cout << "Ai ales echipa: " << echipaSelectata.getNume() << std::endl;
    std::cout << "Alege pilotul: \n";
    auto piloti = echipaSelectata.getPiloti();
    for (size_t i = 0; i < piloti.size(); ++i)
        std::cout << i + 1 << ". " << piloti[i].getNume() << "\n";

    int alegerePilot;
    std::cin >> alegerePilot;
    alegerePilot--;
    if (alegerePilot >= static_cast<int>(piloti.size())) {
        std::cout << "Pilot invalid!\n";
        return 0;
    }
    std::string pilotAles = piloti[alegerePilot].getNume();
    std::cout << "\n Ai ales sa concurezi cu " << pilotAles << "!\n";

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
                } else if (opt == 3) {
                    campionat.afisareRegulament();
                } else if (opt == 4) {
                    campionat.afisareCircuitInfo();
                } else if (opt == 5) {
                    campionat.simularePitStop();
                } else if (opt == 6) {
                    campionat.simulareSafetyCar();
                } else if (opt == 7) {
                    std::cout << "\nCampionatul s-a incheiat mai devreme!\n";
                    campionat.afiseazaClasamentGeneral(scoruri);
                    return 0;
                }
            } while (opt != 1);
        }
    }

    campionat.afiseazaClasamentGeneral(scoruri);
    campionat.afiseazaClasamentEchipe(scoruri);


    std::vector<std::pair<std::string, int> > clasamentFinal(scoruri.begin(), scoruri.end());
    std::sort(clasamentFinal.begin(), clasamentFinal.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    std::string campionPilot = clasamentFinal.front().first;
    int punctePilotCampion = clasamentFinal.front().second;

    std::map<std::string, std::string> pilotEchipa = {
        {"Verstappen", "Red Bull"}, {"Tsunoda", "Red Bull"},
        {"Leclerc", "Ferrari"}, {"Hamilton", "Ferrari"},
        {"Russell", "Mercedes"}, {"Antonelli", "Mercedes"},
        {"Norris", "Mclaren"}, {"Piastri", "Mclaren"}
    };

    std::map<std::string, int> puncteEchipe;
    for (const auto &p: scoruri)
        puncteEchipe[pilotEchipa[p.first]] += p.second;

    auto echipaCampioana = std::max_element(puncteEchipe.begin(), puncteEchipe.end(),
                                            [](const auto &a, const auto &b) { return a.second < b.second; });

    std::cout << "\nCampion mondial: " << campionPilot << " (" << pilotEchipa[campionPilot]
            << ") - " << punctePilotCampion << " puncte\n";
    std::cout << "Campioana la constructori: " << echipaCampioana->first
            << " - " << echipaCampioana->second << " puncte\n";

    campionat.afiseazaCelMaiConstantPilot(scoruri, circuite.size());

    std::cout << "\nFelicitari! Ai terminat intregul campionat de Formula 1!\n";
    return 0;
}
