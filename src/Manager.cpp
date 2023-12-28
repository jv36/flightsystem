#include "Manager.h"
#include <memory>
#include <unordered_set>
#include <set>
#include <algorithm>

void Manager::printflightGraph() {
    for (auto& node : flightGraph->nodes) {
        std::cout << node.first <<std::endl;
    }
}

void Manager::parseAirlines() {
    std::ifstream file("../csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    std::string line;
    //Code,Name,Callsign,Country
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        auto airline = new Airline(code, name, callsign, country);
        airlines.insert({code, airline});
    }

    // Teste print
    /*
      for (const auto& name : airlines) {
        std::cout << name.second->getName() << std::endl;
    }
    std::cout << "There are " << airlines.size() << " airlines in our database.";
     */
}

 void Manager::parseAirport() {
     std::ifstream file("../csv/airports.csv");

     if (!file.is_open()) {
         std::cerr << "Error opening file!" << std::endl;
         return;
     }

     std::string line;

     //Code,Name,City,Country,Latitude,Longitude
     getline(file, line);

     while (getline(file, line)) {
         std::istringstream iss(line);
         std::string code, name, city, country, latitude, longitude;

         getline(iss, code, ',');
         getline(iss, name, ',');
         getline(iss, city, ',');
         getline(iss, country, ',');
         getline(iss, latitude, ',');
         getline(iss, longitude,',');
         double lat = std::stod(latitude);
         double lon = std::stod(longitude);

         Location location = Location(lat, lon);
         auto airport = new Airport(code, name, city, country, location);
         airports.insert({code, airport});

         bool exists = false;
         for(auto it: airportLocations){
             if(it.first == code){
                 exists = true;
                 break;
             }
         }
         if(!exists){ airportLocations.emplace_back(code, location);}
         cities.insert({code, {city, country}});
     }
    /*
     * * print testing
      for (const auto& code : airports) {
         std::cout << code.second->getLocation().getLatitude() << "-" << code.second->getLocation().getLongitude() << std::endl;
     }

     std::cout << "There are " << airports.size() << " airports in our database.";
    */
}

void Manager::parseFlights() {
    std::ifstream file("../csv/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;

    flightGraph = new Graph(airports.size(), false);
    for (auto & airport : airports) {
        flightGraph->addNode(airport.first, airport.second);
    }

    //Source,Target,Airline
    getline(file, line);

    while (getline(file, line)) {
        globalFlights++;
        std::istringstream iss(line);
        std::string source, target, airline;

        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, ',');
        flightGraph->addEdge(source, target, airline);
    }
}

std::unordered_map<std::string, Airline *> Manager::getAirlines() {
    return airlines;
}

std::unordered_map<std::string, Airport *> Manager::getAirports() {
    return airports;
}


// AIRPORT MENU

unsigned long Manager::flightsFromAirport(const std::string& code) {
    return flightGraph->nodeAtKey(code).adj.size();
}

unsigned long Manager::airlinesFromAirport(const std::string& code) {
    std::set<std::string> airList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        airList.insert(edge.airline);
    }
    return airList.size();
}

void Manager::printAirlinesFromAirport(const std::string& code) {
    std::set<std::string> airList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        airList.insert(edge.airline);
    }

    for (const auto& airline : airList) {
        std::cout << airline << std::endl;
    }
}

unsigned long Manager::cityDestinations(const std::string& code) {
    std::set<std::pair<std::string, std::string>> cityList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        cityList.insert({airport->getCity(), airport->getCountry()});
    }
    return cityList.size();
}

void Manager::printCityDestinations(const std::string& code, const char& type) {
    std::set<std::pair<std::string, std::string>> cityList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        cityList.insert({airport->getCity(), airport->getCountry()});
    }

    if (type == 'y') {
        for (const auto &city: cityList) {
            std::cout << city.first << " - " << city.second << std::endl;
        }
    }
    else if (type == 'n') {
        for (const auto& city : cityList) {
            std::cout << city.first << std::endl;
        }
    }
    else {
        return;
    }

}

unsigned long Manager::countryDestinations(const std::string& code) {
    std::set<std::string> countryList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        countryList.insert(airport->getCountry());
    }
    return countryList.size();
}

void Manager::printCountryDestinations(const std::string& code) {
    std::set<std::string> countryList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        countryList.insert(airport->getCountry());
    }

    for (const auto& country : countryList) {
        std::cout << country << std::endl;
    }
}

unsigned long Manager::airportDestinations(const std::string& code) {
    std::set<Airport*> airportList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        airportList.insert(airport);
    }

    return airportList.size();

}

