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
    Echipa(std::string  n, const std::vector<std::string>& numePiloti, const std::string& motorProd, int motorCP, const std::string& motorSerie);
    Echipa(const Echipa& e);
    Echipa& operator=(Echipa other);
    friend void swap(Echipa& first, Echipa& second) noexcept;
    ~Echipa();

    [[nodiscard]] const std::string& getNume() const;
    std::vector<Pilot>& getPiloti();
    [[nodiscard]] const std::vector<Pilot>& getPiloti() const;
    [[nodiscard]] const Motor& getMotor() const { return motorEchipa; }

    friend std::ostream& operator<<(std::ostream& os, const Echipa& e);
};

#endif
