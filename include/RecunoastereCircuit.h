#ifndef RECUNOASTERE_CIRCUIT_H
#define RECUNOASTERE_CIRCUIT_H

#include "Eveniment.h"
#include "Echipa.h"
#include <map>
#include <vector>

class RecunoastereCircuit : public Eveniment {
private:
    std::string detalii;
    std::vector<std::string> listaPiloti;
    std::map<std::string, double> timpiRecunoastere;

public:
    RecunoastereCircuit(const std::string& n, std::string  d, const std::vector<Echipa>& echipe);

    ~RecunoastereCircuit() override = default;
    [[nodiscard]] double calculeazaRiscAbandon() const override;

    RecunoastereCircuit(const RecunoastereCircuit& other);
    RecunoastereCircuit& operator=(const RecunoastereCircuit& other);

    void simuleazaEveniment() override;
    [[nodiscard]] Eveniment* clone() const override;
    void afisareVirtuala() const override;
};

#endif