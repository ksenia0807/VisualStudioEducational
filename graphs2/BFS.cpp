#include"Graph.h"	// ��������� ������

// ����� ������ � ������
class BFS
{
private:
	Graph graph;	// ����

public:

	// �����������
    BFS(const Graph & graph) :graph(graph)
    {}

	// ����� � ������, ���������� ���������� ���������
	vector<int> bfs(vector<bool>& visited, const int& start) {
        vector<int> component;  // ���������� ���������
        queue<int> q;           // �������
        visited[start] = true;  // ������ ������� ��������
        q.push(start);          // ������ ������� � �������

        while (!q.empty()) {                    // ���� ������� �� �����
            int node = q.front();               // ������� = ������ � �������
            q.pop();                            // ������� �� ������� ������ �������
            component.push_back(node);          // ������� � ����������

            for (const auto& neighbor : graph.list_of_edges({ node })) {  // ���� �� ������ ������� ��������� ������� �������
                if (!visited[neighbor.end.index]) {                       // ���� ������� �� ��������
                    visited[neighbor.end.index] = true;                   // ������ ���� ���������
                    q.push(neighbor.end.index);                           // ��������� ������� �������
                }
            }
        }
        return component;
    }
};

