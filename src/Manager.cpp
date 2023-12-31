#include "Manager.h"
#include <unordered_set>
#include <set>
#include <algorithm>

/**
 * @brief Faz parse ao ficheiro airlines.csv e coloca os seus dados nas estruturas adequadas.
 * @details Complexity: O(N*M)
 * @details N - número de linhas no ficheiro
 * @details M - comprimento médio de cada linha
 */
void Manager::parseAirlines() {
    std::ifstream file("../csv/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    std::string line;
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
}


/**
 * @brief Faz parse ao ficheiro airports.csv e coloca os seus dados nas estruturas adequadas.
 * @details Complexity: O(N*M)
 * @details N - número de linhas no ficheiro
 * @details M - comprimento médio de cada linha
 */
 void Manager::parseAirport() {
     std::ifstream file("../csv/airports.csv");

     if (!file.is_open()) {
         std::cerr << "Error opening file!" << std::endl;
         return;
     }

     std::string line;

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
}

/**
 * @brief Faz parse ao ficheiro flights.csv e coloca os seus dados nas estruturas adequadas.
 * @details Complexity: O(N*M)
 * @details N - número de linhas no ficheiro
 * @details M - comprimento médio de cada linha
 */
void Manager::parseFlights() {
    std::ifstream file("../csv/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string line;

    flightGraph = new Graph(airports.size(), true);
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

/**
 * @brief Obtém o unordered map dos aeroportos {código, Airport*}.
 * @details Complexity: O(1)
 * @return Unordered map dos aeroportos.
 */
std::unordered_map<std::string, Airport *> Manager::getAirports() {
    return airports;
}

//Flights

/**
 * @brief Obtém as melhores opções de voos de A até B.
 * @brief Utiliza a função Graph::createPath e imprime estes mesmos caminhos.
 * @brief Caso não haja voos, uma mensagem é apresentada ao utilizador.
 * @param origin: local de origem
 * @param destination: local de destino
 * @param oType: tipo de origem (aeroporto (nome ou IATA), cidade, país ou coordenadas geográficas)
 * @param dType: tipo de destino (aeroporto (nome ou IATA), cidade, país ou coordenadas geográficas)
 * @param filter: filtro de companhias aéreas
 * @param type: tipo de pesquisa (0: sem aplicar filtro, 1: restringe pesquisa às companhias do filtro, 2: exclui da pesquisa companhias do filtro)
 */
void Manager::getFlightPath(std::string origin, std::string destination, int oType, int dType, std::vector<std::string>& filter, int type) {
    std::vector<std::string> airportO;
    std::vector<std::string> airportD;
    std::vector<std::vector<std::string>> paths = {};

    // Origin++
    switch (oType) {
        case 1:
            airportO.push_back(origin);
            break;
        case 2:
            for (const auto& ap : airports) {
                if (ap.second->getName() == origin) {
                    airportO.push_back(ap.second->getCode());
                    break;
                }
            }
            break;
        case 3:
            for (const auto& ap : airports) {
                std::vector<std::string> tokens;
                std::string token;
                std::istringstream iss(origin);

                while (std::getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                if (ap.second->getCity() == tokens[0] && ap.second->getCountry() == tokens[1]) {
                    airportO.push_back(ap.second->getCode());
                }
            }
            break;
        case 4:
            for (auto ap : airports) {
                if (ap.second->getCountry() == origin) {
                    airportO.push_back(ap.second->getCode());
                }
            }
            break;
        case 5:
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream iss(origin);

            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            auto cOrigin = Location(std::stod(tokens[0]), std::stod(tokens[1]));

            std::pair<std::string, double> closestAirport = {airportLocations[0].first, cOrigin.calculateDistance(airportLocations[0].second)};

            for (const auto& airport : airportLocations) {
                if (airport.second.calculateDistance(cOrigin) <= closestAirport.second) {
                    closestAirport = {airport.first, cOrigin.calculateDistance(airport.second)};
                }
            }

            airportO.push_back(closestAirport.first);
            break;
    }

    // Destination
    switch (dType) {
        case 1:
            airportD.push_back(destination);
            break;
        case 2:
            for (const auto& ap : airports) {
                if (ap.second->getName() == destination) {
                    airportD.push_back(ap.second->getCode());
                    break;
                }
            }
            break;
        case 3:
            for (const auto& ap : airports) {
                std::vector<std::string> tokens;
                std::string token;
                std::istringstream iss(destination);

                while (std::getline(iss, token, ',')) {
                    tokens.push_back(token);
                }

                if (ap.second->getCity() == tokens[0] && ap.second->getCountry() == tokens[1]) {
                    airportD.push_back(ap.second->getCode());
                }
            }
            break;
        case 4:
            for (auto ap : airports) {
                if (ap.second->getCountry() == destination) {
                    airportD.push_back(ap.second->getCode());
                }
            }
            break;
        case 5:
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream iss(destination);

            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            auto cOrigin = Location(std::stod(tokens[0]), std::stod(tokens[1]));

            std::pair<std::string, double> closestAirport = {airportLocations[0].first, cOrigin.calculateDistance(airportLocations[0].second)};

            for (const auto& airport : airportLocations) {
                if (airport.second.calculateDistance(cOrigin) <= closestAirport.second) {
                    closestAirport = {airport.first, cOrigin.calculateDistance(airport.second)};
                }
            }

            airportD.push_back(closestAirport.first);
            break;


    }


    for (const auto& ap : airportO) {
        for (const auto& ap2 : airportD) {
            std::vector<std::string> p = flightGraph->createPath(ap, ap2, filter, type);
            if (!p.empty()) {
                paths.push_back(p);
            }
        }
    }


    if (paths.empty()) {
        std::cout << "There are no flights from " << origin << " to " << destination << std::endl;
    }
    else {
        std::sort(paths.begin(), paths.end(),[](const std::vector<std::string> &a, const std::vector<std::string> &b) {
            return a.size() < b.size();
        });


        unsigned long minStops = paths[0].size();
        auto aux = remove_if(paths.begin(), paths.end(), [minStops](const std::vector<std::string> &a) {
            return a.size() > minStops;
        });

        paths.erase(aux, paths.end());

        std::cout << "The best options to travel from " << origin << " to " << destination << ": " << std::endl;

        for (const auto& p : paths) {
            flightGraph->printPath(p);
        }
    }
}

//Filters

/**
 * @brief Verifica se um código de uma companhia aérea existe.
 * @details Complexity: O(1)
 * @param code: código da companhia aérea
 * @return true se o código é válido, false se não for.
 */
bool Manager::validAirlineCode(const std::string &code) {
    return airlines.find(code) != airlines.end() ;
}

/**
 * @brief Obtém o código da companhia aérea através do nome.
 * @details Complexity: O(N)
 * @details N - número de companhias aéreas
 * @param name: nome da companhia aérea
 * @return Código da companhia aérea, "" se não existir.
 */
std::string Manager::getCodeFromName(const std::string &name) {
    for (const auto& a: airlines) {
        if (a.second->getName() == name) {
            return a.second->getCode();
        }
    }
    return "";
}

/**
 * @brief Obtém o código da companhia aérea através do callsign.
 * @details Complexity: O(N)
 * @details N - número de companhias aéreas
 * @param callsign: callsign da companhia aérea
 * @return Código da companhia aérea, "" se não existir.
 */
std::string Manager::getCodeFromCallsign(const std::string &callsign) {
    for (const auto& a: airlines) {
        if (a.second->getCallsign() == callsign) {
            return a.second->getCode();
        }
    }
    return "";
}

/**
 * @brief Vetor de companhias aéreas de um país, para usar como filtro.
 * @details Complexity: O(N)
 * @details N - número de companhias aéreas
 * @param country: país a filtrar
 * @return Vetor de códigos de companhias aéreas do país especificado.
 */
std::vector<std::string> Manager::filterCountry(const std::string &country) {
    std::vector<std::string> res;

    for (const auto& a : airlines) {
        if (a.second->getCountry() == country) {
            res.push_back(a.second->getCode());
        }
    }
    return res;
}

//Airport Menu

/**
 * @brief Retoma o número de voos de um aeroporto específico, definido pelo utilizador.
 * @details Complexity: O(1)
 * @param code: código IATA do aeroporto
 * @return Número de voos do aeroporto.
 */
unsigned long Manager::flightsFromAirport(const std::string& code) {
    return flightGraph->nodeAtKey(code).adj.size();
}

/**
 * @brief Obtém o número de companhias aéreas que operam num aeroporto específico, definido pelo utilizador.
 * @details O número de companhias aéreas com opção de imprimir o código IATA de cada uma.
 * @details Complexity O(O(E * log(V)))
 * @details E - número de edges --> flights
 * @details V - número de vertices --> aeroports
 * @param code: código IATA do aeroporto
 */
void Manager::airlinesFromAirport(const std::string& code) {
    std::set<std::string> airList;
    for (const auto& edge : flightGraph->nodeAtKey(code).adj) {
        airList.insert(edge.airline);
    }
    std::cout << "There is a total of " << airList.size() << " airlines operating in " << code << std::endl;
    std::cout << "Want to see the full list of airlines operating in " << code << "?" << std::endl;
    std::cout << "If so, input 'y' to see the full list." << std::endl;

    char op;
    std::cin >> op;
    std::cout << std::endl;

    if (std::cin.fail() || (op != 'y')) {
        return;
    }
    else {
        for (const auto& airline : airList) {
            std::cout << airline << std::endl;
        }
        return;
    }
}

/**
 * @brief Obtém o número de destino diretos / sem escalas a partir de um aeroporto.
 * @details Complexity: O(E)
 * @details E- número de edges --> flights
 * @details Tem como opção referenciar os destinos por aeroporto, cidade ou país.
 * @details Além disso, dá como opção adicional imprimir os destinos um a um.
 * @param startAirportCode : código IATA do aeroporto
 */
void Manager::directDestinations(const std::string& startAirportCode) {

    std::unordered_set<std::string> directAirports;
    std::unordered_set<std::string> directCities;
    std::unordered_set<std::string> directCountries;

    for (const auto& edge : flightGraph->nodeAtKey(startAirportCode).adj) {
        std::string destinationAirportCode = edge.destination;
        Airport* destinationAirport = airports.at(destinationAirportCode);

        directAirports.insert(destinationAirportCode);
        directCities.insert(destinationAirport->getCity());
        directCountries.insert(destinationAirport->getCountry());
    }

    std::cout << "Choose an option and write down the alinea:" << std::endl;
    std::cout << std::endl;
    std::cout << "a. Airport" << std::endl;
    std::cout << "b. City" << std::endl;
    std::cout << "c. Country" << std::endl;

    char op1, op2;
    std::cin >> op1;
    std::cout << std::endl;

    if (std::cin.fail() || (op1 != 'a' && op1 != 'b' && op1 != 'c' && op1 != 'A' && op1 != 'B' && op1 != 'C')) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if (op1 == 'a' || op1 == 'A') {
        std::cout << " There are " << directAirports.size() << " direct airports" << std::endl;
    }

    else if (op1 == 'b' || op1 == 'B') {
        std::cout << " There are " << directCities.size() << " direct cities" << std::endl;
    }

    else if (op1 == 'c' || op1 == 'C') {
        std::cout << " There are " << directCountries.size() << " direct countries" << std::endl;
    }

    std::cout << "Do you want to print the results?" << std::endl;
    std::cout << std::endl;
    std::cout << "Write y or n." << std::endl;
    std::cin >> op2;
    std::cout << std::endl;

    if (std::cin.fail() || (op2 != 'y' && op2 != 'Y' && op2 != 'n' && op2 != 'N')) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if ((op1 == 'a' || op1 == 'A') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& destinationAirportCode : directAirports) {
            std::cout << airports.at(destinationAirportCode)->getName() << " with code " << destinationAirportCode << " is a direct destination." << std::endl;
        }
        return;
    }

    else if ((op1 == 'b' || op1 == 'B') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& city : directCities) {
            std::cout << city << " is a direct destination." << std::endl;
        }
        return;
    }

    else if ((op1 == 'c' || op1 == 'C') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& country : directCountries) {
            std::cout << country << " is a direct destination." << std::endl;
        }
        return;
    }
    else if (op2 == 'n' || op2 == 'N') {
        return;
    }
}

/**
 * @brief Obtém o número de destino possíveis com número infinito de escalas a partir de um aeroporto.
 * @details Complexity: O(V+E)
 * @details E- número de edges --> flights
 * @details V- número de vertices --> aeroportos
 * @details Tem como opção referenciar os destinos por aeroporto, cidade ou país.
 * @details Além disso, dá como opção adicional imprimir os destinos um a um.
 * @param startAirportCode : código IATA do aeroporto
 */
void Manager::allDestinations(const std::string& startAirportCode) {

    std::unordered_set<std::string> visitedAirports;
    std::unordered_set<std::string> visitedCities;
    std::unordered_set<std::string> visitedCountries;

    std::stack<std::pair<std::string, int>> dfsStack;
    dfsStack.push({startAirportCode, 0});

    while (!dfsStack.empty()) {
        auto top = dfsStack.top();
        dfsStack.pop();

        std::string topAirportCode = top.first;
        int stops = top.second;

        visitedAirports.insert(topAirportCode);

        for (const auto& edge : flightGraph->nodeAtKey(topAirportCode).adj) {
            std::string destinationAirportCode = edge.destination;
            if (destinationAirportCode != startAirportCode && visitedAirports.find(destinationAirportCode) == visitedAirports.end()) {
                Airport* destinationAirport = airports.at(destinationAirportCode);

                visitedAirports.insert(destinationAirportCode);
                visitedCities.insert(destinationAirport->getCity());
                visitedCountries.insert(destinationAirport->getCountry());

                dfsStack.push({destinationAirportCode, stops + 1});
            }
        }
    }

    std::cout << "Choose an option and write down the alinea:" << std::endl;
    std::cout << std::endl;
    std::cout << "a. Airport" << std::endl;
    std::cout << "b. City" << std::endl;
    std::cout << "c. Country" << std::endl;

    char op1, op2;
    std::cin >> op1;
    std::cout << std::endl;

    if (std::cin.fail() || (op1 != 'a' && op1 != 'b' && op1 != 'c' && op1 != 'A' && op1 != 'B' && op1 != 'C')) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if (op1 == 'a' || op1 == 'A') {
        std::cout << " There are " << visitedAirports.size() << " reachable airports" << std::endl;
    }

    else if (op1 == 'b' || op1 == 'B') {
        std::cout << " There are " << visitedCities.size() << " reachable cities" << std::endl;
    }

    else if (op1 == 'c' || op1 == 'C') {
        std::cout << " There are " << visitedCountries.size() << " reachable countries" << std::endl;
    }

    std::cout << "Do you want to print the results?" << std::endl;
    std::cout << std::endl;
    std::cout << "Write y or n." << std::endl;
    std::cin >> op2;
    std::cout << std::endl;

    if (std::cin.fail() || (op2 != 'y' && op2 != 'Y' && op2 != 'n' && op2 != 'N')) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if ((op1 == 'a' || op1 == 'A') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& destinationAirportCode : visitedAirports) {
            std::cout << airports.at(destinationAirportCode)->getName() << " with code " << destinationAirportCode << " was visited." << std::endl;
        }
        return;
    }

    else if ((op1 == 'b' || op1 == 'B') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& city : visitedCities) {
            std::cout << city << " was visited." << std::endl;
        }
        return;
    }

    else if ((op1 == 'c' || op1 == 'C') && (op2 == 'y' || op2 == 'Y')) {
        for (const auto& country : visitedCountries) {
            std::cout << country << " was visited." << std::endl;
        }
        return;
    }
    else if (op2 == 'n' || op2 == 'N') {
        return;
    }
}

