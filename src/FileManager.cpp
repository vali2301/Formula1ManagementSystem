#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Exceptii.h"

std::string FileManager::cale(const std::string& fisier) {
    return (std::filesystem::current_path()/ ".." / "data" / fisier).string();
}

std::vector<Echipa> FileManager::citesteEchipe() {
    std::ifstream fin(cale("echipe.txt"));
    if (!fin)
        throw CampionatException("Nu pot deschide fisierul echipe.txt");

    std::vector<Echipa> echipe;
    std::string linie;

    while (std::getline(fin, linie)) {
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string nume, pilotiStr, motorProd, motorSerie;
        int motorCP;

        std::getline(ss, nume, ';');
        std::getline(ss, pilotiStr, ';');
        std::getline(ss, motorProd, ';');
        ss >> motorCP;
        ss.ignore(1);
        std::getline(ss, motorSerie);

        std::vector<std::string> piloti;
        std::stringstream sp(pilotiStr);
        std::string p;
        while (std::getline(sp, p, ','))
            piloti.push_back(p);

        echipe.emplace_back(nume, piloti, motorProd, motorCP, motorSerie);
    }

    return echipe;
}

std::vector<std::string> FileManager::citesteCircuite() {
    std::ifstream fin(cale("circuite.txt"));
    if (!fin)
        throw CampionatException("Nu pot deschide fisierul circuite.txt");

    std::vector<std::string> circuite;
    std::string linie;
    while (std::getline(fin, linie))
        if (!linie.empty())
            circuite.push_back(linie);

    return circuite;
}

std::vector<std::pair<std::string, std::string>> FileManager::citesteInfoCircuite() {
    std::ifstream fin(cale("circuite_info.txt"));
    if (!fin)
        throw CampionatException("Nu pot deschide fisierul circuite_info.txt");

    std::vector<std::pair<std::string, std::string>> info;
    std::string linie;

    while (std::getline(fin, linie)) {
        auto pos = linie.find(';');
        if (pos != std::string::npos)
            info.emplace_back(linie.substr(0, pos), linie.substr(pos + 1));
    }

    return info;
}
