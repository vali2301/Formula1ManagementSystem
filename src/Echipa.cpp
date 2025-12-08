#include "Echipa.h"

Echipa::Echipa(const std::string& n, std::vector<std::string> numePiloti) : nume(n) {
    for (auto& p : numePiloti)
        piloti.emplace_back(p);
}

Echipa::Echipa(const Echipa& e) : nume(e.nume), piloti(e.piloti) {}

Echipa& Echipa::operator=(const Echipa& e) {
    if (this != &e) {
        nume = e.nume;
        piloti = e.piloti;
    }
    return *this;
}

Echipa::~Echipa() {}

const std::string& Echipa::getNume() const {
    return nume;
}

std::vector<Pilot>& Echipa::getPiloti() {
    return piloti;
}

std::ostream& operator<<(std::ostream& os, const Echipa& e) {
    os << "Echipa: " << e.nume << "\n";
    os << "   Piloti:\n";
    for (const auto& p : e.piloti)
        os << "      " << p << "\n";
    return os;
}
