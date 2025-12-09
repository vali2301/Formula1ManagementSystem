#ifndef RECUNOASTERE_CIRCUIT_H
#define RECUNOASTERE_CIRCUIT_H

#include "Eveniment.h"

class RecunoastereCircuit : public Eveniment {
private:
    std::string detalii;

public:
    RecunoastereCircuit(const std::string& n, const std::string& d);

    virtual ~RecunoastereCircuit() override = default;

    RecunoastereCircuit(const RecunoastereCircuit& other);
    RecunoastereCircuit& operator=(const RecunoastereCircuit& other);

    virtual void simuleazaEveniment() override;
    virtual Eveniment* clone() const override;
    virtual void afisareVirtuala() const override;
};

#endif