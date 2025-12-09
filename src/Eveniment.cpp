#include "Eveniment.h"

Eveniment::~Eveniment() = default;

void Eveniment::afiseazaDetaliiEveniment() const {
    std::cout << "\n----- DETALII EVENIMENT -----\n";
    this->afisareVirtuala();
    std::cout << "-----------------------------\n";
}