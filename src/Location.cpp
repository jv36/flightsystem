#include "Location.h"
#include <cmath>

/**
 * @brief Construtor da classe Location.
 * @brief Inicializa uma localização vazia.
 * @details Complexity: O(1)
 */
Location::Location() {
    this->latitude = 0.0;
    this->longitude = 0.0;
}

/**
 * @brief Construtor da classe Location que recebe valores de latitude e longitude.
 * @brief Inicializa uma localização através destes valores.
 * @details Complexity: O(1)
 * @param latitude: valor da latitude
 * @param longitude: valor da longitude
 */
Location::Location(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

/**
 * @brief Obtém o valor da latitude.
 * @details Complexity: O(1)
 * @return O valor da latitude, em double.
 */
double Location::getLatitude() const {
    return latitude;
}

/**
 * @brief Obtém o valor da longitude.
 * @details Complexity: O(1)
 * @return O valor da longitude, em double.
 */
double Location::getLongitude() const {
    return longitude;
}

/**
 * @brief Converte um ângulo em graus para radianos.
 * @details Complexity: O(1)
 * @return O valor do ângulo em radianos.
 */
double Location::toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

/**
 * @brief Calcula a distância em quilómetros entre duas localizações.
 * @brief Adaptação da Haversine formula.
 * @details Complexity: O(1)
 * @param other: a outra localização para calcular a distância.
 * @return O valor da distância em kms, em double.
 */
double Location::calculateDistance(const Location& other) const {
    // Haversine formula
    const double R = 6371.0; // raio da terra

    double lat1 = toRadians(latitude);
    double lon1 = toRadians(longitude);
    double lat2 = toRadians(other.getLatitude());
    double lon2 = toRadians(other.getLongitude());

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2.0) * std::sin(dlon / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return R * c; // em kms
}
