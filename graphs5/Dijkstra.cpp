#include"Graph.h"

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
	pair<vector<Edge>, int> DijkstraShortestPath(const int& start, const int& end)
    {
        vector<int> distance(graph.countVertex, numeric_limits<int>::max());    // Инициализация расстояний до вершин
        vector<int> previous(graph.countVertex, -1);                            // Предыдущая вершина на пути к каждой вершине
        vector<bool> visited(graph.countVertex, false);                         // Вектор посещенных вершин

        // Список рёбер
        vector<Edge> edges = graph.list_of_edges();

        // Создание списка смежности на основе ребер
        vector<vector<Edge>> adjacencyList(graph.countVertex);
        for (const Edge& edge : edges) {
            adjacencyList[edge.start.index].push_back(edge);
        }

        // Очередь с приоритетом для выбора вершины с минимальным расстоянием
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[start] = 0;            // Расстояние до начальной вершины равно 0
        pq.push(make_pair(distance[start], start));

        // Пока очередь не пуста
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == end) {
                break;                  // Достигнута конечная вершина, выход из цикла
            }

            // Пометить вершину как посещенную
            visited[u] = true;

            // Проходим по всем смежным ребрам вершины
            for (const Edge& edge : edges) {
                if (edge.start.index == u) {
                    int v = edge.end.index;
                    int weight = edge.weight;

                    // Если вершина не посещена и новое расстояние до нее меньше текущего
                    if (!visited[v] && distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;  // Обновляем расстояние
                        previous[v] = u;  // Запоминаем предыдущую вершину

                        pq.push(std::make_pair(distance[v], v));  // Добавляем в очередь
                    }
                }
            }
        }

        // Восстановление пути
        vector<Edge> path;
        int current = end;
        while (current != -1) {
            if (previous[current] != -1) {
                for (const Edge& edge : adjacencyList[previous[current]]) {
                    if (edge.end.index == current) {
                        path.insert(path.begin(), edge);  // Добавляем ребро в начало списка
                        break;
                    }
                }
            }
            current = previous[current];
        }

        return make_pair(path, distance[end]);
    }
};
