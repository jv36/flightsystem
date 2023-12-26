//
// Created by joaomendes on 01-12-2023.
//

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
};


#endif //FLIGHTSYSTEM_MENU_H
