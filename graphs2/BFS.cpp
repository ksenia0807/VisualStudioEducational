#include"Graph.h"	// Заголовок класса

// Класс поиска в ширину
class BFS
{
private:
	Graph graph;	// Граф

public:

	// Конструктор
    BFS(const Graph & graph) :graph(graph)
    {}

	// Поиск в ширину, возвращает компоненту связности
	vector<int> bfs(vector<bool>& visited, const int& start) {
        vector<int> component;  // Компонента связности
        queue<int> q;           // Очередь
        visited[start] = true;  // Первая вершина посещена
        q.push(start);          // Первую вершину в очередь

        while (!q.empty()) {                    // Пока очередь не пуста
            int node = q.front();               // Текущая = первая в очереди
            q.pop();                            // Удаляем из очередь первую вершину
            component.push_back(node);          // Вершину в компоненту

            for (const auto& neighbor : graph.list_of_edges({ node })) {  // Идем по строке матрицы смежности текущей вершины
                if (!visited[neighbor.end.index]) {                       // Если вершина не посещена
                    visited[neighbor.end.index] = true;                   // Ставим флаг посещения
                    q.push(neighbor.end.index);                           // Добавляем очередь вершину
                }
            }
        }
        return component;
    }
};

