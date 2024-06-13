#include "Graph.h"

class DFS
{
private:
	Graph graph;		// ����

public:

    // �����������
    DFS(const Graph& graph);

	// ����� ������
	void bridgesDFS(const int& v, vector<bool>& visited, vector<int>& tin, vector<int>& tup, const int& back, vector<pair<int, int>>& bridges, int time)
    {
        int length = visited.size();
        visited[v] = true;
        tin[v] = tup[v] = time;
        for (const auto& current : graph.adjacency_list({ v }))
        {
            int next = current.index;
            if (next == back)
                continue;
            if (visited[next])         // ��� ���������� ��������� �����
                tup[v] = min(tup[v], tin[next]);
            else
            {
                ++time;
                bridgesDFS(next, visited, tin, tup, v, bridges, time);                   // ����� � ������� ��� ��������� �������
                tup[v] = min(tup[v], tup[next]);                                 // ������� � �������
                if (tup[next] > tin[v])
                {
                    if (find(bridges.begin(), bridges.end(), pair<int, int>{v, next}) == bridges.end() &&
                        find(bridges.begin(), bridges.end(), pair<int, int>{next, v}) == bridges.end())
                        bridges.push_back({ v, next });
                }
            }
        }
    }

	// ����� ��������
	void hingesDFS(const int& v, vector<bool>& visited, vector<int>& tin, vector<int>& tup, const int& back, vector<int>& hinges, int time)
    {
        int length = visited.size();
        visited[v] = true;
        tin[v] = tup[v] = time;
        int children = 0;
        for (const auto& current : graph.adjacency_list({ v }))
        {
            int next = current.index;
            if (next == back)
                continue;
            if (visited[next])                                                             // ��� ���������� ��������� �����
                tup[v] = min(tup[v], tin[next]);
            else
            {
                ++time;
                hingesDFS(next, visited, tin, tup, v, hinges, time);                       // ����� � ������� ��� ��������� �������
                tup[v] = min(tup[v], tup[next]);                                        //������� � �������
                if (tup[next] >= tin[v] && back != -1)
                {
                    if (find(hinges.begin(), hinges.end(), v) == hinges.end()) hinges.push_back(v);
                }
                ++children;
            }
        }
        if (back == -1 && children > 1)      // ���� ��������� ����� ����� ������ �������
        {
            if (find(hinges.begin(), hinges.end(), v) == hinges.end()) hinges.push_back(v);
        }
    }
};

