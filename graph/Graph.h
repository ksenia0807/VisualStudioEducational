#pragma once
// ����������
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

// �������� � ����������� ������������ ���
using namespace std;

// �������
struct Vertex {
    int index;  // ������ �������

    bool operator<(const Vertex& other) const
    {
        return this->index < other.index;
    }
};

// �����/����
struct Edge {
    Vertex start;   // ������
    Vertex end;     // �����
    int weight;     // ��� �����/����

    // �����������
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

// ����� ����
class Graph
{
public:

    // �����������
    Graph(const string& file_path, const string& file_type);

    // ����������� �� ������� ���������
    Graph(const vector<vector<int>>& adjMatr);

    // ���� �� ����� �����/���� � �����
    bool is_edge(const Vertex& vi, const Vertex& vj) const;

    // ��� �����/����
    int weight(const Vertex& vi, const Vertex& vj) const;

    // ������� ��������� �����/�������
    vector<vector<int>> adjacency_matrix() const;

    // ������ ������, ������� ������� v
    vector<Vertex> adjacency_list(const Vertex& v) const;

    // ������ ��������� �����
    vector<vector<Vertex>> adjacency_list() const;

    // ������ ���� �����/��� �����
    vector<Edge> list_of_edges() const;

    // ������ ���� ���� �����, ����������� ������� v / ��������� �� ������� v
    vector<Edge> list_of_edges(const Vertex& v) const;

    // ����/������
    bool is_directed();

    int countVertex;                                // ���������� ������
    vector<vector<int>> adjacencyMatrix;            // ������� ���������
    bool isDirected;                                // ����, ����������� �� ����������������� �����

private:

    // ������ �� ������ �����
    void read_edge_list(const string& filePath);

    // ������ �� ������� ���������
    void read_adjacency_list(const string& filePath);

    // ������ �� ������� ���������
    void read_adjacency_matrix(const string& filePath);
};

