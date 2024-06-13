#include"Graph.h"

class Johnson
{
private:

    vector<vector<int>> graph;	// ������� �����, ����������� ��� ��������(0 -> inf)

public:

    // �����������
    Johnson(const vector<vector<int>>& graph) : graph(graph)
    {}

    // ������� ��� ������������ �����
    void relaxEdge(const int& u, const int& v, const int& weight, vector<int>& distance)
    {
        // ���� ���������� ����� �������� ���� �� ������� u �� ������� v ����� ������� �����,
           // �� ��������� ���������� �� ������� v
        if (distance[u] != INF && distance[v] > distance[u] + weight) {
            distance[v] = distance[u] + weight;
        }
    }

    // ������� ��� ������ ���������� ����� � �������������� ��������� ��������-�����
    bool bellmanFord(const vector<vector<int>>& matrix, const int& countVertex, vector<int>& distance)
    {
        // �������������� ������ ���������� ��������� INT_MAX, �������������� �������������
        distance.resize(countVertex, INF);
        // ���������� �� ��������� ������� �� ����� ���� ����� 0
        distance[0] = 0;

        // ��������� ���������� ����� (n-1) ���, ��� n - ���������� ������ � �����
        for (int i = 0; i < countVertex - 1; ++i) {
            // �������� �� ���� ��������
            for (int u = 0; u < countVertex; ++u) {
                // �������� �� ���� �������� ��������
                for (int v = 0; v < countVertex; ++v) {
                    // ���� ���������� ����� ����� ��������� u � v, ��������� ����������
                    if (matrix[u][v] != INF) {
                        relaxEdge(u, v, matrix[u][v], distance);
                    }
                }
            }
        }

        // ��������� ������� ������������� ������
        // ���� ���������� �� �����-���� ������� ����������� ����� (n-1)-� ��������,
        // �� ���� �������� ������������� ����
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (matrix[u][v] != INF && distance[u] != INF && distance[v] > distance[u] + matrix[u][v]) {
                    return false; // ��������� ������������� ����
                }
            }
        }

        return true;
    }

    // ������� ��� ���������� ��������� ��������
    void dijkstra(const vector<vector<int>>& matrix, const int& start, vector<int>& distance)
    {
        int vertices = matrix.size();
        // �������������� ������ ���������� ��������� infinity, �������������� �������������
        distance.resize(vertices, INF);
        // ���������� �� ��������� ������� �� ����� ���� ����� 0
        distance[start] = 0;

        // ���������� ������������ ������� ��� ������ ������ � ���������� �����������
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            // ��������� ������� � ���������� �����������
            int u = pq.top().second;
            pq.pop();

            // �������� �� ���� �������� ��������
            for (int v = 0; v < vertices; ++v) {
                // ���� ���������� ����� ����� ��������� u � v, ��������� ����������
                if (matrix[u][v] != INF) {
                    if (distance[u] + matrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + matrix[u][v];
                        pq.push(make_pair(distance[v], v));
                    }
                }
            }
        }
    }

    // ������� ��� ���������� ��������� ��������
    vector<vector<int>> johnson(bool& negCycle)
    {
        vector<vector<int>> everyDistance;  // �������������� ������� ����������
        int countVertex = graph.size();
        vector<int> distance;

        // ��������� ��������� ������� � ��������� �������� ��������-�����
        vector<vector<int>> fictMatrix(countVertex + 1, vector<int>(countVertex + 1, INF));
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (graph[u][v] != INF) {
                    fictMatrix[u][v] = graph[u][v];
                }
            }
            fictMatrix[u][u] = 0;
        }

        // ������� �������������� �����
        if (!bellmanFord(fictMatrix, countVertex + 1, distance)) {
            negCycle = true;
            return everyDistance;
        }

        // ������� ��������� ������� � ������������ ���� �����
        fictMatrix.pop_back();
        for (int u = 0; u < countVertex; ++u) {
            for (int v = 0; v < countVertex; ++v) {
                if (graph[u][v] != INF) {
                    fictMatrix[u][v] = fictMatrix[u][v] + distance[u] - distance[v];
                }
            }
        }

        // ��������� �������� �������� ��� ������ �������
        for (int u = 0; u < countVertex; ++u) {
            vector<int> shortestPaths;
            dijkstra(fictMatrix, u, shortestPaths);

            // ��������������� �������� ���� �����
            for (int v = 0; v < countVertex; ++v) {
                if (shortestPaths[v] != INF) {
                    shortestPaths[v] = shortestPaths[v] - distance[u] + distance[v];
                }
            }

            everyDistance.push_back(shortestPaths);     // ��� ������� ������� ������ ������ ���������� � �������������� ������� ����������
        }
        return everyDistance;
    }

};