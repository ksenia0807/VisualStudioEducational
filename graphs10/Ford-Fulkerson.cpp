#include"Graph.h"   // Заголовок

// Алгоритм Форда-Фалкерсона
class FordFulkerson
{
private:
    Graph graph;    // Граф

public:

    // Конструктор
    FordFulkerson(const Graph& graph) :graph(graph)
    {}

    // Функция для поиска истока и стока в графе
    pair<int, int> findSourceSink()
    {
        vector<int> inDegree(graph.countVertex, 0);
        vector<int> outDegree(graph.countVertex, 0);

        // Вычисляем степени захода и исхода для каждой вершины
        for (int u = 0; u < graph.countVertex; ++u) {
            for (int v = 0; v < graph.countVertex; ++v) {
                if (graph.adjacencyMatrix[u][v] > 0) {
                    ++outDegree[u];
                    ++inDegree[v];
                }
            }
        }

        // Ищем вершину с нулевой степенью захода и максимальной степенью исхода - исток
        // Ищем вершину с нулевой степенью исхода и максимальной степенью захода - сток
        int source = -1;
        int sink = -1;
        for (int i = 0; i < graph.countVertex; i++) {
            if (inDegree[i] == 0 && outDegree[i] > 0 && (source == -1 || (source != -1 && outDegree[i] > outDegree[source]))) {
                source = i;
            }
            if (outDegree[i] == 0 && inDegree[i] > 0 && (sink == -1 || (sink != -1 && inDegree[i] > inDegree[sink]))) {
                sink = i;
            }
        }
        return make_pair(source, sink);
    }

    // Функция для поиска максимального потока в графе методом Форда-Фалкерсона
    pair<vector<Edge>, int> fordFulkerson(const int& source, const int& sink)
    {
        // Матрица смежности остаточного графа
        vector<vector<int>> residualMatrix(graph.countVertex, vector<int>(graph.countVertex, 0));
        vector<Edge> edges = graph.list_of_edges(); // Список ребер

        // Инициализация остаточного графа и списка ребер
        for (int u = 0; u < graph.countVertex; u++) {
            for (int v = 0; v < graph.countVertex; v++) {
                if (graph.adjacencyMatrix[u][v] != 0) {
                    residualMatrix[u][v] = graph.adjacencyMatrix[u][v];
                }
            }
        }

        int maxFlow = 0; // Инициализация максимального потока

        // Повторяем поиск увеличивающего пути, пока есть путь от истока к стоку в остаточном графе
        while (true) {
            // BFS для поиска пути от истока к стоку
            vector<int> parent(graph.countVertex, -1);
            queue<int> q;
            q.push(source);
            parent[source] = -2; // Исток помечаем отдельным значением

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < graph.countVertex; ++v) {
                    if (parent[v] == -1 && residualMatrix[u][v] != 0) {
                        q.push(v);
                        parent[v] = u;
                    }
                }
            }

            // Если достигли стока в остаточном графе, то вычисляем поток через найденный путь
            if (parent[sink] != -1) {
                int pathFlow = INF;

                // Находим минимальную пропускную способность ребер в найденном пути
                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    for (auto& edge : edges) {
                        if (edge.start.index == u && edge.end.index == v) {
                            pathFlow = min(pathFlow, edge.weight - edge.flow);
                            break;
                        }
                    }
                }

                // Обновляем поток через каждое ребро в остаточном графе
                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    for (auto& edge : edges) {
                        if (edge.start.index == u && edge.end.index == v) {
                            edge.flow += pathFlow;
                            residualMatrix[u][v] -= pathFlow;  // Обновление остаточной пропускной способности в прямом направлении
                            break;
                        }
                    }

                    for (auto& edge : edges) {
                        if (edge.start.index == v && edge.end.index == u) {
                            edge.flow -= pathFlow;
                            residualMatrix[v][u] += pathFlow;  // Обновление остаточной пропускной способности в обратном направлении
                            break;
                        }
                    }
                }

                maxFlow += pathFlow; // Увеличиваем максимальный поток
            }
            else {
                break; // Если не найден путь, выходим из цикла
            }
        }

        return make_pair(edges, maxFlow);
    }

};
