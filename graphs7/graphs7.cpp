#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Johnson.cpp"		// Заголовок алгоритма

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

	// Создаем матрицу, подогнанную под алгоритм Джонсона
	vector<vector<int>> matrix(graph.countVertex, vector<int>(graph.countVertex, INF));
	for (int i = 0; i < graph.countVertex; ++i)
	{
		for (int j = 0; j < graph.countVertex; ++j)
		{
			if (graph.adjacencyMatrix[i][j] != 0) matrix[i][j] = graph.adjacencyMatrix[i][j];
		}
		matrix[i][i] = 0;
	}

	vector<vector<int>> distance;				// Матрица расстояний
	Johnson johnson (matrix);					// Алгоритм Джонсона
	bool negCycle = false;						// Флаг отрицательного цикла

	distance = johnson.johnson(negCycle);
	if (outFileFlag)
	{
		if (negCycle)
		{
			fileOut << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
		}
		else
		{
			fileOut.open(fileOutName, std::ofstream::out | std::ofstream::trunc);	// Открываем файл для записи
			if (hasNegativeEdges(graph.list_of_edges())) fileOut << "В графе есть отрицательные рёбра!" << endl;
			else fileOut << "В графе нет отрицательных рёбер!" << endl;
			fileOut << "Длины кратчайших путей:" << endl;
			for (int i = 0; i < distance.size(); ++i)
			{
				for (int j = 0; j < distance.size(); ++j)
				{
					if (distance[i][j] != INF && i != j) {
						fileOut << i + 1 << " - " << j + 1 << ": " << distance[i][j] << endl;
					}
				}
			}
		}
		fileOut.close();
	}
	else
	{
		if (negCycle)
		{
			cout << "Алгоритм обнаружил, что в графе присутствует отрицательный цикл!" << endl;
		}
		else
		{
			if (hasNegativeEdges(graph.list_of_edges())) cout << "В графе есть отрицательные рёбра!" << endl;
			else cout << "В графе нет отрицательных рёбер!" << endl;
			cout << "Длины кратчайших путей:" << endl;
			for (int i = 0; i < distance.size(); ++i)
			{
				for (int j = 0; j < distance.size(); ++j)
				{
					if (distance[i][j] != INF && i != j) {
						cout << i + 1 << " - " << j + 1 << ": " << distance[i][j] << endl;
					}
				}
			}
		}
	}
	return 0;
}