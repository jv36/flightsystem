#include <iostream>
#include <limits>
#include "Graph.h"

Graph::Graph(int g_size, bool dir) {
    this->g_size = g_size;
    this->dir = dir;
}

void Graph::addNode(const std::string& airportCode, Airport* airport) {
    Node newNode;
    newNode.airport = airport;
    newNode.visited = false;
    newNode.distance = 0;
    newNode.parent = "";
    nodes.insert({airportCode, newNode});
}

void Graph::addEdge(const std::string &originAirport, const std::string &destAirport, const std::string &airline) {
    auto it = nodes.find(originAirport);
    auto it2 = nodes.find(destAirport);

    if (it == nodes.end() || it2 == nodes.end()) return;

    it->second.adj.push_back({destAirport, airline});
    if (!this->dir) it2->second.adj.push_back({originAirport, airline});

}
//usem isto quando quiserem procurar o máximo possível numa direção
void Graph::dfs(const std::string &airportCode) {
    this->removeDistance();
    this->removeVisited();

    std::stack<std::string> stack;
    stack.push(airportCode);
    nodes[airportCode].visited = true;
    nodes[airportCode].distance = 0;

    while (!stack.empty()) {
        std::string top = stack.top();
        stack.pop();

        for (const Edge& e : nodes.at(top).adj) {
            if (!nodes[e.airline].visited) {
                stack.push(e.airline);
                nodes[e.airline].visited = true;
                nodes[e.airline].parent = top;
                nodes[e.airline].distance = nodes[top].distance + 1;
            }
        }
    }
}

//usem isto quando quiserem procurar o caminho mais curto entre 2 nodes aka aeroportos etc
void Graph::bfs(const std::string &airportCode) {
    this->removeDistance();
    this->removeVisited();

    std::queue<std::string> q;
    q.push(airportCode);
    nodes[airportCode].visited = true;
    nodes[airportCode].distance = 0;

    // while unvisited
    while (!q.empty()) {
        std::string top = q.front();
        q.pop();

        for (const Edge& e : nodes.at(top).adj) {
            if (!nodes[e.airline].visited) {
                q.push(e.airline);
                nodes[e.airline].visited = true;
                nodes[e.airline].parent = top;
                nodes[e.airline].distance = nodes[top].distance + 1;
            }
        }
    }

}

Graph::Node &Graph::nodeAtKey(const std::string &key) {
    Node& node = this->nodes[key];
    return node;
}

void Graph::removeVisited() {
    for (auto& node: nodes) {
        node.second.visited = false;
    }
}

void Graph::removeDistance() {
    for (auto& node: nodes) {
        node.second.distance = -1;
    }
}
void Graph::clearGraph() {
    this->nodes.clear();
}

int Graph::distance(const std::string& in, const std::string& out) {
    if (in == out) {
        return 0;
    }
    bfs(in);
    int dist = nodes[out].distance;
    return dist;
}

/*std::vector<std::string> Graph::createPath(std::string from, std::string to, std::vector<std::string> &airlineList) {
    // tem de se filtrar depois faço

    return std::vector<std::string>();
}
*/
/*
int Graph::addAirport(Airport a){
    if(this->nodes.find(a.getCode())==this->nodes.end()) this->nodes.insert(std::pair<std::string,Node>(a.getCode(),{}));
    return this->nodes.size();
}

bool Graph::addFlight(std::string destination, std::string airline, std::string airline) {
    return this->addFlight(destination,airline,airline);
}

void Graph::printGraph() {
    for (const auto& node : nodes) {
        std::cout << "Airport: " << node.airport->getName() << "\nEdges:\n";
        for (const auto& edge : node.adj) {
            std::cout << "  To: " << edge.destAirport->getName() << ", Airline: " << edge.airline->getName() << ", Distance: " << edge.distance << "\n";
        }
        std::cout << "\n";
    }
}*/
Airport* Graph::findClosestAirport(Graph graph,Location source, Location dest) {
    Airport* closestAirport;
    double minDistance = 0.0;

    for (const auto& nodePair: graph.nodes) {
        const Node& node = nodePair.second;
        double distance = abs(Flight::getDistance(source, dest));   //assim da sempre postiivo

        if (distance < minDistance) {
            minDistance = distance;
            closestAirport = node.airport;
        }
    }

    return closestAirport;
}

void Graph::articulationDFS(Graph::Node &node, std::vector<Airport*> &points, std::stack<Node> &st, int index) {
    node.visited = true;
    node.num = index;
    node.low = index;
    st.push(node);
    node.inStack = true;
    index++;
    bool flag = false;
    int child = 0;

    for (Edge& edge : node.adj) {
        auto& destNode = nodes[edge.destination];
        if(!destNode.visited) {
            child++;
            articulationDFS(destNode, points, st, index);
            node.low = std::min(node.low, destNode.low);
            if (destNode.low >= node.num) flag = true; // it is an art. point
        }
        else if (destNode.inStack) {
            node.low = std::min(node.low, destNode.num);
        }
    }

    // articulation point if and only if it has more than one child on the dfs tree

    if ((node.num == node.low && child > 1) || (node.num != node.low && flag)) {
        while (!st.empty()) {
            Node top = st.top();
            st.pop();
            node.inStack = false;

            if (top.airport->getName() == node.airport->getName()) {
                points.push_back(top.airport);
                break;
            }
        }
    }
}


//hum
/*
Graph Graph::createAirTravelGraph(const std::unordered_map<std::string, Airport*>& airports, const std::vector<Flight>& flights) {
    Graph airTravelGraph;

    for (auto airport : airports) {
        airTravelGraph.addNode(airport.first, airport.second);
    }

    for (const auto& flight : flights) {
        airTravelGraph.addEdge(flight.getSource(), flight.getTarget(), "");
    }

    return airTravelGraph;
}
 */


