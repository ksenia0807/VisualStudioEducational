#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "DFS.cpp"		// Заголовок алгоритма

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
Graph graphForCheck(file_path, dataType);	// Создаём граф

// Создаем матрицу
vector<vector<int>> matrix(graphForCheck.countVertex, vector<int>(graphForCheck.countVertex, 0));
if (graphForCheck.isDirected)	// Если граф ориентированный - создаём соотнесенный граф
{
	for (int i = 0; i < graphForCheck.countVertex; ++i)
	{
		for (int j = 0; j < graphForCheck.countVertex; ++j)
		{
			if (graphForCheck.adjacency_matrix()[i][j] == 0)
			{
				matrix[i][j] = graphForCheck.adjacency_matrix()[j][i];
			}
			else {
				matrix[i][j] = graphForCheck.adjacency_matrix()[i][j];
			}
		}
	}
}
else matrix = graphForCheck.adjacency_matrix();
Graph graph(matrix);	// Граф для поиска мостов и шарниров
DFS algor(graph);		// Алгоритм
vector<int> hinges;		// Шарниры
vector<pair<int, int>> bridges;	// Мосты

vector<bool> visited(graph.countVertex, false);	// Вектор посещения

// Вспомогательные векторы
vector<int> tin(graph.countVertex, 0);
vector<int> tup(graph.countVertex, 0);

// Поиск мостов
for (int i = 0; i < graph.countVertex; ++i)
{
	if (!visited[i]) algor.bridgesDFS(i, visited, tin, tup, i - 1, bridges, 0);
}

// Обнуление векторов
fill(visited.begin(), visited.end(), false);
fill(tin.begin(), tin.end(), 0);
fill(tup.begin(), tup.end(), 0);

// Поиск шарниров
for (int i = 0; i < graph.countVertex; ++i)
{
	if (!visited[i]) algor.hingesDFS(i, visited, tin, tup, i - 1, hinges, 0);
}

if (outFileFlag)	// Запись в файл
{
	fileOut.open(fileOutName, ofstream::out | ofstream::trunc);
	fileOut << "Шарниры:" << endl;
	for (const auto& hinge : hinges)
	{
		fileOut << hinge + 1 << " ";
	}
	fileOut << endl;
	fileOut << "Мосты:" << endl;
	for (const auto& bridge : bridges)
	{
		fileOut << "(" << bridge.first + 1 << "-" << bridge.second + 1 << ")" << endl;
	}
	fileOut.close();
	return 0;
}
else   // В консоль
{
	cout << "Шарниры:" << endl;
	for (const auto& hinge : hinges)
	{
		cout << hinge + 1 << " ";
	}
	cout << endl;
	cout << "Мосты:" << endl;
	for (const auto& bridge : bridges)
	{
		cout << "(" << bridge.first + 1 << "-" << bridge.second + 1 << ")" << endl;
	}
	return 0;
}
}
