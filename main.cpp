#include "Meniu.h"
#include "Exceptii.h"
#include <iostream>

int main() {
    try {
        Meniu meniu;
        meniu.ruleaza();
    } catch (const EroarePilotInvalid &e) {
        std::cerr << "\n[EROARE FATALA DE INPUT] Programul se va opri.\n";
        std::cerr << "Detalii: " << e.what() << "\n";
        return 1;
    } catch (const CampionatException &e) {
        std::cerr << "\n[EROARE CAMPIONAT] O exceptie interna neasteptata a cauzat oprirea programului.\n";
        std::cerr << "Detalii: " << e.what() << "\n";
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "\n[EROARE SISTEM] Exceptie standard C++ neasteptata: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
