#include "Echipa.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void swap(Echipa& first, Echipa& second) noexcept {
    using std::swap;
    swap(first.nume, second.nume);
    swap(first.piloti, second.piloti);
    swap(first.motorEchipa, second.motorEchipa);
}


Echipa::Echipa(std::string  n, const std::vector<std::string>& numePiloti, const std::string& motorProd, int motorCP, const std::string& motorSerie)
    : nume(std::move(n)), motorEchipa(motorProd, motorCP, motorSerie) {
    for (auto& p : numePiloti)
        piloti.emplace_back(p);
}


Echipa::Echipa(const Echipa& e)
    : nume(e.nume), piloti(e.piloti), motorEchipa(e.motorEchipa) {}



Echipa &Echipa::operator=(Echipa other) {
    swap(*this, other);
    return *this;
}

Echipa::~Echipa() = default;

const std::string &Echipa::getNume() const {
    return nume;
}

std::vector<Pilot> &Echipa::getPiloti() {
    return piloti;
}

const std::vector<Pilot> &Echipa::getPiloti() const {
    return piloti;
}

std::ostream &operator<<(std::ostream &os, const Echipa &e) {
    os << "Echipa: " << e.nume << "\n";
    os << "   Motor: " << e.motorEchipa.getProducator() << "\n";
    os << "   Piloti:\n";
    for (const auto &p: e.piloti)
        os << "      " << p << "\n";
    return os;
}