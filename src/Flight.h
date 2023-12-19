//
// Created by joaomendes on 01-12-2023.
//

#ifndef FLIGHTSYSTEM_FLIGHT_H
#define FLIGHTSYSTEM_FLIGHT_H


#include <string>
#include <vector>

class Flight {
public:
    Flight();
    Flight(std::string source, std::string target, std::string airline); //distance?

    const std::string& getSource() const;
    const std::string& getTarget() const;
    float getDistance() const;
    const std::string getAirline() const;
    const std::vector<std::string>& getAirlines() const;

    void setSource(const std::string& source);
    void setTarget(const std::string& target);
    void setDistance(float distance);

    void addAirline(std::string airlineCode);

    void parseFlights(const std::string& filename, std::unordered_map<std::string, std::unique_ptr<Flight>>& flightMap);


private:
    std::string source;
    std::string target;
    std::string airline;
    std::vector<std::string> airlines; // pode haver + que 1 companhia a voar para o mesmo destino
    float distance;
};


#endif //FLIGHTSYSTEM_FLIGHT_H
