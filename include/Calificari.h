#ifndef CALIFICARI_H
#define CALIFICARI_H

#include "Eveniment.h"
#include "Campionat.h"
#include "Echipa.h"
#include <vector>
#include <map>

class Calificari : public Eveniment {
private:
    Campionat& campionat;
    std::vector<std::string> listaPiloti;
    std::map<std::string, double> timpiCalificari;
    // Informație specifică acestei clase, accesată prin dynamic_cast
    std::vector<std::string> grilaStart;

public:
    Calificari(const std::string& n, Campionat& c, const std::vector<Echipa>& echipe);

    virtual ~Calificari() override = default;

    Calificari(const Calificari& other);
    Calificari& operator=(const Calificari& other);

    virtual void simuleazaEveniment() override;

    virtual Eveniment* clone() const override;

    virtual void afisareVirtuala() const override;

    const std::vector<std::string>& getGrilaStart() const;
    void afiseazaGrilaStart() const;
};

#endif