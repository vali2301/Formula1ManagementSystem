#ifndef MANAGER_PERFORMANTA_H
#define MANAGER_PERFORMANTA_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <string>
#include "Exceptii.h"

template <typename T>
class ManagerPerformanta {
private:
    std::string numeCategorie;
    std::vector<T> date;

public:
    explicit ManagerPerformanta(std::string nume) : numeCategorie(std::move(nume)) {}

    void adaugaRezultat(T valoare) {
        date.push_back(valoare);
    }

    T calculeazaMedia() const {
        if (date.empty()) return T(0);
        T suma = std::accumulate(date.begin(), date.end(), T(0));
        return suma / static_cast<T>(date.size());
    }

    T obtineCelMaiBun() const {
        if (date.empty()) throw CampionatException("Nu exista date pentru " + numeCategorie);
        return *std::min_element(date.begin(), date.end());
    }

    void sorteazaRezultate(bool ascendent = true) {
        if (ascendent)
            std::sort(date.begin(), date.end());
        else
            std::sort(date.begin(), date.end(), std::greater<T>());
    }

    void afiseazaRaport() const {
        std::cout << "\n--- RAPORT PERFORMANTA: " << numeCategorie << " ---\n";
        for (size_t i = 0; i < date.size(); ++i) {
            std::cout << "Sesiunea " << i + 1 << ": " << std::fixed << std::setprecision(3) << date[i] << "\n";
        }
        if (!date.empty()) {
            std::cout << "Media categoriei: " << calculeazaMedia() << "\n";
            std::cout << "Cel mai bun rezultat: " << *std::min_element(date.begin(), date.end()) << "\n";
        }
        std::cout << "-------------------------------------------\n";
    }

    const std::vector<T>& getToateDatele() const { return date; }
};

template <typename T>
void comparaRezultate(T r1, T r2, const std::string& eticheta) {
    std::cout << "\n[COMPARATIE " << eticheta << "]\n";
    if (r1 < r2) {
        std::cout << "Rezultatul 1 (" << r1 << ") este mai mic (mai bun in timp) decat Rezultatul 2 (" << r2 << ").\n";
        std::cout << "Diferenta: " << (r2 - r1) << "\n";
    } else if (r1 > r2) {
        std::cout << "Rezultatul 2 (" << r2 << ") este mai mic (mai bun in timp) decat Rezultatul 1 (" << r1 << ").\n";
        std::cout << "Diferenta: " << (r1 - r2) << "\n";
    } else {
        std::cout << "Rezultatele sunt identice: " << r1 << "\n";
    }
}

#endif