/**
 * @brief Apresenta o número de destinos alcançáveis dado um número máximo de escalas. O aeroporto de origem é definido pelo utilizador.
 * @details Complexity: O(V+E)
 * @details E- número de  edges --> flights
 * @details V- número de vertices --> aeroportos
 * @details Tem como opção referenciar os destinos por aeroporto, cidade ou país.
 * @details Além disso, dá como opção adicional imprimir os destinos um a um.
 * @param startAirport: código IATA ou nome do aeroporto de origem
 * @param maxStops: número máximo de escalas
 */
void Manager::destinationsWithinStops(const std::string& startAirportCode, int maxStops){
    std::unordered_set<std::string> visitedAirports;
    std::unordered_set<std::string> visitedCities;
    std::unordered_set<std::string> visitedCountries;

    std::stack<std::pair<std::string, int>> dfsStack;
    dfsStack.push({startAirportCode, 0});

    while (!dfsStack.empty()) {
        auto top = dfsStack.top();
        dfsStack.pop();

        std::string topAirportCode = top.first;
        int stops = top.second;

        if (stops > maxStops) {
            continue;
        }

        visitedAirports.insert(topAirportCode);

        for (const auto& edge : flightGraph->nodeAtKey(topAirportCode).adj) {
            std::string destinationAirportCode = edge.destination;
            if (destinationAirportCode != startAirportCode && visitedAirports.find(destinationAirportCode) == visitedAirports.end()) {
                Airport* destinationAirport = airports.at(destinationAirportCode);

                visitedAirports.insert(destinationAirportCode);
                visitedCities.insert(destinationAirport->getCity());
                visitedCountries.insert(destinationAirport->getCountry());

                dfsStack.push({destinationAirportCode, stops + 1});
            }
        }
    }

    std::cout << "Input the type of destination:" << std::endl;
    std::cout << std::endl;
    std::cout << "a. Airports" << std::endl;
    std::cout << "b. Cities" << std::endl;
    std::cout << "c. Countries" << std::endl;

    char op1, op2;
    std::cin >> op1;
    std::cout << std::endl;

    if (std::cin.fail() || (op1 !='a' &&  op1 !='b' &&  op1 !='c' &&  op1 !='A' &&  op1 !='B' && op1 !='C' )) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if( op1 =='a' || op1 =='A'){
        std::cout << "There are " << visitedAirports.size() << " reachable airports" << std::endl;
    }

    else if( op1 =='b' || op1 =='B'){
        std::cout << "There are " << visitedCities.size() << " reachable cities" << std::endl;
    }

    else if( op1 =='c' || op1 =='C'){
        std::cout << "There are " << visitedCountries.size() << " reachables countries" << std::endl;
    }

    std::cout << "Do you want to print the results?" << std::endl;
    std::cout << std::endl;
    std::cout << "Write y or n." << std::endl;
    std::cin >> op2;
    std::cout << std::endl;

    if (std::cin.fail() || (op2 !='y' && op2 !='Y' && op2 !='n' && op2 !='N')) {
        throw std::invalid_argument("Error 001: Your input was not an option. Please restart the program and try again.");
        return;
    }

    else if(( op1 =='a' || op1 =='A') && ( op2 =='y' || op2 =='Y') ){
        for(const auto& destinationAirportCode : visitedAirports){
            std::cout << airports.at(destinationAirportCode)->getName() << " with code " << destinationAirportCode << " was visited." << std::endl;
        }
        return;
    }

    else if(( op1 =='b' || op1 =='B') && ( op2 =='y' || op2 =='Y') ){
        for(const auto& city : visitedCities){
            std::cout << city <<  " was visited." << std::endl;
        }
        return;
    }

    else if(( op1 =='c' || op1 =='C') && ( op2 =='y' || op2 =='Y') ){
        for(const auto& country : visitedCountries){
            std::cout << country <<  " was visited." << std::endl;
        }
        return;
    }
    else if( op2 =='n' || op2 =='N'){ return;}
}

