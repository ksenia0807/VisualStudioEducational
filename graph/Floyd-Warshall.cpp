#include "Floyd-Warshall.h" // Заголовок


//----------------------------------------------------------------------------------------//
//------------------------------РЕАЛИЗАЦИЯ МЕТОДОВ----------------------------------------//
//----------------------------------------------------------------------------------------//

// Конструктор
Floyd_Warshall::Floyd_Warshall(Graph graph) : graph(graph)
{
    // Инициализация матрицы расстояний с бесконечными значениями
    distance.resize(graph.countVertex, vector<int>(graph.countVertex, INF));
    // Заполнение матрицы расстояний из исходного графа
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

// Ищем матрицу кратчайших расстояний
vector<vector<int>> Floyd_Warshall::find_distance_matrix()
{
    // Алгоритм Флойда-Уоршелла для нахождения кратчайших расстояний
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

// Ищем вектор степеней для графа
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

// Ищем векторы полустепеней для орграфа
pair<vector<int>, vector<int>> Floyd_Warshall::find_degree_vectors_for_orgraph()
{
    vector<int> in(graph.countVertex, 0);
    vector<int> out(graph.countVertex, 0);
    pair<vector<int>, vector<int>> vectors(in, out);

    // Ищем полустепени выхода(по строкам)
    for (int i = 0; i < graph.countVertex; ++i) {
        for (int j = 0; j < graph.countVertex; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) {
                ++vectors.second[i];
            }
        }
    }
    // Ищем полустепени захода(по столбцам)
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

// Ищем вектор эксцентриситетов
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

// Ищем диаметр и радиус
pair<int, int> Floyd_Warshall::find_diametr_and_radius()
{
    pair<int, int> diametr_radius(0, INF);                  // Диаметр и радиус
    vector<int> ecc = eccentricity();
    diametr_radius.first = max(*max_element(ecc.begin(), ecc.end()), diametr_radius.first);
    diametr_radius.second = min(*min_element(ecc.begin(), ecc.end()), diametr_radius.second);
    return diametr_radius;
}

//----------------------------------------------------------------------------------------//

// Поиск множества центральных вершин
set<Vertex> Floyd_Warshall::find_cent_vertex()
{
    int radius = find_diametr_and_radius().second;
    vector<int> ecc = eccentricity();
    set<Vertex> centrVertex;                    // Множество
    for (int i = 0; i < ecc.size(); ++i) {      // Перебор
        if (ecc[i] == radius) centrVertex.insert({ i + 1 });
    }
    return centrVertex;
}

//----------------------------------------------------------------------------------------//

// Поиск множества периферийных вершин
set<Vertex> Floyd_Warshall::find_perif_vertex()
{
    int diametr = find_diametr_and_radius().first;
    vector<int> ecc = eccentricity();
    set<Vertex> perifVertex;                      // Множество
    for (int i = 0; i < ecc.size(); ++i) {        // Перебор
        if (ecc[i] == diametr) perifVertex.insert({ i + 1 });
    }
    return perifVertex;
}
//----------------------------------------------------------------------------------------//