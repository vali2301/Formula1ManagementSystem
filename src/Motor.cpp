#include "Motor.h"
#include <cstring>
#include <algorithm>

Motor::Motor(const std::string &prod, int cp, const std::string &spec)
    : producator(prod), putereCP(cp) {
    specificatii = new char[spec.length() + 1];
    std::strcpy(specificatii, spec.c_str());
}

Motor::~Motor() {
    delete[] specificatii;
}

Motor::Motor(const Motor &other)
    : producator(other.producator), putereCP(other.putereCP) {
    specificatii = new char[std::strlen(other.specificatii) + 1];
    std::strcpy(specificatii, other.specificatii);
}


void swap(Motor &first, Motor &second) {
    using std::swap;
    swap(first.producator, second.producator);
    swap(first.putereCP, second.putereCP);
    swap(first.specificatii, second.specificatii);
}

Motor &Motor::operator=(Motor other) {
    swap(*this, other);
    return *this;
}
