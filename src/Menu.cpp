#include <cstdlib>
#include <iostream>
#include <limits>
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
    std::cout << "| 4 - Articulation points       |\n";
    std::cout << "| 5 - Exit                      |\n";
    std::cout << "| ============================= |\n";
    std::cout << "| Please enter your choice:     |\n";
    std::cout << "+-------------------------------+\n";


    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 5 ) && !(std::cin.fail())) {
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
    }
    return 0;
}

//---- FLIGHTS ---- //
void Menu::flightsMenu() {
    std::cout << "Welcome to flights menu!" << std::endl;
    std::cout << "Here you'll be able to search for the best flight option from A to B!" << std::endl;
    std::cout << "To begin the search, you will have to input the origin and the destination places." << std::endl;

    std::cout << "+-------------------------------+\n";
    std::cout << "| Select type of origin:        |\n";
    std::cout << "| 1 - Airport (by code)         |\n";
    std::cout << "| 2 - Airport (by name)         |\n";
    std::cout << "| 3 - City                      |\n";
    std::cout << "| 4 - Country                   |\n";
    std::cout << "| 5 - Geographical coordinates  |\n";
    std::cout << "| 6 - Return to main menu       |\n";
    std::cout << "+-------------------------------+\n";


    std::string origin, dest;
    std::vector<std::string> filter = {};

    int oType;
    std::string oCode, oName, oCity, oCountry;
    std::string oLat, oLon;
    std::cin >> oType;
    switch (oType) {
        case 1:
            std::cout << "Input the airport IATA code: " << std::endl;
            std::cin >> oCode;
            origin = oCode;
            break;
        case 2:
            std::cout << "Input the airport name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, oName);
            origin = oName;
            break;

        case 3:
            std::cout << "Input the city name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, oCity);
            std::cout << std::endl;
            std::cout << "You also have to input the country name: " << std::endl;
            std::getline(std::cin >> std::ws, oCountry);

            origin = oCity + "," + oCountry;
            break;

        case 4:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::cout << "Input the country name: " << std::endl;
            std::getline(std::cin >> std::ws, oCountry); // Read the entire line, including spaces
            origin = oCountry;
            break;
        case 5:
            std::cout << "Input the latitude (double precision): " << std::endl;
            std::cin >> oLat;
            std::cout << std::endl;
            std::cout << "Input the longitude (double precision): " << std::endl;
            std::cin >> oLon;
            origin = oLat + "," + oLon;
            break;
        case 6:
            mainMenu();
            break;
        default:
            std::cout << "Invalid option. Please try again.";
    }

    std::cout << "+-------------------------------+\n";
    std::cout << "| Select type of destination:   |\n";
    std::cout << "| 1 - Airport (by code)         |\n";
    std::cout << "| 2 - Airport (by name)         |\n";
    std::cout << "| 3 - City                      |\n";
    std::cout << "| 4 - Country                   |\n";
    std::cout << "| 5 - Geographical coordinates  |\n";
    std::cout << "| 6 - Return to main menu       |\n";
    std::cout << "+-------------------------------+\n";

    int dType;
    std::string dCode, dName, dCity, dCountry;
    std::string dLat, dLon;
    std::cin >> dType;
    switch (dType) {
        case 1:
            std::cout << "Input the airport IATA code: " << std::endl;
            std::cin >> dCode;
            dest = dCode;
            break;
        case 2:
            std::cout << "Input the airport name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, dName);
            dest = dName;
            break;
        case 3:
            std::cout << "Input the city name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, dCity);
            std::cout << std::endl;
            std::cout << "You also have to input the country name: " << std::endl;
            std::getline(std::cin >> std::ws, dCountry);
            dest = dCity + "," + dCountry;
            break;
        case 4:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::cout << "Input the country name: " << std::endl;
            std::getline(std::cin >> std::ws, dCountry); // Read the entire line, including spaces
            dest = dCountry;
            break;
        case 5:
            std::cout << "Input the latitude (double precision): " << std::endl;
            std::cin >> dLat;
            std::cout << std::endl;
            std::cout << "Input the longitude (double precision): " << std::endl;
            std::cin >> dLon;
            dest = dLat + "," + dLon;
            break;
        case 6:
            mainMenu();
            break;
        default:
            std::cout << "Invalid option. Please try again.";
    }

    char fType;
    std::cout << "Do you wish to filter airlines?" << std::endl;
    std::cout << "If yes, input 'y'." << std::endl;
    std::cout << "If no, input 'n'." << std::endl;
    std::cin >> fType;
    std::string airline, aType, code;
    bool flag = true;

    switch(fType) {
        case 'n':
            manager.getFlightPath(origin, dest, oType, dType, filter, 0);
            break;
        case 'y':
            while (flag) {
                std::cout << "+-------------------------------+\n";
                std::cout << "| Select type of airline:       |\n";
                std::cout << "| 1 - Code                      |\n";
                std::cout << "| 2 - Name                      |\n";
                std::cout << "| 3 - Callsign                  |\n";
                std::cout << "| 4 - All from country          |\n";
                std::cout << "| DONE - when finished          |\n";
                std::cout << "+-------------------------------+\n";

                std::cin >> aType;
                if (aType == "DONE") {
                    flag = false;
                }
                else {
                    switch(aType[0]) {
                        case '1':
                            std::cout << "Insert airline code: " << std::endl;
                            std::cin >> airline;
                            if (manager.validAirlineCode(airline)) {
                                filter.push_back(airline);
                            }
                            else {
                                std::cout << "Invalid airline code." << std::endl;
                            }
                            break;
                        case '2':
                            std::cout << "Insert airline name: " << std::endl;
                            std::cin.ignore();
                            std::getline(std::cin, airline);

                            code = manager.getCodeFromName(airline);
                            if (!code.empty()) {
                                filter.push_back(code);
                            }
                            else {
                                std::cout << "Invalid airline code." << std::endl;
                            }
                            break;
                        case '3':
                            std::cout << "Insert airline callsign: " << std::endl;
                            std::cin.ignore();
                            std::getline(std::cin, airline);

                            code = manager.getCodeFromCallsign(airline);
                            if (!code.empty()) {
                                filter.push_back(code);
                            }
                            else {
                                std::cout << "Invalid airline callsign." << std::endl;
                            }
                            break;
                        case '4':
                            std::cout << "Insert country: " << std::endl;
                            std::cin.ignore();
                            std::getline(std::cin, airline);
                            filter = manager.filterCountry(airline);
                            if (filter.empty()) {
                                std::cout << "Invalid country." << std::endl;
                            }
                            break;
                        default:
                            std::cout << "Invalid option. Please try again." << std::endl;
                            break;
                    }
                }
            }

            int sType;
            std::cout << "+-------------------------------+\n";
            std::cout << "| Do you wish to...?            |\n";
            std::cout << "| 1 - Restrict search           |\n";
            std::cout << "| 2 - Exclude from search       |\n";
            std::cout << "+-------------------------------+\n";
            std::cin >> sType;

            switch(sType) {
                case 1:
                    manager.getFlightPath(origin, dest, oType, dType, filter, 1);
                    break;
                case 2:
                    manager.getFlightPath(origin, dest, oType, dType, filter, 2);
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }

            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
    }



}


