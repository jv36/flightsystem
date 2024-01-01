#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <climits>
#include "Graph.h"

/**
 * @brief Construtor da classe Graph que recebe o tamanho do grafo e se ele é dirigido ou não.
 * @details Complexity: O(1)
 * @param g_size: tamanho do grafo
 * @param dir: dirigido ou não dirigido
 */
Graph::Graph(int g_size, bool dir) {
    this->g_size = g_size;
    this->dir = dir;
}

/**
 * @brief Adiciona um node ao grafo.
 * @details Complexity: O(1)
 * @param airportCode: código IATA do aeroporto
 * @param airport: apontador para objeto da classe Airport, representa um aeroporto
 */
void Graph::addNode(const std::string& airportCode, Airport* airport) {
    Node newNode;
    newNode.airport = airport;
    newNode.visited = false;
    newNode.distance = 0;
    newNode.parent = "";
    nodes.insert({airportCode, newNode});
}

/**
 * @brief Adiciona um edge ao grafo.
 * @details Complexity: O(1)
 * @param originAirport: código IATA do aeroporto de origem
 * @param destAirport: código IATA do aeroporto de destino
 * @param airline: companhia aérea do voo
 */
void Graph::addEdge(const std::string &originAirport, const std::string &destAirport, const std::string &airline) {
    auto it = nodes.find(originAirport);
    auto it2 = nodes.find(destAirport);

    if (it == nodes.end() || it2 == nodes.end()) return;

    it->second.adj.push_back({destAirport, airline});
    if (!this->dir) it2->second.adj.push_back({originAirport, airline});
}

/**
 * @brief Faz uma pesquisa DFS no grafo.
 * @details Complexity: O(V + E)
 * @details V - número de aeroportos
 * @details E - número de edges
 * @param airportCode: código IATA do aeroporto
 */
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

/**
 * @brief Faz uma pesquisa BFS no grafo.
 * @details Complexity: O(V + E)
 * @details V - número de aeroportos
 * @details E - número de edges
 * @param airportCode: código IATA do aeroporto
 */
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
            if (!nodes[e.destination].visited) {
                q.push(e.destination);
                nodes[e.destination].visited = true;
                nodes[e.destination].parent = top;
                nodes[e.destination].distance = nodes[top].distance + 1;
            }
        }
    }

}

/**
 * @brief Faz uma pesquisa BFS no grafo, utilizando um filtro de companhias aéreas a restringir.
 * @details Complexity: O(V + E + F)
 * @details V - número de aeroportos
 * @details E - número de edges
 * @details F - número de companhias aéreas no filtro
 * @param airportCode: código IATA do aeroporto
 * @param filter: vetor de companhias aéreas a quem queremos restringir a pesquisa
 */
void Graph::bfsFilteredRestrict(const std::string &airportCode, std::vector<std::string>& filter) {
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
            if (find(filter.begin(), filter.end(), e.airline) != filter.end()) {
                if (!nodes[e.destination].visited) {
                    q.push(e.destination);
                    nodes[e.destination].visited = true;
                    nodes[e.destination].parent = top;
                    nodes[e.destination].distance = nodes[top].distance + 1;
                }
            }
        }
    }

}

/**
 * @brief Faz uma pesquisa BFS no grafo, utilizando um filtro de companhias aéreas a excluir da pesquisa.
 * @details Complexity: O(V + E + F)
 * @details V - número de aeroportos
 * @details E - número de edges
 * @details F - número de companhias aéreas no filtro
 * @param airportCode: código IATA do aeroporto
 * @param filter: vetor de companhias aéreas que queremos excluir da pesquisa
 */
void Graph::bfsFilteredExclude(const std::string &airportCode, std::vector<std::string> &filter) {
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
            if (find(filter.begin(), filter.end(), e.airline) == filter.end()) {
                if (!nodes[e.destination].visited) {
                    q.push(e.destination);
                    nodes[e.destination].visited = true;
                    nodes[e.destination].parent = top;
                    nodes[e.destination].distance = nodes[top].distance + 1;
                }
            }
        }
    }

}

/**
 * @brief Retoma o node pertencente à chave introduzida como parâmetro.
 * @details Complexity: O(1) mas poderá ser O(n) no pior caso
 * @param key: chave do node que queremos
 * @return O node pertencente à chave key.
 */
Graph::Node &Graph::nodeAtKey(const std::string &key) {
    Node& node = this->nodes[key];
    return node;
}

/**
 * @brief Coloca todos os nodes como não visitados.
 * @details Complexity: O(V)
 * @details V - número de vértices no grafo
 */
void Graph::removeVisited() {
    for (auto& node: nodes) {
        node.second.visited = false;
    }
}

/**
 * @brief Coloca todos os nodes com a distância a -1.
 * @details Complexity: O(V)
 * @details V - número de vértices no grafo
 */
void Graph::removeDistance() {
    for (auto& node: nodes) {
        node.second.distance = -1;
    }
}

/**
 * @brief Limpa os nodes do grafo.
 * @details Complexity: O(1)
 */
void Graph::clearGraph() {
    this->nodes.clear();
}

/**
 * @brief Faz uma pesquisa DFS para obter os pontos de articulação do grafo.
 * @brief Adaptação do Tarjan's Algorithm, baseado num dos recursos teóricos da cadeira.
 * @details Complexity: O(V + E)
 * @details V - número de vértices no grafo
 * @details E - número de edges no grafo
 * @param node: node
 * @param points: aeroportos que são pontos de articulação
 * @param st: stack de nodes para usar na pesquisa
 * @param index: índice
 */
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


/**
 * @brief Cria um caminho entre aeroportos, utilizando as funções de pesquisa BFS.
 * @details Complexity: O(V + E)
 * @details V - número de vértices no grafo
 * @details E - número de edges no grafo
 * @param from: código IATA do aeroporto de origem
 * @param to: código IATA do aeroporto de destino
 * @param filter: vetor com companhias aéreas, se for necessário restringir ou excluir da pesquisa. Vazio caso não se aplique.
 * @param type: tipo de BFS a efetuar, determinado pelo utilizador
 * @return Vetor com os códigos dos aeroportos do caminho.
 */
std::vector<std::string> Graph::createPath(std::string from, std::string to, std::vector<std::string>& filter, int type) {
    std::vector<std::string> path;
    if (filter.empty() || type == 0) {
        bfs(from);
    }
    else if (type == 1) {
        bfsFilteredRestrict(from, filter);
    }
    else if (type == 2) {
        bfsFilteredExclude(from, filter);
    }

    path.push_back(to);
    while (to != from) {
        to = nodes[to].parent;
        if (to.empty()) {
            return {};
        }
        path.insert(path.begin(), to);
    }
    return path;
}

/**
 * @brief Imprime um caminho entre aeroportos.
 * @details Complexity: O(N)
 * @details N - número de aeroportos do caminho
 * @param path: vetor com os códigos dos aeroportos do caminho
 */
void Graph::printPath(const std::vector<std::string>& path) {
    if (!path.empty()) {
        auto last = path.end() - 1;

        for (auto i = path.begin(); i != last; ++i) {
            std::cout << *i << " -> ";
        }

        std::cout << *last << std::endl;
    }
}
