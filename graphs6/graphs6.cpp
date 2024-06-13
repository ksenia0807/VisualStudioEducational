#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Algorithms.cpp"		// Заголовок алгоритма

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
	bool chooseAlgorithm = false;	// Флаг выбора алгоритма
	int typeOfAlgorithm = 0;		// Тип алгоритма
	int startVertex;				// Старт
	bool chooseStart = false;		// Флаг выбора старта
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
			cout << "-d : Дейкстра" << endl;
			cout << "-b : Беллман-Форд-Мур" << endl;
			cout << "-t : Левит" << endl;
			cout << "-n : Начальная вершина" << endl;
			cout << "-o : Результат выводится в файл" << endl;
			cout << "-----------------------------------------------------" << endl << endl;
			continue;
		}
		if (id != "-h" && id != "-l" && id != "-e" && id != "-m" && id != "-o" && id != "-d" && id != "-b" && id != "-t" && id != "-n")
		{
			cout << "Такого ключа не существует!" << endl;
			cin.clear();
			continue;
		}
		if (line.eof() && (id == "-o" || id == "-e" || id == "-l" || id == "-m" || id == "-n"))		// Если ничего больше не введено
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
			line >> fileOutName;										// Из буффера записываем имя файла
			if (!line.eof())
			{
				cin.clear();	// Очищаем буффер
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
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
			line >> file_path;		// Из буффера записываем название файла
			if (!line.eof())
			{
				cin.clear();		// Очищаем буффер
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
			if (!chooseStart || !chooseAlgorithm) continue;
			else break;
		}
		if (chooseFile && (id == "-e" || id == "-l" || id == "-m"))
		{
			cout << "Файл уже был выбран!" << endl;
			cin.clear();
			continue;
		}
		if (!chooseAlgorithm && (id == "-d" || id == "-b" || id == "-t"))
		{
			if (!line.eof())
			{
				cin.clear();		// Очищаем буффер
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			if (id == "-d")
			{
				typeOfAlgorithm = 1;
				cout << "Выбран алгоритм Дейкстры!" << endl;
			}
			if (id == "-b")
			{
				typeOfAlgorithm = 2;
				cout << "Выбран алгоритм Беллмана-Форда-Мура!" << endl;
			}
			if (id == "-t")
			{
				typeOfAlgorithm = 3;
				cout << "Выбран алгоритм Левита!" << endl;
			}
			chooseAlgorithm = true;
			if (!chooseFile || !chooseStart) continue;
			else break;
		}
		if (chooseAlgorithm && (id == "-d" || id == "-b" || id == "-t"))
		{
			cout << "Алгоритм уже был выбран!" << endl;
			cin.clear();
			continue;
		}
		if (!chooseStart && id == "-n")
		{
			line >> startVertex;
			if (!line.eof())
			{
				cin.clear();		// Очищаем буффер
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			chooseStart = true;
			if (!chooseFile || !chooseAlgorithm) continue;
			break;
		}
		if (chooseStart && id == "-n")
		{
			cout << "Старт уже был выбран!" << endl;
			cin.clear();
			continue;
		}
	}
	// Приводим номер к индексу
	--startVertex;

	Graph graph(file_path, dataType);	// Граф

	// Ограничения для графа
	bool negativeEdges = hasNegativeEdges(graph.list_of_edges());
	bool negativeCycleZero = hasNegativeZeroCycle(graph.list_of_edges(), graph.countVertex);
	bool negativeCycleNegative = hasNegativeWeightCycle(graph.list_of_edges(), graph.countVertex);
	bool positiveCycle = hasPositiveCycle(graph.list_of_edges(), graph.countVertex);

	if (typeOfAlgorithm == 1)
	{
		if (negativeEdges)
		{
			cout << "В графе присутствует ребро(а) с отрицательным весом, алгоритм может работать некорректно!" << endl;
		}
		if (negativeCycleNegative || negativeCycleZero)
		{
			cout << "В графе присутствуют отрицательный цикл(ы), алгоритм может работать некорректно!" << endl;
		}
	}
	if (typeOfAlgorithm == 2)
	{
		if (positiveCycle)
		{
			cout << "В графе присутствует цикл(ы) с положительным весом, алгоритм может работать некорректно!" << endl;
		}
		if (negativeCycleNegative || negativeCycleZero)
		{
			cout << "В графе присутствуют отрицательный цикл(ы), алгоритм может работать некорректно!" << endl;
		}
	}
	if (typeOfAlgorithm == 3)
	{
		if (negativeCycleNegative)
		{
			cout << "В графе присутствует цикл(ы) отрицательного веса, алгоритм может работать некорректно!" << endl;
		}
		if (negativeCycleZero)
		{
			cout << "В графе присутствуют отрицательный цикл(ы) нулевого веса, алгоритм может работать некорректно!" << endl;
		}
	}

	vector<int> distance;				// Вектор расстояний
	Dijkstra dijkstra (graph);			// Алгоритм Дейкстры
	BellmanFord bfm (graph);				// Алгоритм Беллмана-Форда-Мура
	Levit levit (graph);					// Алгоритм Левита

	bool negCycle = false;				// Флаг обнаружения алгоритмом отрицательного цикла

	// Выбор алгоритма
	switch (typeOfAlgorithm)
	{
	case 1:	// Дейкстра
		distance = dijkstra.DijkstraShortestPath(startVertex);
		if (outFileFlag)	// Файл
		{
			fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
			fileOut << "Длины кратчайших путей:" << endl;
			for (int i = 0; i < distance.size(); ++i)
			{
				fileOut << startVertex + 1 << " - " << i + 1 << ": ";
				if (distance[i] == INF) fileOut << "Нет пути между вершинами!" << endl;
				else fileOut << distance[i] << endl;
			}
			fileOut.close();
		}
		else   // Консоль
		{
			cout << "Длины кратчайших путей:" << endl;
			for (int i = 0; i < distance.size(); ++i)
			{
				cout << startVertex + 1 << " - " << i + 1 << ": ";
				if (distance[i] == INF) cout << "Нет пути между вершинами!" << endl;
				else cout << distance[i] << endl;
			}
		}
		return 0;

	case 2:	// Беллман-Форд-Мур
		distance = bfm.BellmanFordMoore(startVertex, negCycle);
		if (outFileFlag)	// Файл
		{
			if (negCycle)
			{
				fileOut << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
			}
			else
			{
				fileOut.open(fileOutName, std::ofstream::out | std::ofstream::trunc);	// Открываем файл для записи
				fileOut << "Длины кратчайших путей:" << endl;
				for (int i = 0; i < distance.size(); ++i)
				{
					fileOut << startVertex + 1 << " - " << i + 1 << ": ";
					if (distance[i] == INF) fileOut << "Нет пути между вершинами!" << endl;
					else fileOut << distance[i] << endl;
				}
			}
			fileOut.close();
		}
		else   // Консоль
		{
			if (negCycle)
			{
				cout << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
			}
			else
			{
				cout << "Длины кратчайших путей:" << endl;
				for (int i = 0; i < distance.size(); ++i)
				{
					cout << startVertex + 1 << " - " << i + 1 << ": ";
					if (distance[i] == INF) cout << "Нет пути между вершинами!" << endl;
					else cout << distance[i] << endl;
				}
			}
		}
		return 0;

	case 3:	// Левит
		distance = levit.levit(startVertex, negCycle);
		if (outFileFlag)	// Файл
		{
			if (negCycle)
			{
				fileOut << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
			}
			else
			{
				fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
				fileOut << "Длины кратчайших путей:" << endl;
				for (int i = 0; i < distance.size(); ++i)
				{
					fileOut << startVertex + 1 << " - " << i + 1 << ": ";
					if (distance[i] == INF) fileOut << "Нет пути между вершинами!" << endl;
					else fileOut << distance[i] << endl;
				}
			}
			fileOut.close();
		}
		else   // Консоль
		{
			if (negCycle)
			{
				cout << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
			}
			else
			{
				cout << "Длины кратчайших путей:" << endl;
				for (int i = 0; i < distance.size(); ++i)
				{
					cout << startVertex + 1 << " - " << i + 1 << ": ";
					if (distance[i] == INF) cout << "Нет пути между вершинами!" << endl;
					else cout << distance[i] << endl;
				}
			}
		}
		return 0;
	}

}