#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <string>
#include <utility>

class CampionatException : public std::exception {
private:
    std::string mesaj;

public:
    explicit CampionatException(std::string msg) : mesaj(std::move(msg)) {
    }


    [[nodiscard]] const char *what() const noexcept override {
        return mesaj.c_str();
    }
};


class EroarePilotInvalid : public CampionatException {
public:
    explicit EroarePilotInvalid(const std::string &msg) : CampionatException(msg) {
    }
};


class EroareOptiuneMeniu : public CampionatException {
public:
    explicit EroareOptiuneMeniu(const std::string &msg) : CampionatException(msg) {
    }
};


class EroareSimulareCursa : public CampionatException {
public:
    explicit EroareSimulareCursa(const std::string &msg) : CampionatException(msg) {
    }
};

#endif