//  STATISTICS MENU

/**
 * @brief Imprime o número de voos que saem de uma determinada cidade, especificada pelo utilizador.
 * @details Complexity: O(V+E)
 * @details E- número de  edges --> flights
 * @details V- número de vertices --> aeroportos
 * @param nameCity: nome da cidade
 */
void Manager::flightsPerCity(const std:: string& nameCity) {
    std::string CityCode, AirportCode;
    int countFlights = 0;

    for (const auto &city: cities) {
        if (city.second.first == nameCity) {
            CityCode = city.first;
        }
    }

    if (CityCode.empty()) {
        std::cout << "City not found " << std::endl;
        return;
    }

    for (const auto &airport: airports) {
        if(nameCity ==  airport.second->getCity()){
           AirportCode= airport.first;
           countFlights += flightGraph->nodeAtKey(AirportCode).adj.size();
        }
    }
    std::cout << "There are " << countFlights << " flights operated from " << nameCity << std::endl;
}

/**
 * @brief Imprime o número de voos que são operados por uma determinada companhia aérea, especificada pelo utilizador.
 * @details Complexity: O(V+E)
 * @details E- número de  edges --> flights
 * @details V- número de vertices --> aeroportos
 * @param nameAirline: nome da companhia aérea
 */
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

/**
 * @brief Imprime os K aeroportos com mais voos. O número de aeroportos a apresentar é especificado pelo utilizador.
 * @details Complexity: O(V*log(V))
 * @details V- número de vertices --> aeroportos
 * @param k: número de aeroportos a mostrar
 */
