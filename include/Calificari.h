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
    std::vector<std::string> grilaStart;

public:
    Calificari(const std::string& n, Campionat& c, const std::vector<Echipa>& echipe);

    ~Calificari() override;

    [[nodiscard]] double calculeazaRiscAbandon() const override;

    Calificari(const Calificari& other);
    Calificari& operator=(const Calificari& other);

    void simuleazaEveniment() override;

    [[nodiscard]] Eveniment* clone() const override;

    void afisareVirtuala() const override;

    [[nodiscard]] const std::vector<std::string>& getGrilaStart() const;
    void afiseazaGrilaStart() const;
};

#endif