#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Floyd-Warshall.h"		// Заголовок алгоритма

int main() {
	const char* file = NULL;		// Файл
	string key;						// Ключ
	string id;						// Выбранный тип
	string dataType;				// Вводные данные
	ifstream fileIn;				// Файл для записи
	string file_path;				// Название файла для ввода
	bool chooseFile = false;		// Флаг выбора файла
	bool outFileFlag = false;		// Флаг вывода в файл
	string fileOutName;				// Название файла для вывода
	ofstream fileOut;				// Файл для записи
	setlocale(LC_ALL, "ru");		// Русский язык
	while (true)
	{
		cout << "Введите ключ: ";
		getline(cin, key);		// Получаем строку из консоли
		stringstream line(key);	// Объект для обработки строки
		line >> id;				// Вводим первое слово в строке
		if (id == "-h")	// Справка
		{
			cout << "-----------------------Справка------------------------" << endl;
			cout << "Работу выполнила студентка М3О-211Б-21 Денисенко София" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << "-h : Справка" << endl;
			cout << "-l : Список смежности" << endl;
			cout << "-e : Список рёбер" << endl;
			cout << "-m : Матрица смежности" << endl;
			cout << "-o : Результат выводится в файл" << endl;
			cout << "-----------------------------------------------------" << endl << endl;
			continue;
		}
		if (id != "-h" && id != "-l" && id != "-e" && id != "-m" && id != "-o")
		{
			cout << "Такого ключа не существует!" << endl;
			cin.clear();
			continue;
		}
		if (line.eof())		// Если ничего больше не введено
		{
			cout << "Неправильный формат ключа!" << endl;
			cin.clear();
			continue;
		}
		if (id == "-o" && outFileFlag)
		{
			cout << "Файл для записи уже был выбран!" << endl;
			cin.clear();
			continue;
		}
		if (id == "-o")	// Файл
		{
			line >> fileOutName;										// Записываем имя файла
			if (!line.eof())
			{
				cin.clear();
				cout << "В одном запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			ifstream checkFile(fileOutName);
			if (checkFile.fail())											// Если файла нет
			{
				cout << "Файла с таким названием не существует!" << endl;
				fileOutName.clear();
				checkFile.close();
				continue;
			}
			checkFile.close();
			outFileFlag = true;				// Флаг записи в файл
			cout << "Результат будет выведен в файл!" << endl;
			continue;
		}
		if (!chooseFile && (id == "-e" || id == "-l" || id == "-m"))
		{
			line >> file_path;		// Записываем название файла
			if (!line.eof())
			{
				cin.clear();
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			fileIn.open(file_path);
			if (fileIn.fail())		// Если файла нет
			{
				cout << "Файла с таким названием не существует!" << endl;
				file_path.clear();
				fileIn.close();
				continue;
			}
			fileIn.close();
			dataType = id;
			chooseFile = true;
			break;
		}
		if (chooseFile && (id == "-e" || id == "-l" || id == "-m"))
		{
			cout << "Файл уже был выбран!" << endl;
			cin.clear();
			continue;
		}
	}

	Graph graph(file_path, dataType);	// Создаём граф
	Floyd_Warshall algor(graph);		// Алгоритм

	// Матрица расстояний
	vector<vector<int>> dist = algor.find_distance_matrix();

	if (outFileFlag)	// Вывод в файл
	{
		// Открываем файл с очисткой
		fileOut.open(fileOutName, ofstream::out | ofstream::trunc);
		if (graph.isDirected)	// Если орграф
		{
			// Векторы полустепеней
			pair<vector<int>, vector<int>> degrees = algor.find_degree_vectors_for_orgraph();
			fileOut << "deg+ : ";
			for (const auto& current : degrees.first)
			{
				fileOut << current << " ";
			}
			fileOut << endl;
			fileOut << "deg- : ";
			for (const auto& current : degrees.second)
			{
				fileOut << current << " ";
			}
			fileOut << endl;
		}
		else  // Неорграф
		{
			// Вектор степеней
			vector<int> degrees = algor.find_degree_vector_for_graph();
			fileOut << "deg = ";
			for (const auto& current : degrees)
			{
				fileOut << current << " ";
			}
			fileOut << endl;
		}
		// Матрица расстояний
		fileOut << "Destancies:" << endl;
		for (const auto& current : dist)
		{
			for (const auto& col : current)
			{
				if (col == INF)
					fileOut << "INF" << "\t";
				else fileOut << col << "\t";
			}
			fileOut << endl;
		}

		// Вектор эксцентриситетов
		vector<int> ecc = algor.eccentricity();
		fileOut << "Eccentricity: ";
		for (const auto& e : ecc) {
			fileOut << e << " ";
		}
		fileOut << endl;

		// Пара из диаметра и радиуса
		pair<int, int> DR = algor.find_diametr_and_radius();
		fileOut << "D = ";
		if (DR.first == INF) fileOut << "INF" << endl;
		else fileOut << DR.first << endl;
		fileOut << "R = ";
		if (DR.second == INF) fileOut << "INF" << endl;
		else fileOut << DR.second << endl;

		if (!graph.isDirected)	// Если орграф
		{
			// Множество центральных вершин
			fileOut << "Z : ";
			set<Vertex> Z = algor.find_cent_vertex();
			for (const auto& vertex : Z)
			{
				fileOut << vertex.index << " ";
			}
			fileOut << endl;

			// Множество периферийных вершин
			fileOut << "P : ";
			set<Vertex> P = algor.find_perif_vertex();
			for (const auto& vertex : P)
			{
				fileOut << vertex.index << " ";
			}
			fileOut << endl;
		}
		fileOut.close();
	}
	else   // В консоль
	{
		if (graph.isDirected)	// Орграф
		{
			// Векторы полустепеней
			pair<vector<int>, vector<int>> degrees = algor.find_degree_vectors_for_orgraph();
			cout << "deg+ : ";
			for (const auto& current : degrees.first)
			{
				cout << current << " ";
			}
			cout << endl;
			cout << "deg- : ";
			for (const auto& current : degrees.second)
			{
				cout << current << " ";
			}
			cout << endl;
		}
		else   // Неорграф
		{
			// Вектор степеней
			vector<int> degrees = algor.find_degree_vector_for_graph();
			cout << "deg = ";
			for (const auto& current : degrees)
			{
				cout << current << " ";
			}
			cout << endl;
		}

		// Матрица расстояний
		cout << "Destancies:" << endl;
		for (const auto& current : dist)
		{
			for (const auto& col : current)
			{
				if (col == INF)
					cout << "INF" << "\t";
				else cout << col << "\t";
			}
			cout << endl;
		}

		// Вектор эксцентриситетов
		vector<int> ecc = algor.eccentricity();
		cout << "Eccentricity: ";
		for (const auto& e : ecc) {
			cout << e << " ";
		}
		cout << endl;

		// Пара из диаметра и радиуса
		pair<int, int> DR = algor.find_diametr_and_radius();
		cout << "D = ";
		if (DR.first == INF) cout << "INF" << endl;
		else cout << DR.first << endl;
		cout << "R = ";
		if (DR.second == INF) cout << "INF" << endl;
		else cout << DR.second << endl;

		if (!graph.isDirected)	// Если неорграф
		{
			// Множество центральных вершин
			cout << "Z : ";
			set<Vertex> Z = algor.find_cent_vertex();
			for (const auto& vertex : Z)
			{
				cout << vertex.index << " ";
			}
			cout << endl;

			// Множество периферийных вершин
			cout << "P : ";
			set<Vertex> P = algor.find_perif_vertex();
			for (const auto& vertex : P)
			{
				cout << vertex.index << " ";
			}
			cout << endl;
		}
	}


}