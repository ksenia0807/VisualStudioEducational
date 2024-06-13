#include"Graph.h"	// ���������

// ��������
class Dijkstra
{
private:
	Graph graph;

public:

	// �����������
	Dijkstra(const Graph& graph) : graph(graph)
	{}

	// ������� ��� ������ ����������� ���� � �������������� ��������� ��������
	vector<int> DijkstraShortestPath(const int& start)
    {
        vector<Edge> edges = graph.list_of_edges();
        vector<int> distances(graph.countVertex, INF); // ������������� ���������� ��������������
        distances[start] = 0; // ���������� �� ��������� ������� �� ���� ����� 0

        // ������� � ����������� ��� ������ ������ � ���������� �����������
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(std::make_pair(0, start)); // ��������� ��������� ������� � �������

        while (!pq.empty()) {
            int currentVertex = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            // ���������� �������, ���� ��� ���� ���������� � ������� �����������
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // ������������� ��� �����, ��������� �� ������� �������
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

// ����� ��������� ��������-�����-����
class BellmanFord
{
private:

    Graph graph;	// ����

public:

    // �����������
    BellmanFord(const Graph& graph) : graph(graph)
    {}

    // ������� ��� ������ ����������� ���� � ���������� ����� start � end
    vector<int> BellmanFordMoore(const int& start, bool& negCycle)
    {
        vector<Edge> edges = graph.list_of_edges();

        vector<int> distance(graph.countVertex, INF);
        distance[start] = 0;

        // ���������� ����� (graph.countVertex - 1) ���
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

        // �������� ������� �������������� �����
        for (const auto& edge : edges) {
            int u = edge.start.index;
            int v = edge.end.index;
            int w = edge.weight;
            if (distance[u] != INF && distance[u] + w < distance[v]) {
                // ��������� ������������� ����
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
    Graph graph;	// ����

public:

    // �����������
    Levit(const Graph& graph) : graph(graph)
    {}

    // ������� ��� ������ ����������� ���� � ���������� ����� start � end
    vector<int> levit(const int& start, bool& negCycle)
    {
        vector<Edge> edges = graph.list_of_edges();

        // ������������� ���������� �� ���� ������ ��������������
        vector<int> distance(graph.countVertex, INF);
        // ������ ������ ��� ������������ ������ � �������
        vector<int> inQueue(graph.countVertex, 0);
        // ������� ���������� ��������� ������
        vector<int> count(graph.countVertex, 0);

        // ���������� �� ��������� ������� ����� 0
        distance[start] = 0;
        // �������� ������� � ��������� ��������� ������� � ���
        queue<int> queue;
        queue.push(start);
        // ������� ��������� ������� � �������
        inQueue[start] = 1;

        // �������� ������
        while (!queue.empty()) {
            // ���������� ������� �� �������
            int u = queue.front();
            queue.pop();
            // ������ ������� � ��������� �������
            inQueue[u] = 0;

            // ������� ���� ����� � ������ �����
            for (const auto& edge : edges) {
                // ���� ������� ������� �������� �������� �������� �����
                if (edge.start.index == u) {
                    int v = edge.end.index;
                    int weight = edge.weight;

                    // ���������� �����
                    if (distance[u] + weight < distance[v]) {
                        // ���������� ���������� �� ������� v
                        distance[v] = distance[u] + weight;

                        // ���� ������� v �� ��������� � �������
                        if (!inQueue[v]) {
                            // ���� ������� v �������� ����� numVertices ���,
                            // ������ � ����� ���� ������������� ����
                            if (count[v] >= graph.countVertex) {
                                negCycle = true;
                                return distance;
                            }
                            // ���������� ������� v � ������� � ������� � �� ���������
                            queue.push(v);
                            inQueue[v] = 1;
                            // ���������� �������� ��������� ������� v
                            ++count[v];
                        }
                    }
                }
            }
        }

        return distance;
    }

};

