#ifndef ECHIPA_H
#define ECHIPA_H

#include <string>
#include <vector>
#include <iostream>
#include "Pilot.h"
#include "Motor.h"

class Echipa {
private:
    std::string nume;
    std::vector<Pilot> piloti;
    Motor motorEchipa;

public:
    Echipa(const std::string& n, std::vector<std::string> numePiloti, const std::string& motorProd, int motorCP, const std::string& motorSerie);
    Echipa(const Echipa& e);
    Echipa& operator=(Echipa other);
    friend void swap(Echipa& first, Echipa& second);
    ~Echipa();

    const std::string& getNume() const;
    std::vector<Pilot>& getPiloti();
    const std::vector<Pilot>& getPiloti() const;
    const Motor& getMotor() const { return motorEchipa; }

    friend std::ostream& operator<<(std::ostream& os, const Echipa& e);
};

#endif
