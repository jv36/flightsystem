cmake_minimum_required(VERSION 3.26)
project(flightsystem)

set(CMAKE_CXX_STANDARD 17)
#add_executable(flightsystem main.cpp src/Manager.cpp src/Menu.cpp src/Location.cpp src/Flight.cpp src/Airport.cpp src/Airline.cpp src/Graph.cpp)

add_executable(flightsystem main.cpp
        src/Manager.h
        src/Manager.cpp
        src/Menu.h
        src/Menu.cpp
        src/Location.h
        src/Location.cpp
        src/Flight.h
        src/Flight.cpp
        src/Airport.h
        src/Airport.cpp
        src/Airline.h
        src/Airline.cpp
        src/Graph.cpp
        src/Graph.h
)
