#include "Flight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>

/*
 * @brief Construtor da classe Flight.
 * @details Complexity: O(1)
 */
Flight::Flight() {
    this->source = "";
    this->target = "";
    this->airline = "";
}

/*
 * @brief Construtor da classe Flight que recebe o local de partida, o de destino e a companhia aérea.
 * @details Complexity: O(1)
 * @param source: local de origem
 * @param target: local de destino
 * @param airline: companhia aérea
 */
Flight::Flight(std::string source, std::string target, std::string airline) {
    this->source = source;
    this->target = target;
    this->airline = airline;
}

/*
 * @brief Obtém o código do aeroporto do local de origem.
 * @details Complexity: O(1)
 * @return O código do aeroporto de origem.
 */
std::string Flight::getSource() const {
    return source;
}

/*
 * @brief Obtém o código do aeroporto do local de destino.
 * @details Complexity: O(1)
 * @return O código do aeroporto de destino.
 */
std::string Flight::getTarget() const {
    return target;
}

/*
 * @brief Obtém o código da companhia aérea responsável pelo voo.
 * @details Complexity: O(1)
 * @return O código da companhia aérea do voo.
 */
std::string Flight::getAirline() const {
    return airline;
}






// não sei o que é isto não vou mexer - vicente
//---- aux --- //
float toRadians(float degree) {
    return degree * (M_PI / 180.0);
}

float Flight::getDistance(Location source, Location dest) {

    const float EARTH_RADIUS = 6371.0;
    float sc_lat = toRadians(source.getLatitude());
    float dest_lat = toRadians(dest.getLatitude());

    float dLat = toRadians(dest.getLatitude()) - toRadians(source.getLatitude());
    float dLon = toRadians(dest.getLongitude()) - toRadians(source.getLongitude());

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(sc_lat) * cos(dest_lat) *
              sin(dLon / 2) * sin(dLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    float distance = EARTH_RADIUS * c;

    return distance;
}

