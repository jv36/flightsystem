#ifndef FLIGHTSYSTEM_LOCATION_H
#define FLIGHTSYSTEM_LOCATION_H


class Location {
public:
    Location();
    Location(double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;
    static double toRadians(double degrees);
    double calculateDistance(const Location &other) const;
private:
    double latitude; /*brief valor da latitude, double precision*/
    double longitude; /*brief valor da longitude, double precision*/
};

#endif //FLIGHTSYSTEM_LOCATION_H
