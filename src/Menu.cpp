//
// Created by joaomendes on 01-12-2023.
//

#include <cstdlib>
#include <iostream>
#include "Manager.h"

#include "Menu.h"

int Menu::main() {
    system("clear");
    manager.parseAirport();
    manager.parseAirlines();
    manager.parseFlights();
    mainMenu();
    return 0;
}

int Menu::mainMenu() {
    std::cout << "███████╗██╗░░░░░██╗░██████╗░██╗░░██╗████████╗  ░██████╗██╗░░░██╗░██████╗████████╗███████╗███╗░░░███╗" << std::endl;
    std::cout << "██╔════╝██║░░░░░██║██╔════╝░██║░░██║╚══██╔══╝  ██╔════╝╚██╗░██╔╝██╔════╝╚══██╔══╝██╔════╝████╗░████║" << std::endl;
    std::cout << "█████╗░░██║░░░░░██║██║░░██╗░███████║░░░██║░░░  ╚█████╗░░╚████╔╝░╚█████╗░░░░██║░░░█████╗░░██╔████╔██║" << std::endl;
    std::cout << "██╔══╝░░██║░░░░░██║██║░░╚██╗██╔══██║░░░██║░░░  ░╚═══██╗░░╚██╔╝░░░╚═══██╗░░░██║░░░██╔══╝░░██║╚██╔╝██║" << std::endl;
    std::cout << "██║░░░░░███████╗██║╚██████╔╝██║░░██║░░░██║░░░  ██████╔╝░░░██║░░░██████╔╝░░░██║░░░███████╗██║░╚═╝░██║" << std::endl;
    std::cout << "╚═╝░░░░░╚══════╝╚═╝░╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░  ╚═════╝░░░░╚═╝░░░╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░░░░╚═╝" << std::endl;

    std::cout << "+-------------------------------+\n";
    std::cout << "| Welcome to the Flight System  |\n";
    std::cout << "|                               |\n";
    std::cout << "| Our menu works based on       |\n";
    std::cout << "| number inputs! i.e., for      |\n";
    std::cout << "| option 1, please input 1 in   |\n";
    std::cout << "| the terminal.                 |\n";
    std::cout << "|                               |\n";
    std::cout << "| ========== Main Menu =========|\n";
    std::cout << "| 1 - Flights                   |\n";
    std::cout << "| 2 - Airports                  |\n";
    std::cout << "| 3 - Data/Statistics           |\n";
    std::cout << "| 4 - Misc                      |\n";
    std::cout << "| 5 - Exit                      |\n";
    std::cout << "| ============================= |\n";
    std::cout << "| Please enter your choice:    |\n";
    std::cout << "+-------------------------------+\n";


    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while (n < 1 || n > 5) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch (n) {
        case 1:
            flightsMenu();
            break;
        case 2:
            airportsMenu();
            break;
        case 3:
             statsMenu();
             break;
        case 4:
            miscMenu();
            break;
        case 5:
            std::cout << "Terminating program. Goodbye!";
            exit(0);
        default:
            std::cout << "Invalid option. Please try again.";
    }
    return 0;
}

void Menu::flightsMenu() {
    std::cout << "Welcome to flights menu.";
    manager.printGraph();
}

void Menu::airportsMenu() {
    std::cout << "Welcome to airports menu.";
}

void Menu::statsMenu() {
    std::cout << "+-------------------------------+\n";
    std::cout << "| ========== Stats Menu ========|\n";
    std::cout << "| 1 - Global stats              |\n";
    std::cout << "| 2 - Placeholder               |\n";
    std::cout << "| 3 - Placeholder               |\n";
    std::cout << "| 4 - Placeholder               |\n";
    std::cout << "| 5 - Return to main menu       |\n";
    std::cout << "| ============================= |\n";
    std::cout << "| Please enter your choice:     |\n";
    std::cout << "+-------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while (n < 1 || n > 5) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            globalStatsMenu();
            break;
        case 5:
            mainMenu();
            break;
        default:
            std::cout << "Invalid option. Please try again.";
    }
}

void Menu::globalStatsMenu() {
    std::cout << "+-------------------------------+\n";
    std::cout << "| ========= Global Stats =======|\n";
    std::cout << "| 1 - Global number of airports |\n";
    std::cout << "| 2 - Global number of flights  |\n";
    std::cout << "| 3 - Global number of airlines |\n";
    std::cout << "| 4 - Return to main menu       |\n";
    std::cout << "| ============================= |\n";
    std::cout << "| Please enter your choice:     |\n";
    std::cout << "+-------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while (n < 1 || n > 4) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            std::cout << "There is a total of " << manager.globalAirports() << " airports in our database." << std::endl;
            std::cout << "Want to see the full list of airports?" << std::endl;
            std::cout << "If so, input 'c' for code, 'n' for name or 'a' for code and name to see the full lists." << std::endl;
            std::cout << "If no, just input anything else and press enter." << std::endl;

            char op;
            std::cin >> op;
            std::cout << std::endl;

            if (std::cin.fail() || (op != 'c' && op != 'n' && op != 'a')) {
                globalStatsMenu();
                break;
            }
            else {
                manager.printGlobalAirports(op);
                break;
            }
        case 2:
            std::cout << "There is a total of " << manager.globalFlights << " flights in our database." << std::endl;
            break;
        case 3:
            std::cout << "There is a total of " << manager.globalAirlines() << " airlines in our database." << std::endl;
            std::cout << "Want to see the full list of airlines?" << std::endl;
            std::cout << "If so, input 'y' to see the full list." << std::endl;

            char op2;
            std::cin >> op2;
            std::cout << std::endl;

            if (std::cin.fail() || (op2 != 'y')) {
                globalStatsMenu();
                break;
            }
            else {
                manager.printGlobalAirlines();
                break;
            }
        case 4:
            mainMenu();
            break;
        default:
            std::cout << "Invalid option. Please try again.";
    }
}

void Menu::miscMenu() {
    std::cout << "Welcome to misc menu.";
    std::cout << "Teste";
}






