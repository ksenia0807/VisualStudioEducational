#include"Graph.h"

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
	pair<vector<Edge>, int> DijkstraShortestPath(const int& start, const int& end)
    {
        vector<int> distance(graph.countVertex, numeric_limits<int>::max());    // ������������� ���������� �� ������
        vector<int> previous(graph.countVertex, -1);                            // ���������� ������� �� ���� � ������ �������
        vector<bool> visited(graph.countVertex, false);                         // ������ ���������� ������

        // ������ ����
        vector<Edge> edges = graph.list_of_edges();

        // �������� ������ ��������� �� ������ �����
        vector<vector<Edge>> adjacencyList(graph.countVertex);
        for (const Edge& edge : edges) {
            adjacencyList[edge.start.index].push_back(edge);
        }

        // ������� � ����������� ��� ������ ������� � ����������� �����������
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[start] = 0;            // ���������� �� ��������� ������� ����� 0
        pq.push(make_pair(distance[start], start));

        // ���� ������� �� �����
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == end) {
                break;                  // ���������� �������� �������, ����� �� �����
            }

            // �������� ������� ��� ����������
            visited[u] = true;

            // �������� �� ���� ������� ������ �������
            for (const Edge& edge : edges) {
                if (edge.start.index == u) {
                    int v = edge.end.index;
                    int weight = edge.weight;

                    // ���� ������� �� �������� � ����� ���������� �� ��� ������ ��������
                    if (!visited[v] && distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;  // ��������� ����������
                        previous[v] = u;  // ���������� ���������� �������

                        pq.push(std::make_pair(distance[v], v));  // ��������� � �������
                    }
                }
            }
        }

        // �������������� ����
        vector<Edge> path;
        int current = end;
        while (current != -1) {
            if (previous[current] != -1) {
                for (const Edge& edge : adjacencyList[previous[current]]) {
                    if (edge.end.index == current) {
                        path.insert(path.begin(), edge);  // ��������� ����� � ������ ������
                        break;
                    }
                }
            }
            current = previous[current];
        }

        return make_pair(path, distance[end]);
    }
};
