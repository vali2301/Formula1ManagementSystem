#ifndef EVENIMENT_FACTORY_H
#define EVENIMENT_FACTORY_H

#include <memory>
#include <string>
#include <vector>
#include "Eveniment.h"
#include "Echipa.h"
#include "Campionat.h"

class EvenimentFactory {
public:
    virtual ~EvenimentFactory() = default;
    virtual std::unique_ptr<Eveniment> creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const = 0;
};

class FactoryCursa : public EvenimentFactory {
public:
    std::unique_ptr<Eveniment> creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const override;
};

class FactoryCalificari : public EvenimentFactory {
public:
    std::unique_ptr<Eveniment> creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const override;
};

class FactorySprint : public EvenimentFactory {
public:
    std::unique_ptr<Eveniment> creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const override;
};

class FactoryRecunoastere : public EvenimentFactory {
public:
    std::unique_ptr<Eveniment> creeazaEveniment(const std::string& locatie, const std::vector<Echipa>& echipe, Campionat& camp) const override;
};

#endif