void Manager::topKAirports(int k) {
    std::vector<std::pair<Airport*, int>> allAirports;

    for (const auto& airport : airports) {
        int numFlights = 0;

        for (const auto& node : flightGraph->nodes) {
            for (const auto& edge : node.second.adj) {
                if (edge.destination == airport.first || node.first == airport.first) {
                    numFlights++;
                }
            }
        }

        allAirports.push_back({airport.second, numFlights});
    }

    std::sort(allAirports.begin(), allAirports.end(), [](const auto& p1, const auto& p2) {
        return p1.second > p2.second;
    });

    for (int i = 0; i < k && i < allAirports.size(); i++) {
        std::cout << allAirports[i].first->getCode() << " - " << allAirports[i].first->getName()
                  << " with " << allAirports[i].second << " total flights;" << std::endl;
    }
}
/**
 * @brief Encontra o maior caminho com o maior número de escalas entre aeroportos no grafo.
 * @details Complexity: O(V+E)
 * @details E- número de  edges --> flights
 * @details V- número de vertices --> aeroportos
 * @details utiliza DFS na sua busca
 */
void Manager::maximumTripWithStops() {
    std::pair<std::string, std::string> maxStopsPair;

    for (const auto &airport: airports) {
        const std::string &currentAirportCode = airport.first;
        auto &currentNode = flightGraph->nodeAtKey(currentAirportCode);

        if (!currentNode.visited) {
            std::vector<std::string> currentPath;
            flightGraph->dfs(currentAirportCode, currentPath, maxStopsPair);
        }
    }

    std::cout << "Maximum trip with the greatest number of stops: "
              << maxStopsPair.first << " -> " << maxStopsPair.second
              << " (Total stops: " << flightGraph->nodeAtKey(maxStopsPair.second).distance << ")" << std::endl;
}





