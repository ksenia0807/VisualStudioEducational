#pragma once
#include "Graph.h"  // Заголовок

// Структура, представляющая набор для объединения
struct Subset {

    int parent, rank;
};

// Класс алгоритма Крускала
class Kruskal
{
private:

    Graph graph;

public:

    // Конструктор
    /*Kruskal(const Graph& graph);*/
    Kruskal(const Graph& graph) : graph(graph)
    {}

    // Функция для нахождения корня подмножества с использованием компрессии пути
    int find(Subset subsets[], const int& i)
    {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    // Функция для объединения двух подмножеств на основе ранга
    void unionSets(Subset subsets[], const int& x, const int& y)
    {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

    // Функция для поиска минимального остовного дерева с использованием алгоритма Крускала
    vector<Edge> kruskalMST()
    {
        vector<Edge> result; // Результирующий вектор ребер
        vector<Edge> edges = graph.list_of_edges();
        // Сортируем ребра по возрастанию весов
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight; });

        Subset* subsets = new Subset[graph.countVertex];

        // Инициализация каждого подмножества
        for (int i = 0; i < graph.countVertex; ++i) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }

        int edgeCount = 0;
        int edgeIndex = 0;

        // Проходим по всем ребрам и добавляем их в остовное дерево, если они не образуют цикл
        while (edgeCount < graph.countVertex - 1 && edgeIndex < edges.size()) {
            Edge nextEdge = edges[edgeIndex++];

            int x = find(subsets, nextEdge.start.index);
            int y = find(subsets, nextEdge.end.index);

            // Если ребро не образует цикл, добавляем его в остовное дерево
            if (x != y) {
                result.push_back(nextEdge);
                unionSets(subsets, x, y);
                ++edgeCount;
            }
        }

        delete[] subsets;

        return result;
    }
};

// Класс алгоритма Прима
class Prim
{
private:
    Graph graph;    // Граф

public:

    // Конструктор
    Prim(const Graph& graph) : graph(graph)
    {}

    // Функция для реализации алгоритма Прима
    vector<Edge> primMST()
    {
        vector<bool> visited(graph.countVertex, false);     // Посещенные вершины
        vector<Edge> minimumSpanningTree;                   // Минимальное остовное дерево

        // Создаем приоритетную очередь для выбора ребер с минимальным весом
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        // Начинаем с выбранной стартовой вершины
        visited[0] = true;

        // Добавляем все ребра, выходящие из стартовой вершины, в приоритетную очередь
        for (const auto& edge : graph.list_of_edges({ 0 })) {
            pq.push(edge);
        }

        while (!pq.empty()) {
            // Извлекаем ребро с минимальным весом из очереди
            Edge currentEdge = pq.top();
            pq.pop();

            int vertex = currentEdge.end.index;
            int weight = currentEdge.weight;

            // Если вершина уже посещена, пропускаем ее
            if (visited[vertex]) {
                continue;
            }

            // Добавляем ребро в минимальное остовное дерево
            minimumSpanningTree.push_back(currentEdge);

            // Помечаем вершину как посещенную
            visited[vertex] = true;

            // Добавляем все ребра, выходящие из текущей вершины, в приоритетную очередь
            for (const auto& edge : graph.list_of_edges({ vertex })) {
                if (!visited[edge.end.index]) {
                    pq.push(edge);
                }
            }
        }

        return minimumSpanningTree;
    }
};

// Класс алгоритма Борувки
class Boruvka
{
private:

    Graph graph;    // Граф

public:

    // Конструктор
    /*Boruvka(const Graph& graph);*/
    Boruvka(const Graph& graph) : graph(graph) {}

    // Функция для поиска корня подмножества с использованием сжатия пути
    int find(vector<int>& parent, const int& i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    // Функция для объединения двух подмножеств на основе ранга
    void Union(vector<int>& parent, vector<int>& rank, const int& x, const int& y)
    {
        int xroot = find(parent, x);
        int yroot = find(parent, y);
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    // Функция для построения минимального остовного дерева с помощью алгоритма Борувки
    vector<Edge> boruvkaMST()
    {
        // Инициализация минимального остовного дерева и вспомогательных структур данных
        vector<Edge> minimumSpanningTree;
        vector<int> parent(graph.countVertex, -1);
        vector<int> rank(graph.countVertex, 0);

        int numTrees = graph.countVertex;
        int minWeight = 0;

        vector<Edge> edges = graph.list_of_edges();

        // Повторяем, пока не останется только одно дерево
        while (numTrees > 1) {
            vector<int> cheapest(graph.countVertex, -1);

            // Находим минимальное ребро для каждого подмножества
            for (int i = 0; i < edges.size(); i++) {
                int x = find(parent, edges[i].start.index);
                int y = find(parent, edges[i].end.index);

                if (x != y) {
                    if (cheapest[x] == -1 || edges[i].weight < edges[cheapest[x]].weight)
                        cheapest[x] = i;
                    if (cheapest[y] == -1 || edges[i].weight < edges[cheapest[y]].weight)
                        cheapest[y] = i;
                }
            }

            // Объединяем подмножества, используя найденные минимальные ребра
            for (int i = 0; i < graph.countVertex; i++) {
                if (cheapest[i] != -1) {
                    int x = find(parent, edges[cheapest[i]].start.index);
                    int y = find(parent, edges[cheapest[i]].end.index);

                    if (x != y) {
                        minimumSpanningTree.push_back(edges[cheapest[i]]);
                        minWeight += edges[cheapest[i]].weight;
                        Union(parent, rank, x, y);
                        numTrees--;
                    }
                }
            }
        }

        return minimumSpanningTree;
    }
};