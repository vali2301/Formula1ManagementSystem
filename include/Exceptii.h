#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class CampionatException : public std::exception {
private:
    std::string mesaj;

public:
    CampionatException(const std::string &msg) : mesaj(msg) {
    }


    virtual const char *what() const noexcept override {
        return mesaj.c_str();
    }
};


class EroarePilotInvalid : public CampionatException {
public:
    EroarePilotInvalid(const std::string &msg) : CampionatException(msg) {
    }
};


class EroareOptiuneMeniu : public CampionatException {
public:
    EroareOptiuneMeniu(const std::string &msg) : CampionatException(msg) {
    }
};


class EroareSimulareCursa : public CampionatException {
public:
    EroareSimulareCursa(const std::string &msg) : CampionatException(msg) {
    }
};

#endif