// Global Statístics

/**
 * @brief Retoma o número de aeroportos no grafo.
 * @details Complexity: O(1)
 * @return Número total de aeroportos no grafo.
 */
unsigned long Manager::globalAirports() {
    return airports.size();
}

/**
 * @brief Imprime todos os aeroportos do grafo, no modo especificado pelo utilizador.
 * @details Complexity: O(N)
 * @details N - número de aeroportos no grafo
 * @param type: modo de apresentação da lista
 */
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

/**
 * @brief Retoma o número de companhias aéreas no grafo.
 * @details Complexity: O(1)
 * @return Número total de companhias aéreas no grafo.
 */
unsigned long Manager::globalAirlines() {
    return airlines.size();
}

/**
 * @brief Imprime todos as companhias aéreas do grafo.
 * @details Complexity: O(N)
 * @details N - número de aeroportos no grafo
 */
void Manager::printGlobalAirlines() {
    for (const auto& airline : airlines) {
        std::cout << airline.second->getCode() << " - " << airline.second->getName() << " - " << airline.second->getCallsign() << " - " << airline.second->getCountry() << std::endl;
    }
}


/**
 * @brief Imprime o número de articulation points no grafo, utilizando o algoritmo DFS específico para tal.
 * @details Complexity: O(V+E)
 * @details E- número de  edges --> flights
 * @details V- número de vertices --> aeroports
 * @param type: tipo de apresentação, definido pelo utilizador: se imprime também os aeroportos que são pontos de articulação.
 */
