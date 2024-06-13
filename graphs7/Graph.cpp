#include "Graph.h"  // ���������


//----------------------------------------------------------------------------------------//
//------------------------------���������� �������----------------------------------------//
//----------------------------------------------------------------------------------------//


// �����������
Graph::Graph(const string& file_path, const string& file_type)
{

    if (file_type == "-e") {            // ������ ����
        read_edge_list(file_path);
    }
    else if (file_type == "-l") {       // ������ ���������
        read_adjacency_list(file_path);
    }
    else if (file_type == "-m") {       // ������� ���������
        read_adjacency_matrix(file_path);
    }
    else {
        cout << "������" << endl;
    }
    isDirected = is_directed();         // ��������� ������������ �� ����
}

//----------------------------------------------------------------------------------------//

// ����������� �� ������� ���������
Graph::Graph(const vector<vector<int>>& adjMatr)
{
    adjacencyMatrix.resize(adjMatr.size(), vector<int>(adjMatr.size(), 0)); // �������� ������ ��� ������� ���������
    for (int i = 0; i < adjMatr.size(); ++i)                                // � ����� ��������� �������
    {
        for (int j = 0; j < adjMatr.size(); ++j)
        {
            adjacencyMatrix[i][j] = adjMatr[i][j];
        }
    }
    countVertex = adjacencyMatrix.size();   // ��������� ���������� ������
    isDirected = is_directed();             // ��������� ����������������� �����                                
}

//----------------------------------------------------------------------------------------//

