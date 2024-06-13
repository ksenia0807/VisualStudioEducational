#pragma once
// Библиотеки
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <set>
#include <queue>

#define INF 1e9

// Работаем в стандартном пространстве имён
using namespace std;

// Вершина
struct Vertex {
    int index;  // Индекс вершины

    bool operator<(const Vertex& other) const
    {
        return this->index < other.index;
    }
};

// Ребро/дуга
struct Edge {
    Vertex start;   // Начало
    Vertex end;     // Конец
    int weight;     // Вес ребра/дуги

    // Конструктор
    Edge(const Vertex& v1, const Vertex& v2, const int& w) : start(v1), end(v2), weight(w) {}

    bool operator<(const Edge& other) const
    {
        return this->weight < other.weight;
    }
    bool operator>(const Edge& other) const
    {
        return this->weight > other.weight;
    }
};

// Класс Граф
class Graph
{
public:

    // Конструктор
    Graph(const string& file_path, const string& file_type);

    // Конструктор по матрице смежности
    Graph(const vector<vector<int>>& adjMatr);

    // Есть ли такое ребро/дуга в графе
    bool is_edge(const Vertex& vi, const Vertex& vj) const;

    // Вес ребра/дуги
    int weight(const Vertex& vi, const Vertex& vj) const;

    // Матрица смежности графа/орграфа
    vector<vector<int>> adjacency_matrix() const;

    // Список вершин, смежных вершине v
    vector<Vertex> adjacency_list(const Vertex& v) const;

    // Список смежности графа
    vector<vector<Vertex>> adjacency_list() const;

    // Список всех ребер/дуг графа
    vector<Edge> list_of_edges() const;

    // Список всех рёбер графа, инцидентных вершине v / исходящих из вершины v
    vector<Edge> list_of_edges(const Vertex& v) const;

    // Граф/орграф
    bool is_directed();

    int countVertex;                                // Количество вершин
    vector<vector<int>> adjacencyMatrix;            // Матрица смежности
    bool isDirected;                                // Флаг, указывающий на ориентированность графа

private:

    // Чтение из списка ребер
    void read_edge_list(const string& filePath);

    // Чтение из списков смежности
    void read_adjacency_list(const string& filePath);

    // Чтение из матрицы смежности
    void read_adjacency_matrix(const string& filePath);
};

