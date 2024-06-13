#include"Graph.h"   // ���������

// �������� �����-����������
class FordFulkerson
{
private:
    Graph graph;    // ����

public:

    // �����������
    FordFulkerson(const Graph& graph) :graph(graph)
    {}

    // ������� ��� ������ ������ � ����� � �����
    pair<int, int> findSourceSink()
    {
        vector<int> inDegree(graph.countVertex, 0);
        vector<int> outDegree(graph.countVertex, 0);

        // ��������� ������� ������ � ������ ��� ������ �������
        for (int u = 0; u < graph.countVertex; ++u) {
            for (int v = 0; v < graph.countVertex; ++v) {
                if (graph.adjacencyMatrix[u][v] > 0) {
                    ++outDegree[u];
                    ++inDegree[v];
                }
            }
        }

        // ���� ������� � ������� �������� ������ � ������������ �������� ������ - �����
        // ���� ������� � ������� �������� ������ � ������������ �������� ������ - ����
        int source = -1;
        int sink = -1;
        for (int i = 0; i < graph.countVertex; i++) {
            if (inDegree[i] == 0 && outDegree[i] > 0 && (source == -1 || (source != -1 && outDegree[i] > outDegree[source]))) {
                source = i;
            }
            if (outDegree[i] == 0 && inDegree[i] > 0 && (sink == -1 || (sink != -1 && inDegree[i] > inDegree[sink]))) {
                sink = i;
            }
        }
        return make_pair(source, sink);
    }

    // ������� ��� ������ ������������� ������ � ����� ������� �����-����������
    pair<vector<Edge>, int> fordFulkerson(const int& source, const int& sink)
    {
        // ������� ��������� ����������� �����
        vector<vector<int>> residualMatrix(graph.countVertex, vector<int>(graph.countVertex, 0));
        vector<Edge> edges = graph.list_of_edges(); // ������ �����

        // ������������� ����������� ����� � ������ �����
        for (int u = 0; u < graph.countVertex; u++) {
            for (int v = 0; v < graph.countVertex; v++) {
                if (graph.adjacencyMatrix[u][v] != 0) {
                    residualMatrix[u][v] = graph.adjacencyMatrix[u][v];
                }
            }
        }

        int maxFlow = 0; // ������������� ������������� ������

        // ��������� ����� �������������� ����, ���� ���� ���� �� ������ � ����� � ���������� �����
        while (true) {
            // BFS ��� ������ ���� �� ������ � �����
            vector<int> parent(graph.countVertex, -1);
            queue<int> q;
            q.push(source);
            parent[source] = -2; // ����� �������� ��������� ���������

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < graph.countVertex; ++v) {
                    if (parent[v] == -1 && residualMatrix[u][v] != 0) {
                        q.push(v);
                        parent[v] = u;
                    }
                }
            }

            // ���� �������� ����� � ���������� �����, �� ��������� ����� ����� ��������� ����
            if (parent[sink] != -1) {
                int pathFlow = INF;

                // ������� ����������� ���������� ����������� ����� � ��������� ����
                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    for (auto& edge : edges) {
                        if (edge.start.index == u && edge.end.index == v) {
                            pathFlow = min(pathFlow, edge.weight - edge.flow);
                            break;
                        }
                    }
                }

                // ��������� ����� ����� ������ ����� � ���������� �����
                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    for (auto& edge : edges) {
                        if (edge.start.index == u && edge.end.index == v) {
                            edge.flow += pathFlow;
                            residualMatrix[u][v] -= pathFlow;  // ���������� ���������� ���������� ����������� � ������ �����������
                            break;
                        }
                    }

                    for (auto& edge : edges) {
                        if (edge.start.index == v && edge.end.index == u) {
                            edge.flow -= pathFlow;
                            residualMatrix[v][u] += pathFlow;  // ���������� ���������� ���������� ����������� � �������� �����������
                            break;
                        }
                    }
                }

                maxFlow += pathFlow; // ����������� ������������ �����
            }
            else {
                break; // ���� �� ������ ����, ������� �� �����
            }
        }

        return make_pair(edges, maxFlow);
    }

};