// ���������� �� ����� ����� � �����
bool Graph::is_edge(const Vertex& vi, const Vertex& vj) const
{
    vector<Edge> edges = list_of_edges();       // �������� ������ ����
    // ������������ ������ �����
    for (const Edge& edge : edges) {           // ���������� ������ ����
        // ���� ����� ����� � ������ - ���������� true
        if (edge.start.index == vi.index && edge.end.index == vj.index) {
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------//

// ��� �����
int Graph::weight(const Vertex& vi, const Vertex& vj) const
{
    vector<Edge> edges = list_of_edges();

    // ���� ��� �����
    if (!is_edge(vi, vj)) return 0;

    // ������������ ������ ����
    for (const Edge& edge : edges) {
        // ����� ���������� ����� - ���������� ���
        if (edge.start.index == vi.index && edge.end.index == vj.index) {
            return edge.weight;
        }
    }
}

//----------------------------------------------------------------------------------------//

// ������� ��������� �����
vector<vector<int>> Graph::adjacency_matrix() const
{
    // ���������� �������
    return adjacencyMatrix;
}


//----------------------------------------------------------------------------------------//

// ������ ������, ������� ������� v
vector<Vertex> Graph::adjacency_list(const Vertex& v) const
{
    // ������ ������
    vector<Vertex> adjList;

    // �������� ������ ����
    vector<Edge> edges = list_of_edges();

    // ������������ ������ ����
    for (const Edge& edge : edges) {
        // ���� ������ �������� ����� ��������� � ��������
        if (edge.start.index == v.index)
            adjList.push_back(edge.end);       // ���������� �������
    }

    // ���������� ������ ���������
    return adjList;
}

//----------------------------------------------------------------------------------------//

// ������ ��������� �����
vector<vector<Vertex>> Graph::adjacency_list() const
{
    // ������ ���������
    vector<vector<Vertex>> adjacencyList;
    // �� ������� ������� ���������� ������ ������, ������� ������� �������
    for (int i = 0; i < countVertex; ++i)
    {
        adjacencyList.push_back(adjacency_list({ i }));
    }
    return adjacencyList;
}

//----------------------------------------------------------------------------------------//

// ������ ���� �����/��� �����
vector<Edge> Graph::list_of_edges() const
{
    vector<Edge> edges;     // ������ ����
    // ��������� ������ ����
    for (int i = 0; i < countVertex; ++i)
    {
        for (int j = 0; j < countVertex; ++j)
        {
            if (adjacencyMatrix[i][j])
            {
                edges.push_back({ {i}, {j}, adjacencyMatrix[i][j] });
            }
        }
    }
    return edges;   // ���������� ����, � ������� ������ ����
}

//----------------------------------------------------------------------------------------//

// ������ ���� ���� �����, ����������� ������� v / ��������� �� ������� v
vector<Edge> Graph::list_of_edges(const Vertex& v) const
{
    // ������ ����
    vector<Edge> edges = list_of_edges();

    // ��������������� ������ ��� ������ ����
    vector<Edge> incidentEdges;

    //  ������������ ������ ����
    for (const Edge& edge : edges) {
        // ���� ������ ��� ����� �������� ����� ������� � ��������
        if (edge.start.index == v.index || edge.end.index == v.index)
            incidentEdges.push_back(edge);  // ���������� ����� � ������
    }

    // ���������� ������ ����������� ����
    return incidentEdges;
}

//----------------------------------------------------------------------------------------//

// ����/������
bool Graph::is_directed()
{
    // ������ ����
    vector<Edge> edges = list_of_edges();

    // ������� � ����������� � ��������
    vector<int> startVertices;
    vector<int> targetVertices;

    // ������������ ������ �����
    for (const auto& edge : edges)
    {
        startVertices.push_back(edge.start.index);
        targetVertices.push_back(edge.end.index);
    }
    // ������������ ������ ���������� ������
    for (const auto& start : startVertices) {
        if (count(startVertices.begin(), startVertices.end(), start) != count(targetVertices.begin(), targetVertices.end(), start)) {
            return true;    // ���� indeg != outdeg => ������
        }
    }
    return false;
}


//----------------------------------------------------------------------------------------//

// ������ �� ������ �����
void Graph::read_edge_list(const string& filePath)
{
    vector<Edge> edges; // ������ ����
    // ��������� ���� ��� ������
    ifstream file(filePath);
    string line;        // ������� �����
    int start, end;     // ������ ����� �����
    int maxVertexIndex = -1;    // ����� ��������������� �������� ���������� ������� ���������� ������ � �����
    int weight;         // ��� �����
    while (getline(file, line)) {           // ���� ���� �� ����
        stringstream ss(line);              // ������� �����
        ss >> start >> end;                 // ��������� ������ �� ������ � �����
        if (ss.eof()) weight = 1;           // ���� ������ ��� �����
        else ss >> weight;                  // ����� - ������ ���
        maxVertexIndex = max(maxVertexIndex, max(start, end));  // ��������� ������������ ������� � ������
        edges.push_back(Edge({ start }, { end }, weight));      // ��������� ����� � ������
    }
    file.close();                                               // ��������� ����
    // ���������� ������
    countVertex = maxVertexIndex;
    // �������� ����������� ������ ��� ������� ���������
    adjacencyMatrix.resize(countVertex, vector<int>(countVertex, 0));
    // ��������� �������
    for (const Edge& edge : edges)
    {
        adjacencyMatrix[edge.start.index - 1][edge.end.index - 1] = edge.weight;
    }
}

//----------------------------------------------------------------------------------------//

// ������ �� ������� ���������
void Graph::read_adjacency_list(const string& filePath)
{
    // ��������� ���� ��� ������
    ifstream file(filePath);
    string line;        // ������� �����
    int counter = 0;    // �������
    int N = 0;          // ������ ������������ �������
    vector<set<Vertex>> vertex_to_adjacent_vertices;  // ������ ������� ������� ������
    while (getline(file, line)) {       // ���� ���� �� ����
        if (!line.empty()) {
            stringstream ss(line);              // ������� �����
            int vertexIndex;                    // ������� ������� �������
            set<Vertex> adjacent_vertices;   // ������ ���������
            while (ss >> vertexIndex) {         // ���� � ������ ���� �������
                N = max(N, vertexIndex);
                adjacent_vertices.insert({ vertexIndex - 1 });           // ���������� � ������ ������� �������
            }

            vertex_to_adjacent_vertices.push_back(adjacent_vertices); // � ������� ��������� ������ ���������
        }
        else
        {
            vertex_to_adjacent_vertices.push_back({});
        }
        ++counter;
    }
    file.close();                                               // ��������� ����
    // ���������� ������
    countVertex = max(counter, N);
    // �������� ����������� ������ ��� ������� ���������
    adjacencyMatrix.resize(countVertex, vector<int>(countVertex, 0));
    // ��������� �������
    for (int i = 0; i < counter; ++i)
    {
        for (const auto& current : vertex_to_adjacent_vertices[i])
        {
            adjacencyMatrix[i][current.index] = 1;
        }
    }
}

//----------------------------------------------------------------------------------------//

// ������ �� ������� ���������
void Graph::read_adjacency_matrix(const string& filePath)
{
    ifstream file(filePath);            // ��������� ���� ��� ������
    string line;                        // ������� �����
    while (getline(file, line)) {       // ���� �� ����� �����
        vector<int> row;                // ������� ������ � �������
        istringstream iss(line);        // ������� ����� � �����
        int num;                        // �����
        while (iss >> num) {            // ���� �� ����� �����    
            row.push_back(num);         // ���������� � ������ ������� ������
        }
        adjacencyMatrix.push_back(row); // ��������� � ������� ������
    }
    file.close();                       // ��������� ����
    // ���������� ������
    countVertex = adjacencyMatrix.size();
}

//----------------------------------------------------------------------------------------//

// ������� ������������� ����
bool hasNegativeEdges(const vector<Edge>& edges) {
    for (const auto& edge : edges)
    {
        if (edge.weight < 0) return true;
    }
    return false;                   // ������������� ����� �� �������
}

//----------------------------------------------------------------------------------------//