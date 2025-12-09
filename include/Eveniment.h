#ifndef EVENIMENT_H
#define EVENIMENT_H

#include <string>

class Eveniment {
private:
    std::string nume;

public:
    explicit Eveniment(const std::string &n) : nume(n) {
    }

    virtual ~Eveniment();

    virtual void simuleazaEveniment() = 0;

    virtual Eveniment *clone() const = 0;

    virtual void afisareVirtuala() const = 0;

    void afiseazaDetaliiEveniment() const;

    const std::string &getNume() const { return nume; }
};
#endif