//---- AIRPORTS ---- //

void Menu::airportsMenu() {
    std::string code;
    std::cout << "Insert an airport IATA code to proceed." << std::endl;
    std::cin >> code;
    if (manager.getAirports().find(code) == manager.getAirports().end()) {
        std::cout << "Airport not found. Are you sure you have the right IATA code?" << std::endl;
        airportsMenu();
    }
    std::cout << "+-------------------------------+\n";
    std::cout << "|==========="<<code<< " stats===========|\n";
    std::cout << "| 1 - Number of flights         |\n";
    std::cout << "| 2 - Number of airlines        |\n";
    std::cout << "| 3 - Number of destinations    |\n";
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

    while ((n < 1 || n > 4 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            std::cout << "There is a total of " << manager.flightsFromAirport(code) << " flights departing from " << code << std::endl;
            break;
        case 2:
            std::cout << "There is a total of " << manager.airlinesFromAirport(code) << " airlines operating in " << code << std::endl;
            std::cout << "Want to see the full list of airlines operating in " << code << "?" << std::endl;
            std::cout << "If so, input 'y' to see the full list." << std::endl;

            char op;
            std::cin >> op;
            std::cout << std::endl;

            if (std::cin.fail() || (op != 'y')) {
                airportsMenu();
                break;
            }
            else {
                manager.printAirlinesFromAirport(code);
                break;
            }
        case 3:
            std::cout << "There is a total of " << manager.cityDestinations(code) << " cities, " << manager.countryDestinations(code) << " countries and " << manager.airportDestinations(code) << " airports you can fly to from " << code << std::endl;

            std::cout << "Want to see the full list of cities or countries you can fly to from " << code << "?" << std::endl;
            std::cout << std::endl;
            std::cout << "To see the full list of cities, input 'y' (displayed with respective country) or input 'n' for just the city names." << std::endl;
            std::cout << std::endl;
            std::cout << "If you wish to see the country list, please input 'c'." << std::endl;
            std::cout << std::endl;
            std::cout << "Want to see the airport list? Input 'a'." << std::endl;

            char op2;
            std::cin >> op2;
            std::cout << std::endl;

            if (std::cin.fail()) {
                throw std::invalid_argument(
                        "Error 001: Your input was not an integer. Please restart the program and try again.");
            } else if (std::cin.fail() || (op2 != 'y' && op2 != 'n' && op2 != 'c' && op2 != 'a')) {
                airportsMenu();
                break;
            }
            else if (op2 == 'c') {
                manager.printCountryDestinations(code);
                break;
            }
            else if (op2 == 'a') {
                std::cout << std::endl;
                std::cout << "There are 3 ways of showing the airport list." << std::endl;
                std::cout << std::endl;
                std::cout << "Input 'a' to show: code, name, city, country and coordinates." << std::endl;
                std::cout << "Input 'b' to show: code, name, city and country." << std::endl;
                std::cout << "Input 'c' to show: code and name." << std::endl;


                char op3;
                std::cin >> op3;
                std::cout << std::endl;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
                } else if (!(std::cin.fail()) || (op3 != 'a' && op3 != 'b' && op3 != 'c')) {
                    airportsMenu();
                    break;
                } else {
                    manager.printAirportDestinations(code, op3);
                    break;
                }
            }
            else {
                manager.printCityDestinations(code, op2);
                break;
            }
    }
}

