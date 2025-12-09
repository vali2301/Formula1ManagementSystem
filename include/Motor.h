#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <string>

class Motor {
private:
    std::string producator;
    int putereCP;
    char* specificatii;

public:
    Motor(const std::string& prod, int cp, const std::string& spec);
    ~Motor();

    // rof
    Motor(const Motor& other);
    Motor& operator=(Motor other);

    friend void swap(Motor& first, Motor& second);

    const std::string& getProducator() const { return producator; }
};

#endif