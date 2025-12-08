#ifndef PILOT_H
#define PILOT_H

#include <string>
#include <iostream>

class Pilot {
private:
    std::string nume;
    int puncte;

public:
    explicit Pilot(std::string n);

    Pilot(const Pilot &);

    Pilot &operator=(const Pilot &);

    ~Pilot();

    const std::string &getNume() const;

    void adaugaPuncte(int p);

    friend std::ostream &operator<<(std::ostream &os, const Pilot &p);
};

#endif
