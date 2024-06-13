#pragma once
#include"Graph.h"	// Заголовок класса Graph

// Класс Флойд-Уоршелл
class Floyd_Warshall
{
private:
	Graph graph;					// Граф
	vector<vector<int>> distance;	// Матрица расстояний

public:

	// Конструктор
	Floyd_Warshall(Graph graph);

	// Поиск матрицы кратчайших расстояний
	vector<vector<int>> find_distance_matrix();

	// Поиск степеней вершин для неорграфа
	vector<int> find_degree_vector_for_graph();

	// Поиск полустепеней для орграфа
	pair<vector<int>, vector<int>> find_degree_vectors_for_orgraph();

	// Поиск эксцентриситетов
	vector<int> eccentricity();

	// Поиск диаметра и радиуса
	pair<int, int> find_diametr_and_radius();

	// Поиск центрального множества вершин
	set<Vertex> find_cent_vertex();

	// Поиск периферийного множества вершин
	set<Vertex> find_perif_vertex();
};
