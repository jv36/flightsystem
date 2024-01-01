#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

/**
 * @brief Construtor da classe Airport que recebe um código do aeroporto.
 * @details Complexity: O(1)
 * @param code: código do aeroporto
 */
Airport::Airport(std::string code) : code(code){
}

/**
 * @brief Construtor da classe Airport que recebe um código, um nome, uma cidade, um país e uma localizaçãp
 * @details Complexity: O(1)
 * @param code: código do aeroporto
 * @param name: nome do aeroporto
 * @param city: cidade do aeroporto
 * @param country: país do aeroporto
 * @param location: localização do aeroporto (lat, lon)
 */
Airport::Airport(std::string code, std::string name, std::string city, std::string country, Location location) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->location = location;
}

/**
 * @brief Obtém o código do aeroporto.
 * @details Complexity: O(1)
 * @return O código do aeroporto.
 */
std::string Airport::getCode() const {
    return code;
}

/**
 * @brief Obtém o nome do aeroporto.
 * @details Complexity: O(1)
 * @return O nome do aeroporto.
 */
std::string Airport::getName() const {
    return name;
}

/**
 * @brief Obtém a cidade do aeroporto.
 * @details Complexity: O(1)
 * @return A cidade do aeroporto.
 */
std::string Airport::getCity() const {
    return city;
}

/**
 * @brief Obtém o país do aeroporto.
 * @details Complexity: O(1)
 * @return O país do aeroporto.
 */
std::string Airport::getCountry() const {
    return country;
}

/**
 * @brief Obtém a localização do aeroporto.
 * @details Complexity: O(1)
 * @return A localização do aeroporto, como objeto da classe Location(latitude, longitude).
 */
Location Airport::getLocation() const {
    return location;
}
