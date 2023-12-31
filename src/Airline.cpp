#include "Airline.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

/*
 * @brief Construtor da classe Airline que recebe um código de companhia aérea.
 * @details Complexity: O(1)
 * @param code: código da companhia aérea
 */
Airline::Airline(std::string code) : code(code){
}

/*
 * @brief Construtor da classe Airline que recebe um código, um nome, um callsign e um país
 * @details Complexity: O(1)
 * @param code: código da companhia aérea
 * @param name: nome da companhia aérea
 * @param callsign: callsign da companhia aérea
 * @param country: país da companhia aérea
 */
Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) :
    code(code), callsign(callsign), name(name), country(country){
}

/*
 * @brief Obtém o código da companhia aérea.
 * @details Complexity: O(1)
 * @return O código da companhia aérea.
 */
std::string Airline::getCode() const {
    return code;
}

/*
 * @brief Obtém o nome da companhia aérea.
 * @details Complexity: O(1)
 * @return O nome da companhia aérea.
 */
std::string Airline::getName() const {
    return name;
}

/*
 * @brief Obtém o callsign da companhia aérea.
 * @details Complexity: O(1)
 * @return O callsign da companhia aérea.
 */
std::string Airline::getCallsign() const {
    return callsign;
}

/*
 * @brief Obtém o país da companhia aérea.
 * @details Complexity: O(1)
 * @return O país da companhia aérea.
 */
std::string Airline::getCountry() const {
    return country;
}

