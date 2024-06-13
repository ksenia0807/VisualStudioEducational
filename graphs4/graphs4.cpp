#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Algorithms.cpp"		// Заголовок алгоритма

// Итоговый вес остовного дерева
int sumWeight(const vector<Edge>& edges)
{
	int weight = 0;
	for (const auto& cur : edges)
	{
		weight += cur.weight;
	}
	return weight;
}


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
			cout << "-k : Крускал" << endl;
			cout << "-p : Прим" << endl;
			cout << "-b : Борувка" << endl;
			cout << "-s : Три алгоритма поочерёдно" << endl;
			cout << "-o : Результат выводится в файл" << endl;
			cout << "-----------------------------------------------------" << endl << endl;
			continue;
		}
		if (id != "-h" && id != "-l" && id != "-e" && id != "-m" && id != "-o" && id != "-k" && id != "-p" && id != "-b" && id != "-s")
		{
			cout << "Такого ключа не существует!" << endl;
			cin.clear();
			continue;
		}
		if ((id == "-o" || id == "-l" || id == "-e" || id == "-m") && line.eof())		// Если ничего больше не введено
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
			if (!chooseAlgorithm) continue;
			break;
		}
		if (chooseFile && (id == "-e" || id == "-l" || id == "-m"))
		{
			cout << "Файл уже был выбран!" << endl;
			cin.clear();
			continue;
		}
		if (!chooseAlgorithm && (id == "-k" || id == "-p" || id == "-b" || id == "-s"))
		{
			if (!line.eof())
			{
				cin.clear();	// Очищаем буффер
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			if (id == "-k")
			{
				typeOfAlgorithm = 1;
				cout << "Выбран алгоритм Крускала!" << endl;
			}
			if (id == "-p")
			{
				typeOfAlgorithm = 2;
				cout << "Выбран алгоритм Прима!" << endl;
			}
			if (id == "-b")
			{
				typeOfAlgorithm = 3;
				cout << "Выбран алгоритм Борувки!" << endl;
			}
			if (id == "-s")
			{
				typeOfAlgorithm = 4;
				cout << "Выбраны все алгоритмы!" << endl;
			}
			chooseAlgorithm = true;
			if (!chooseFile)
			{
				continue;
			}
			else break;
		}
		if (chooseAlgorithm && (key == "-k" || key == "-p" || key == "-b" || key == "-s"))
		{
			cout << "Алгоритм уже был выбран!" << endl;
			cin.clear();
			continue;
		}
	}

	Graph graphForCheck(file_path, dataType);	// Создаём граф
	// Создаем матрицу
	vector<vector<int>> matrix(graphForCheck.countVertex, vector<int>(graphForCheck.countVertex, 0));
	if (graphForCheck.isDirected)	// Если граф ориентированный - создаём соотнесенный граф
	{
		for (int i = 0; i < graphForCheck.countVertex; ++i)
		{
			for (int j = 0; j < graphForCheck.countVertex; ++j)
			{
				if (graphForCheck.adjacencyMatrix[i][j] != 0)
				{
					matrix[i][j] = graphForCheck.adjacencyMatrix[i][j];
					matrix[j][i] = graphForCheck.adjacencyMatrix[i][j];
				}
				if (graphForCheck.adjacencyMatrix[j][i] != 0)
				{
					matrix[i][j] = graphForCheck.adjacencyMatrix[j][i];
					matrix[j][i] = graphForCheck.adjacencyMatrix[j][i];
				}
			}
		}
	}
	else matrix = graphForCheck.adjacency_matrix();

	Graph graph(matrix);	// Граф

	vector<Edge> mst;		// Минимальное остовное дерево
	Kruskal kruskal (graph);	// Алгоритм Крускала
	Prim prim (graph);		// Алгоритм Прима
	Boruvka boruvka (graph);	// Алгоритм Борувки

	// Счётчик времени
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();

	// Выбор алгоритма
	switch (typeOfAlgorithm)
	{
	case 1:	// Крускал
		mst = kruskal.kruskalMST();
		if (outFileFlag)	// Файл
		{
			fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
			fileOut << "Kruskal:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut.close();
		}
		else   // Консоль
		{
			cout << "Kruskal:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
		}
		return 0;

	case 2:	// Прим
		mst = prim.primMST();
		if (outFileFlag)	// Файл
		{
			fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
			fileOut << "Prim:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut.close();
		}
		else   // Консоль
		{
			cout << "Prim:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
		}
		return 0;

	case 3:	// Борувка
		mst = boruvka.boruvkaMST();
		if (outFileFlag)	// Файл
		{
			fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
			fileOut << "Boruvka:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut.close();
		}
		else // Консоль
		{
			cout << "Boruvka:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		return 0;

	case 4:
		start = chrono::steady_clock::now();
		mst = kruskal.kruskalMST();
		end = chrono::steady_clock::now();
		if (outFileFlag)
		{
			fileOut.open(fileOutName, ofstream::out | ofstream::trunc);	// Открываем файл для записи
			fileOut << "Kruskal:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			fileOut << "-----------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "Kruskal:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
			cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		start = chrono::steady_clock::now();
		mst = prim.primMST();
		end = chrono::steady_clock::now();
		if (outFileFlag)
		{
			fileOut << "Prim:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			fileOut << "-----------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "Prim:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
			cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		start = chrono::steady_clock::now();
		mst = boruvka.boruvkaMST();
		end = chrono::steady_clock::now();
		if (outFileFlag)
		{
			fileOut << "Boruvka:" << endl;
			for (const auto& edge : mst)
			{
				fileOut << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			fileOut << "Weight: " << sumWeight(mst) << endl;
			fileOut << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			fileOut << "-----------------------------------------------------------------" << endl;
			fileOut.close();
		}
		else
		{
			cout << "Boruvka:" << endl;
			for (const auto& edge : mst)
			{
				cout << "(" << edge.start.index + 1 << "-" << (edge.end.index + 1) << ")\t" << edge.weight << endl;
			}
			cout << "Weight: " << sumWeight(mst) << endl;
			cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		return 0;
	}

}