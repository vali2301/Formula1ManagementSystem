#include "Pilot.h"

Pilot::Pilot(std::string n) : nume(n), puncte(0) {
}

Pilot::Pilot(const Pilot &p) = default;

Pilot &Pilot::operator=(const Pilot &p) = default;

Pilot::~Pilot() = default;

const std::string &Pilot::getNume() const {
    return nume;
}

void Pilot::adaugaPuncte(int p) {
    puncte += p;
}

std::ostream &operator<<(std::ostream &os, const Pilot &p) {
    os << "Pilot: " << p.nume << " (" << p.puncte << " puncte)";
    return os;
}
