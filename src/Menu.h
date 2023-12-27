#ifndef FLIGHTSYSTEM_MENU_H
#define FLIGHTSYSTEM_MENU_H

#include "Manager.h"
#include "Airport.h"
class Menu {
private:
    Manager manager;
public:

    int main();

    int mainMenu();

    void flightsMenu();

    void airportsMenu();

    void statsMenu();

    void miscMenu();

    void globalStatsMenu();
};

#endif //FLIGHTSYSTEM_MENU_H