void Manager::printArticulation(char type) {
    std::vector<Airport*> points;
    std::stack<Graph::Node> st;
    int index = 1;

    for (auto& node : flightGraph->nodes) {
        node.second.low = 0;
        node.second.num = 0;
        node.second.inStack = false;
        node.second.visited = false;
    }

    for (auto n : flightGraph->nodes) {
        if (!n.second.visited) {
            flightGraph->articulationDFS(n.second, points, st, index);
        }
    }

    std::cout << "In the graph, there are " << points.size() << " articulation points." << std::endl;
    if (type == 'y') {
        for (auto point: points) {
            std::cout << point->getCode() << " - " << point->getName() << std::endl;
        }
    }
}

/**
 * @brief Obtém o diâmetro do grafo.
 * @details Complexity: O(N^2 * (N + E))
 * @details N - número de nodes
 * @details E - número de edges
 * @return Diâmetro do grafo.
 */
int Manager::graphDiameter() {

    int diameter = 0;

    for (const auto& ap : airports) {
        flightGraph->bfs(ap.first);
        for (auto ap2 : airports) {
            if (flightGraph->nodeAtKey(ap2.first).distance > diameter) {
                diameter = flightGraph->nodeAtKey(ap2.first).distance;
            }
        }
    }

    return diameter;
}