void Manager::printAirportDestinations(const std::string& code, const char& type) {
    std::set<Airport*> airportList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        Airport* airport = airports.at(edge.destination);
        airportList.insert(airport);
    }

    if (type == 'a') {
        for (const auto& air : airportList) {
            std::cout << air->getCode() << " - " << air->getName() << " - " << air->getCity() << ", " << air->getCountry() << " - " << "(" << air->getLocation().getLatitude() << "," << air->getLocation().getLongitude() << ")" << std::endl;
        }
    }
    else if (type == 'b') {
        for (const auto& air : airportList) {
            std::cout << air->getCode() << " - " << air->getName() << " - " << air->getCity() << ", " << air->getCountry() << std::endl;
        }
    }
    else if (type == 'c') {
        for (const auto& air : airportList) {
            std::cout << air->getCode() << " - " << air->getName() << std::endl;
        }
    }
    else {
        return;
    }
}
//  STATISTICS MENU

void Manager::flightsPerCity(const std:: string& nameCity) {
    std::string CityCode;

    for (const auto &city: cities) {
        flightsCity[city.first] = 0;
        if (city.second.first == nameCity) {
            CityCode = city.first;
        }
    }

    if (CityCode.empty()) {
        std::cout << "City not found " << std::endl;
        return;
    }

    for (const auto &airport: airports) {
        const std::string &airportCode = airport.first;
        for (const auto &edge: flightGraph->nodeAtKey(airportCode).adj) {
            flightsCity[edge.destination]++;
        }
    }
}

void Manager::flightsPerAirline(const std:: string& nameAirline) {
    std::string AirlineCode;

    for (const auto &airline: airlines) {
        flightsAirline[airline.first] = 0;
        if (airline.second->getName() == nameAirline) {
            AirlineCode = airline.first;
        }
    }

    if (AirlineCode.empty()) {
        std::cout << "Airline not found " << std::endl;
        return;
    }

    for (const auto &airport: airports) {
        const std::string &airportCode = airport.first;
        for (const auto &edge: flightGraph->nodeAtKey(airportCode).adj) {
            flightsAirline[edge.airline]++;
        }
    }

    std::cout << "There are " << flightsAirline[AirlineCode] << " flights operated by " << nameAirline << std::endl;
}
// void Manager::

//                      GLOBAL STATS

unsigned long Manager::globalAirports() {
    return airports.size();
}

void Manager::printGlobalAirports(const char& type) {
    if (type == 'n') {
        for (const auto& airport: airports) {
            std::cout << airport.second->getName() << std::endl;
        }
    }
    else if (type == 'c') {
        for (const auto& airport : airports) {
            std::cout << airport.second->getCode() << std::endl;
        }
    }
    else if (type == 'a') {
        for (const auto& airport : airports) {
            std::cout << airport.second->getCode() << " - " << airport.second->getName() << std::endl;
        }
    }
    else {
        return;
    }
}

unsigned long Manager::globalAirlines() {
    return airlines.size();
}

void Manager::printGlobalAirlines() {
    for (const auto& airline : airlines) {
        std::cout << airline.second->getCode() << " - " << airline.second->getName() << " - " << airline.second->getCallsign() << " - " << airline.second->getCountry() << std::endl;
    }
}

void Manager::topKAirports(int k) {
    std::vector<std::pair<Airport*, int>> allAirports;
    for (const auto& airport : airports) {
        allAirports.push_back({airport.second, flightGraph->nodeAtKey(airport.first).adj.size()});
    }

    std::sort(allAirports.begin(), allAirports.end(), [](const auto& p1, const auto& p2) {
        return p1.second > p2.second;
    });

    for (int i = 0; i < k; i++) {
        std::cout << allAirports[i].first->getCode() << " - " << allAirports[i].first->getName() << " with " << allAirports[i].second << " flights;" << std::endl;
    }
}

void Manager::destinationsWithinStops(const std::string& startAirport, int maxStops){
    std::queue<std::pair<std::string ,int>> q;
    q.push({startAirport,0});

    std::unordered_set<std::string > visitedAirports;
    std::unordered_set<std::string > visitedCities;
    std::unordered_set<std::string > visitedCountries;

    while (!q.empty()){
        auto top=q.front();
        q.pop();

        std::string topAirportCode = top.first;
        int stops = top.second;

        if(stops > maxStops) { continue;}

        visitedAirports.insert(topAirportCode);

        for(const auto& edge : flightGraph->nodeAtKey(topAirportCode).adj){
            std::string destinationAirportCode = edge.destination;
            Airport* destinationAirport = airports.at(destinationAirportCode);

            visitedAirports.insert(destinationAirportCode);
            visitedCities.insert(destinationAirport->getCity());
            visitedCountries.insert(destinationAirport->getCountry());

            q.push({destinationAirportCode,stops + 1});
        }
    }

}