// ---- DATA/STATISTICS ----

void Menu::statsMenu() {
    std::cout << "+-----------------------------------------+\n";
    std::cout << "| ============  Stats Menu   =============|\n";
    std::cout << "| 1 - Global stats                        |\n";
    std::cout << "| 2 - Flights per city                    |\n";
    std::cout << "| 3 - Flights per airline                 |\n";
    std::cout << "| 4 - Airports with topK number of flights|\n";
    std::cout << "| 5 - Destinations Within Stops           |\n";
    std::cout << "| 6 - Return to main menu                 |\n";
    std::cout << "| ========================================|\n";
    std::cout << "| Please enter your choice:               |\n";
    std::cout << "+-----------------------------------------+\n";

    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 6 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }
    std::string nameCity;
    std::string nameAirline;
    std::string startAirport;
    int maxStops;

    switch(n) {
        case 1:
            globalStatsMenu();
            break;
        case 2:
            std::cout << "Write an City's name";
            std::cin >> nameCity;
            std::cout << "\n";

            manager.flightsPerCity(nameCity);
            break;
        case 3:
            std::cout << "Write an Airline's name" <<std::endl;

            std::cin >> nameAirline;
            std::cout << "\n";

            manager.flightsPerAirline(nameAirline);
            break;
        case 4:
            std::cout << "Select the number of airports: " << std::endl;
            int op;
            std::cin >> op;
            std::cout << std::endl;

            manager.topKAirports(op);
            break;
        case 5:
            std::cout << "Write an Airport's name" <<std::endl;
            std::cin >> startAirport;
            std::cout <<"Write the maximum stops" <<std::endl;
            std::cin >> maxStops;
            manager.destinationsWithinStops(startAirport,maxStops);
            break;
        case 6:
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

    while ((n < 1 || n > 4) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            std::cout << "There is a total of " << manager.globalAirports() << " airports in our database." << std::endl;
            std::cout << "Want to see the full list of airports?" << std::endl;
            std::cout << std::endl;
            std::cout << "If so, input 'c' for code, 'n' for name or 'a' for code and name to see the full lists." << std::endl;
            std::cout << std::endl;
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
            std::cout << std::endl;
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
            globalStatsMenu();
    }
}

//--- MISCS ----

void Menu::miscMenu() {
    std::cout << "Want to show the list of articulation points along with the total number?" << std::endl;
    std::cout << "If yes, input 'y', if no, input anything else." << std::endl;
    std::cout << std::endl;

    char typ;
    std::cin >> typ;
    if (std::cin.fail()) {
        miscMenu();
    }
    else {
        manager.printArticulation(typ);
    }
}






