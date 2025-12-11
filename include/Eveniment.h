#ifndef EVENIMENT_H
#define EVENIMENT_H

#include <string>
#include <utility>

class Eveniment {
private:
    std::string nume;

public:
    explicit Eveniment(std::string n) : nume(std::move(n)) {
    }

    virtual ~Eveniment();

    virtual void simuleazaEveniment() = 0;

    [[nodiscard]] virtual Eveniment *clone() const = 0;

    virtual void afisareVirtuala() const = 0;

    [[nodiscard]] virtual double calculeazaRiscAbandon() const = 0; //virtuala pura(sper)

    void afiseazaDetaliiEveniment() const;

    [[nodiscard]] const std::string &getNume() const { return nume; }
};
#endif
