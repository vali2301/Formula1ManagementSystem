#ifndef CONDITII_METEO_H
#define CONDITII_METEO_H

#include <string>

class ConditiiMeteo {
public:
    enum TipVreme { Soare, Nori, PloaieUsoara, PloaieTorentiala };

private:
    TipVreme vremeActuala;
    double coeficientAderenta;
    std::string numeCircuit;

public:
    explicit ConditiiMeteo(const std::string &circuit);


    ConditiiMeteo(const ConditiiMeteo &) = default;

    ConditiiMeteo &operator=(const ConditiiMeteo &) = default;

    void schimbaVremea();

    [[nodiscard]] double getCoeficientAderenta() const { return coeficientAderenta; }

    [[nodiscard]] std::string getNumeVreme() const;

    friend std::ostream &operator<<(std::ostream &os, const ConditiiMeteo &cm);
};

#endif
