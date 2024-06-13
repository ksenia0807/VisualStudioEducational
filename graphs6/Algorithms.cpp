#include"Graph.h"	// Заголовок

// Дейкстра
class Dijkstra
{
private:
	Graph graph;

public:

	// Конструктор
	Dijkstra(const Graph& graph) : graph(graph)
	{}

	// Функция для поиска кратчайшего пути с использованием алгоритма Дейкстры
	vector<int> DijkstraShortestPath(const int& start)
    {
        vector<Edge> edges = graph.list_of_edges();
        vector<int> distances(graph.countVertex, INF); // Инициализация расстояний бесконечностью
        distances[start] = 0; // Расстояние от начальной вершины до себя равно 0

        // Очередь с приоритетом для выбора вершин с наименьшим расстоянием
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(std::make_pair(0, start)); // Добавляем начальную вершину в очередь

        while (!pq.empty()) {
            int currentVertex = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            // Пропускаем вершину, если уже была обработана с меньшим расстоянием
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // Просматриваем все ребра, выходящие из текущей вершины
            for (const Edge& edge : edges) {
                if (edge.start.index == currentVertex) {
                    int newDistance = currentDistance + edge.weight;
                    if (newDistance < distances[edge.end.index]) {
                        distances[edge.end.index] = newDistance;
                        pq.push(std::make_pair(newDistance, edge.end.index));
                    }
                }
            }
        }

        return distances;
    }
};

// Класс алгоритма Беллмана-Форда-Мура
class BellmanFord
{
private:

    Graph graph;	// Граф

public:

    // Конструктор
    BellmanFord(const Graph& graph) : graph(graph)
    {}

    // Функция для поиска кратчайшего пути и расстояния между start и end
    vector<int> BellmanFordMoore(const int& start, bool& negCycle)
    {
        vector<Edge> edges = graph.list_of_edges();

        vector<int> distance(graph.countVertex, INF);
        distance[start] = 0;

        // Релаксация ребер (graph.countVertex - 1) раз
        for (int i = 1; i <= graph.countVertex - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.start.index;
                int v = edge.end.index;
                int w = edge.weight;
                if (distance[u] != INF && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }

        // Проверка наличия отрицательного цикла
        for (const auto& edge : edges) {
            int u = edge.start.index;
            int v = edge.end.index;
            int w = edge.weight;
            if (distance[u] != INF && distance[u] + w < distance[v]) {
                // Обнаружен отрицательный цикл
                negCycle = true;
                break;
            }
        }

        return distance;
    }
};

class Levit
{
private:
    Graph graph;	// Граф

public:

    // Конструктор
    Levit(const Graph& graph) : graph(graph)
    {}

    // Функция для поиска кратчайшего пути и расстояния между start и end
    vector<int> levit(const int& start, bool& negCycle)
    {
        vector<Edge> edges = graph.list_of_edges();

        // Инициализация расстояний до всех вершин бесконечностью
        vector<int> distance(graph.countVertex, INF);
        // Список флагов для отслеживания вершин в очереди
        vector<int> inQueue(graph.countVertex, 0);
        // Счетчик количества посещений вершин
        vector<int> count(graph.countVertex, 0);

        // Расстояние до начальной вершины равно 0
        distance[start] = 0;
        // Создание очереди и помещение начальной вершины в нее
        queue<int> queue;
        queue.push(start);
        // Отметка начальной вершины в очереди
        inQueue[start] = 1;

        // Алгоритм Левита
        while (!queue.empty()) {
            // Извлечение вершины из очереди
            int u = queue.front();
            queue.pop();
            // Снятие отметки о посещении вершины
            inQueue[u] = 0;

            // Перебор всех ребер в списке ребер
            for (const auto& edge : edges) {
                // Если текущая вершина является исходной вершиной ребра
                if (edge.start.index == u) {
                    int v = edge.end.index;
                    int weight = edge.weight;

                    // Релаксация ребра
                    if (distance[u] + weight < distance[v]) {
                        // Обновление расстояния до вершины v
                        distance[v] = distance[u] + weight;

                        // Если вершина v не находится в очереди
                        if (!inQueue[v]) {
                            // Если вершина v посещена более numVertices раз,
                            // значит в графе есть отрицательный цикл
                            if (count[v] >= graph.countVertex) {
                                negCycle = true;
                                return distance;
                            }
                            // Добавление вершины v в очередь и отметка о ее посещении
                            queue.push(v);
                            inQueue[v] = 1;
                            // Увеличение счетчика посещений вершины v
                            ++count[v];
                        }
                    }
                }
            }
        }

        return distance;
    }

};

