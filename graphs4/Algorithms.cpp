#pragma once
#include "Graph.h"  // ���������

// ���������, �������������� ����� ��� �����������
struct Subset {

    int parent, rank;
};

// ����� ��������� ��������
class Kruskal
{
private:

    Graph graph;

public:

    // �����������
    /*Kruskal(const Graph& graph);*/
    Kruskal(const Graph& graph) : graph(graph)
    {}

    // ������� ��� ���������� ����� ������������ � �������������� ���������� ����
    int find(Subset subsets[], const int& i)
    {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    // ������� ��� ����������� ���� ����������� �� ������ �����
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

    // ������� ��� ������ ������������ ��������� ������ � �������������� ��������� ��������
    vector<Edge> kruskalMST()
    {
        vector<Edge> result; // �������������� ������ �����
        vector<Edge> edges = graph.list_of_edges();
        // ��������� ����� �� ����������� �����
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight; });

        Subset* subsets = new Subset[graph.countVertex];

        // ������������� ������� ������������
        for (int i = 0; i < graph.countVertex; ++i) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }

        int edgeCount = 0;
        int edgeIndex = 0;

        // �������� �� ���� ������ � ��������� �� � �������� ������, ���� ��� �� �������� ����
        while (edgeCount < graph.countVertex - 1 && edgeIndex < edges.size()) {
            Edge nextEdge = edges[edgeIndex++];

            int x = find(subsets, nextEdge.start.index);
            int y = find(subsets, nextEdge.end.index);

            // ���� ����� �� �������� ����, ��������� ��� � �������� ������
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

// ����� ��������� �����
class Prim
{
private:
    Graph graph;    // ����

public:

    // �����������
    Prim(const Graph& graph) : graph(graph)
    {}

    // ������� ��� ���������� ��������� �����
    vector<Edge> primMST()
    {
        vector<bool> visited(graph.countVertex, false);     // ���������� �������
        vector<Edge> minimumSpanningTree;                   // ����������� �������� ������

        // ������� ������������ ������� ��� ������ ����� � ����������� �����
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        // �������� � ��������� ��������� �������
        visited[0] = true;

        // ��������� ��� �����, ��������� �� ��������� �������, � ������������ �������
        for (const auto& edge : graph.list_of_edges({ 0 })) {
            pq.push(edge);
        }

        while (!pq.empty()) {
            // ��������� ����� � ����������� ����� �� �������
            Edge currentEdge = pq.top();
            pq.pop();

            int vertex = currentEdge.end.index;
            int weight = currentEdge.weight;

            // ���� ������� ��� ��������, ���������� ��
            if (visited[vertex]) {
                continue;
            }

            // ��������� ����� � ����������� �������� ������
            minimumSpanningTree.push_back(currentEdge);

            // �������� ������� ��� ����������
            visited[vertex] = true;

            // ��������� ��� �����, ��������� �� ������� �������, � ������������ �������
            for (const auto& edge : graph.list_of_edges({ vertex })) {
                if (!visited[edge.end.index]) {
                    pq.push(edge);
                }
            }
        }

        return minimumSpanningTree;
    }
};

// ����� ��������� �������
class Boruvka
{
private:

    Graph graph;    // ����

public:

    // �����������
    /*Boruvka(const Graph& graph);*/
    Boruvka(const Graph& graph) : graph(graph) {}

    // ������� ��� ������ ����� ������������ � �������������� ������ ����
    int find(vector<int>& parent, const int& i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    // ������� ��� ����������� ���� ����������� �� ������ �����
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

    // ������� ��� ���������� ������������ ��������� ������ � ������� ��������� �������
    vector<Edge> boruvkaMST()
    {
        // ������������� ������������ ��������� ������ � ��������������� �������� ������
        vector<Edge> minimumSpanningTree;
        vector<int> parent(graph.countVertex, -1);
        vector<int> rank(graph.countVertex, 0);

        int numTrees = graph.countVertex;
        int minWeight = 0;

        vector<Edge> edges = graph.list_of_edges();

        // ���������, ���� �� ��������� ������ ���� ������
        while (numTrees > 1) {
            vector<int> cheapest(graph.countVertex, -1);

            // ������� ����������� ����� ��� ������� ������������
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

            // ���������� ������������, ��������� ��������� ����������� �����
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