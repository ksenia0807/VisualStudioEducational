#include "Floyd-Warshall.h" // ���������


//----------------------------------------------------------------------------------------//
//------------------------------���������� �������----------------------------------------//
//----------------------------------------------------------------------------------------//

// �����������
Floyd_Warshall::Floyd_Warshall(Graph graph) : graph(graph)
{
    // ������������� ������� ���������� � ������������ ����������
    distance.resize(graph.countVertex, vector<int>(graph.countVertex, INF));
    // ���������� ������� ���������� �� ��������� �����
    for (int i = 0; i < graph.countVertex; ++i) {
        for (int j = 0; j < graph.countVertex; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) {
                distance[i][j] = graph.adjacencyMatrix[i][j];
            }
            if (i == j)
            {
                distance[i][j] = 0;
            }
        }
    }
}

//----------------------------------------------------------------------------------------//

// ���� ������� ���������� ����������
vector<vector<int>> Floyd_Warshall::find_distance_matrix()
{
    // �������� ������-�������� ��� ���������� ���������� ����������
    for (int k = 0; k < graph.countVertex; ++k) {
        for (int i = 0; i < graph.countVertex; ++i) {
            for (int j = 0; j < graph.countVertex; ++j) {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }
    return distance;
}

//----------------------------------------------------------------------------------------//

// ���� ������ �������� ��� �����
vector<int> Floyd_Warshall::find_degree_vector_for_graph()
{
    vector<int> degree(graph.countVertex, 0);
    for (int i = 0; i < graph.countVertex; ++i) {
        for (int j = 0; j < graph.countVertex; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) {
                ++degree[i];
            }
        }
    }
    return degree;
}

//----------------------------------------------------------------------------------------//

// ���� ������� ������������ ��� �������
pair<vector<int>, vector<int>> Floyd_Warshall::find_degree_vectors_for_orgraph()
{
    vector<int> in(graph.countVertex, 0);
    vector<int> out(graph.countVertex, 0);
    pair<vector<int>, vector<int>> vectors(in, out);

    // ���� ����������� ������(�� �������)
    for (int i = 0; i < graph.countVertex; ++i) {
        for (int j = 0; j < graph.countVertex; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) {
                ++vectors.second[i];
            }
        }
    }
    // ���� ����������� ������(�� ��������)
    for (int i = 0; i < graph.countVertex; ++i) {
        for (int j = 0; j < graph.countVertex; ++j) {
            if (graph.adjacencyMatrix[j][i] != 0) {
                ++vectors.first[i];
            }
        }
    }
    return vectors;
}

//----------------------------------------------------------------------------------------//

// ���� ������ ����������������
vector<int> Floyd_Warshall::eccentricity()
{
    vector<int> ecc;
    for (int i = 0; i < graph.countVertex; ++i) {
        int eccentricity = 0;
        for (int j = 0; j < graph.countVertex; ++j) {
            if (distance[i][j] != INF) {
                eccentricity = max(eccentricity, distance[i][j]);
            }
        }
        ecc.push_back(eccentricity);
    }
    return ecc;
}

//----------------------------------------------------------------------------------------//

// ���� ������� � ������
pair<int, int> Floyd_Warshall::find_diametr_and_radius()
{
    pair<int, int> diametr_radius(0, INF);                  // ������� � ������
    vector<int> ecc = eccentricity();
    diametr_radius.first = max(*max_element(ecc.begin(), ecc.end()), diametr_radius.first);
    diametr_radius.second = min(*min_element(ecc.begin(), ecc.end()), diametr_radius.second);
    return diametr_radius;
}

//----------------------------------------------------------------------------------------//

// ����� ��������� ����������� ������
set<Vertex> Floyd_Warshall::find_cent_vertex()
{
    int radius = find_diametr_and_radius().second;
    vector<int> ecc = eccentricity();
    set<Vertex> centrVertex;                    // ���������
    for (int i = 0; i < ecc.size(); ++i) {      // �������
        if (ecc[i] == radius) centrVertex.insert({ i + 1 });
    }
    return centrVertex;
}

//----------------------------------------------------------------------------------------//

// ����� ��������� ������������ ������
set<Vertex> Floyd_Warshall::find_perif_vertex()
{
    int diametr = find_diametr_and_radius().first;
    vector<int> ecc = eccentricity();
    set<Vertex> perifVertex;                      // ���������
    for (int i = 0; i < ecc.size(); ++i) {        // �������
        if (ecc[i] == diametr) perifVertex.insert({ i + 1 });
    }
    return perifVertex;
}
//----------------------------------------------------------------------------------------//