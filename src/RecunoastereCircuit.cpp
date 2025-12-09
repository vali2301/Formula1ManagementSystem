#include "RecunoastereCircuit.h"
#include <iostream>

RecunoastereCircuit::RecunoastereCircuit(const std::string &n, const std::string &d)
    : Eveniment(n), detalii(d) {
}

RecunoastereCircuit::RecunoastereCircuit(const RecunoastereCircuit &other)
    : Eveniment(other), detalii(other.detalii) {
}

RecunoastereCircuit &RecunoastereCircuit::operator=(const RecunoastereCircuit &other) {
    if (this != &other) {
        Eveniment::operator=(other);
        detalii = other.detalii;
    }
    return *this;
}

void RecunoastereCircuit::simuleazaEveniment() {
    std::cout << "\n[SIMULARE] Recunoastere Circuit: Pilotii fac un tur lent de recunoastere a pistei.\n";
    std::cout << "Detalii circuit: " << detalii << "\n";
}

Eveniment *RecunoastereCircuit::clone() const {
    return new RecunoastereCircuit(*this);
}

void RecunoastereCircuit::afisareVirtuala() const {
    std::cout << "Tip: Recunoastere Circuit\n";
    std::cout << "Circuit: " << getNume() << "\n";
    std::cout << "Scurta descriere: " << detalii << "\n";
}
