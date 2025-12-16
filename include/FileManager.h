#pragma once
#include <string>
#include <vector>
#include "Echipa.h"

class FileManager {
public:
    static std::vector<Echipa> citesteEchipe();
    static std::vector<std::string> citesteCircuite();
    static std::vector<std::pair<std::string, std::string>> citesteInfoCircuite();

private:
    static std::string cale(const std::string& fisier);
};
