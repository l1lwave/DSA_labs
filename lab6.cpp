#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> incidenceMatrix;
    unordered_map<char, int> vertexMap;
    list<pair<char, char>> edgeList;
    vector<list<char>> adjacencyList;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
        adjacencyList.resize(numVertices);
    }

    void addEdge(char from, char to) {
        int u = vertexMap[from];
        int v = vertexMap[to];
        adjacencyMatrix[u][v] = 1;
        // For a directed graph, comment out the line below
        adjacencyMatrix[v][u] = 1; // for an undirected graph

        edgeList.push_back({ from, to });
        adjacencyList[u].push_back(to);
        adjacencyList[v].push_back(from); // for an undirected graph
    }

    vector<vector<int>> getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }

    vector<vector<int>> getIncidenceMatrix() const {
        return incidenceMatrix;
    }

    list<pair<char, char>> getEdgeList() const {
        return edgeList;
    }

    vector<list<char>> getAdjacencyList() const {
        return adjacencyList;
    }

    void createVertexMap(const vector<char>& vertices) {
        for (int i = 0; i < numVertices; ++i) {
            vertexMap[vertices[i]] = i;
        }
    }

    void createIncidenceMatrix(const vector<pair<char, char>>& edges, bool isDirected) {
        int numEdges = edges.size();
        incidenceMatrix.resize(numVertices, vector<int>(numEdges, 0));

        for (int i = 0; i < numEdges; ++i) {
            char from = edges[i].first;
            char to = edges[i].second;
            int u = vertexMap[from];
            int v = vertexMap[to];

            incidenceMatrix[u][i] = 1;

            if (isDirected) {
                incidenceMatrix[v][i] = -1;
            }
            else {
                incidenceMatrix[v][i] = 1; 
            }
        }
    }

    void displayMatrix(const vector<vector<int>>& matrix, const string& matrixType) const {
        cout << matrixType << ":" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void displayEdgeList() const {
        cout << "Edge List:" << endl;
        for (auto edge : edgeList) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    void displayAdjacencyList() const {
        cout << "Adjacency List:" << endl;
        for (const auto& entry : vertexMap) {
            char vertex = entry.first;
            int index = entry.second;

            cout << vertex << ": ";
            for (char neighbor : adjacencyList[index]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

void first() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    vector<char> vertices(numVertices);

    cout << "Enter the vertices of the graph (e.g., a b c):" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cin >> vertices[i];
    }

    bool isDirected;
    cout << "Is the graph directed? (1 for yes, 0 for no): ";
    cin >> isDirected;

    Graph graph(numVertices);
    graph.createVertexMap(vertices);


    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    vector<pair<char, char>> edges(numEdges);

    cout << "Enter edges (e.g., a b, b b, b d): " << endl;
    for (int i = 0; i < numEdges; ++i) {
        cin >> edges[i].first >> edges[i].second;
        graph.addEdge(edges[i].first, edges[i].second);
    }

    graph.createIncidenceMatrix(edges, isDirected);

    graph.displayMatrix(graph.getAdjacencyMatrix(), "Adjacency Matrix");
    graph.displayMatrix(graph.getIncidenceMatrix(), "Incidence Matrix");
    graph.displayEdgeList();
    graph.displayAdjacencyList();
}

vector<vector<int>> buildIncidenceMatrix(const vector<vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    int numEdges = 0;

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++numEdges;
            }
        }
    }

    vector<vector<int>> incidenceMatrix(numVertices, vector<int>(numEdges, 0));

    int edgeIndex = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                ++edgeIndex;
            }
        }
    }

    return incidenceMatrix;
}

// Функція для побудови списку ребер за матрицею інцидентності
vector<pair<int, int>> buildEdgeList(const vector<vector<int>>& incidenceMatrix) {
    int numVertices = incidenceMatrix.size();
    int numEdges = incidenceMatrix[0].size();

    vector<pair<int, int>> edgeList;

    for (int j = 0; j < numEdges; ++j) {
        int vertex1 = -1, vertex2 = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (incidenceMatrix[i][j] == 1) {
                if (vertex1 == -1) {
                    vertex1 = i;
                }
                else {
                    vertex2 = i;
                    break;
                }
            }
        }
        edgeList.push_back({ vertex1, vertex2 });
    }

    return edgeList;
}

// Функція для побудови списку суміжності за матрицею суміжності
vector<vector<int>> buildAdjacencyList(const vector<vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();

    vector<vector<int>> adjacencyList(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    return adjacencyList;
}

// Функція для побудови матриці суміжності за матрицею інцидентності
vector<vector<int>> buildAdjacencyMatrix(const vector<vector<int>>& incidenceMatrix) {
    int numVertices = incidenceMatrix.size();
    int numEdges = incidenceMatrix[0].size();

    vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

    for (int j = 0; j < numEdges; ++j) {
        int vertex1 = -1, vertex2 = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (incidenceMatrix[i][j] == 1) {
                if (vertex1 == -1) {
                    vertex1 = i;
                }
                else {
                    vertex2 = i;
                    break;
                }
            }
        }
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1;
    }

    return adjacencyMatrix;
}

// Функція для введення матриці з клавіатури
vector<vector<int>> inputMatrix(int numRows, int numCols) {
    vector<vector<int>> matrix(numRows, vector<int>(numCols, 0));

    cout << "Enter the size matrix " << numRows << "x" << numCols << ":\n";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            cin >> matrix[i][j];
        }
    }

    return matrix;
}

void seccond() {
    int numRows;
    int numCols;

    cout << "Enter the matrix size:";
    cin >> numRows; cin >> numCols;

    // Задана матриця суміжності
    vector<vector<int>> adjacencyMatrix = inputMatrix(numRows, numCols);

    // Завдання 1: Побудова матриці інцидентності за матрицею суміжності
    vector<vector<int>> incidenceMatrix = buildIncidenceMatrix(adjacencyMatrix);

    // Завдання 2: Побудова списку ребер за матрицею інцидентності
    vector<pair<int, int>> edgeList = buildEdgeList(incidenceMatrix);

    // Завдання 3: Побудова списку суміжності за матрицею суміжності
    vector<vector<int>> adjacencyList = buildAdjacencyList(adjacencyMatrix);

    // Завдання 4: Побудова матриці суміжності за матрицею інцидентності
    vector<vector<int>> newAdjacencyMatrix = buildAdjacencyMatrix(incidenceMatrix);

    // Виведення результатів
    cout << "Incidence matrix:" << endl;
    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "\nList of edges:" << endl;
    for (const auto& edge : edgeList) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }

    cout << "\n\nAdjacency list:" << endl;
    for (int i = 0; i < adjacencyList.size(); ++i) {
        cout << i << ": ";
        for (int neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    cout << "\nNew adjacency matrix:" << endl;
    for (const auto& row : newAdjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}


int main() {
    int a;
    while (true)
    {
        cout << "Enter the exercise: ";
        if (!(cin >> a)) {
            cout << "Error: Invalid input. Please enter only integers.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else {
            if (a == 1) {
                first();
            }
            else if (a == 2) {
                seccond();
            }
            else {
                cout << "Error: Invalid input.\n";
            }
        }
    }

    return 0;
}
