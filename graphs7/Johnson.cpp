#include"Graph.h"

class Johnson
{
private:

    vector<vector<int>> graph;	// Матрица графа, подогнанная под алгоритм(0 -> inf)

public:

    // Конструктор
    Johnson(const vector<vector<int>>& graph) : graph(graph)
    {}

    // Функция для расслабления ребра
    void relaxEdge(const int& u, const int& v, const int& weight, vector<int>& distance)
    {
        // Если существует более короткий путь от вершины u до вершины v через текущее ребро,
           // то обновляем расстояние до вершины v
        if (distance[u] != INF && distance[v] > distance[u] + weight) {
            distance[v] = distance[u] + weight;
        }
    }

    // Функция для поиска кратчайших путей с использованием алгоритма Беллмана-Форда
    bool bellmanFord(const vector<vector<int>>& matrix, const int& countVertex, vector<int>& distance)
    {
        // Инициализируем массив расстояний значением INT_MAX, представляющим бесконечность
        distance.resize(countVertex, INF);
        // Расстояние от начальной вершины до самой себя равно 0
        distance[0] = 0;

        // Выполняем релаксацию ребер (n-1) раз, где n - количество вершин в графе
        for (int i = 0; i < countVertex - 1; ++i) {
            // Проходим по всем вершинам
            for (int u = 0; u < countVertex; ++u) {
                // Проходим по всем соседним вершинам
                for (int v = 0; v < countVertex; ++v) {
                    // Если существует ребро между вершинами u и v, выполняем релаксацию
                    if (matrix[u][v] != INF) {
                        relaxEdge(u, v, matrix[u][v], distance);
                    }
                }
            }
        }

        // Проверяем наличие отрицательных циклов
        // Если расстояние до какой-либо вершины уменьшается после (n-1)-й итерации,
        // то граф содержит отрицательный цикл
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (matrix[u][v] != INF && distance[u] != INF && distance[v] > distance[u] + matrix[u][v]) {
                    return false; // Обнаружен отрицательный цикл
                }
            }
        }

        return true;
    }

    // Функция для выполнения алгоритма Дейкстры
    void dijkstra(const vector<vector<int>>& matrix, const int& start, vector<int>& distance)
    {
        int vertices = matrix.size();
        // Инициализируем массив расстояний значением infinity, представляющим бесконечность
        distance.resize(vertices, INF);
        // Расстояние от начальной вершины до самой себя равно 0
        distance[start] = 0;

        // Используем приоритетную очередь для выбора вершин с наименьшим расстоянием
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            // Извлекаем вершину с наименьшим расстоянием
            int u = pq.top().second;
            pq.pop();

            // Проходим по всем соседним вершинам
            for (int v = 0; v < vertices; ++v) {
                // Если существует ребро между вершинами u и v, выполняем релаксацию
                if (matrix[u][v] != INF) {
                    if (distance[u] + matrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + matrix[u][v];
                        pq.push(make_pair(distance[v], v));
                    }
                }
            }
        }
    }

    // Функция для выполнения алгоритма Джонсона
    vector<vector<int>> johnson(bool& negCycle)
    {
        vector<vector<int>> everyDistance;  // Результирующая матрица расстояний
        int countVertex = graph.size();
        vector<int> distance;

        // Добавляем фиктивную вершину и выполняем алгоритм Беллмана-Форда
        vector<vector<int>> fictMatrix(countVertex + 1, vector<int>(countVertex + 1, INF));
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (graph[u][v] != INF) {
                    fictMatrix[u][v] = graph[u][v];
                }
            }
            fictMatrix[u][u] = 0;
        }

        // Наличие отрицательного цикла
        if (!bellmanFord(fictMatrix, countVertex + 1, distance)) {
            negCycle = true;
            return everyDistance;
        }

        // Удаляем фиктивную вершину и корректируем веса ребер
        fictMatrix.pop_back();
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (graph[u][v] != INF) {
                    fictMatrix[u][v] = fictMatrix[u][v] + distance[u] - distance[v];
                }
            }
        }

        // Выполняем алгоритм Дейкстры для каждой вершины
        for (int u = 0; u < countVertex; ++u) {
            vector<int> shortestPaths;
            dijkstra(fictMatrix, u, shortestPaths);

            // Восстанавливаем исходные веса ребер
            for (int v = 0; v < countVertex; ++v) {
                if (shortestPaths[v] != INF) {
                    shortestPaths[v] = shortestPaths[v] - distance[u] + distance[v];
                }
            }

            everyDistance.push_back(shortestPaths);     // Для текущей вершины пихаем вектор расстояний в результирующую матрицу расстояний
        }
        return everyDistance;
    }

};