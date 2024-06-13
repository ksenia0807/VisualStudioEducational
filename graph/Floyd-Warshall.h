#pragma once
#include"Graph.h"	// ��������� ������ Graph

// ����� �����-�������
class Floyd_Warshall
{
private:
	Graph graph;					// ����
	vector<vector<int>> distance;	// ������� ����������

public:

	// �����������
	Floyd_Warshall(Graph graph);

	// ����� ������� ���������� ����������
	vector<vector<int>> find_distance_matrix();

	// ����� �������� ������ ��� ���������
	vector<int> find_degree_vector_for_graph();

	// ����� ������������ ��� �������
	pair<vector<int>, vector<int>> find_degree_vectors_for_orgraph();

	// ����� ����������������
	vector<int> eccentricity();

	// ����� �������� � �������
	pair<int, int> find_diametr_and_radius();

	// ����� ������������ ��������� ������
	set<Vertex> find_cent_vertex();

	// ����� ������������� ��������� ������
	set<Vertex> find_perif_vertex();
};
