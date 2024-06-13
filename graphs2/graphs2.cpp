#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "BFS.cpp"		// Заголовок алгоритма

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
	BFS algor (graph);					// Алгоритм

	if (outFileFlag)	// Запись в файл
	{
		// Открываем файл с очисткой
		fileOut.open(fileOutName, ofstream::out | ofstream::trunc);
		if (!graph.isDirected)		// Если неорграф
		{
			vector<bool> visited(graph.countVertex, false);		// Вектор посещения
			vector<vector<int>> components;						// Компоненты
			// Пока есть непосещенные вершины
			while (find(visited.begin(), visited.end(), false) != visited.end())
			{
				int numberNotVisited = 0;					// Номер непосещенной вершины
				for (int i = 0; i < visited.size(); ++i)	// Поиск непосещенной вершины
				{
					if (visited[i] == false)
					{
						numberNotVisited = i;
						break;
					}
				}
				components.push_back(algor.bfs(visited, numberNotVisited));		// Поиском в ширину получаем компоненту связности
			}
			if (components.size() == 1) fileOut << "Граф связен" << endl;		// Если кол-во компонент - 1 => граф связен
			else fileOut << "Граф не связен и содержит " << components.size() << " компонент связности:" << endl;
			for (const auto& component : components)
			{
				for (const auto& cur : component)
				{
					fileOut << cur + 1 << " ";
				}
				fileOut << endl;
			}
		}
		else   // Орграф
		{
			// Создаём соотнесенную матрицу
			vector<vector<int>> correlatedMatrix(graph.countVertex, vector<int>(graph.countVertex, 0));
			for (int i = 0; i < graph.countVertex; ++i)
			{
				for (int j = 0; j < graph.countVertex; ++j)
				{
					if (graph.adjacency_matrix()[i][j] == 0)
					{
						correlatedMatrix[i][j] = graph.adjacency_matrix()[j][i];
					}
					else {
						correlatedMatrix[i][j] = graph.adjacency_matrix()[i][j];
					}
				}
			}
			// Соотнесенный граф
			Graph correlatedGraph(correlatedMatrix);			// Соотнесенный граф
			BFS correlatedAlgor (correlatedGraph);				// Алгоритм

			vector<bool> visited(graph.countVertex, false);		// Вектор посещения
			vector<vector<int>> correlatedComponents;			// Компоненты связности

			// BFS для соотнесенного графа
			while (find(visited.begin(), visited.end(), false) != visited.end())
			{
				int numberNotVisited = 0;
				for (int i = 0; i < visited.size(); ++i)
				{
					if (visited[i] == false)
					{
						numberNotVisited = i;
						break;
					}
				}
				correlatedComponents.push_back(correlatedAlgor.bfs(visited, numberNotVisited));
			}

			vector<set<int>> components;									// Компоненты сильной связности
			for (int i = 0; i < graph.countVertex; ++i)
			{
				visited = vector<bool>(graph.countVertex, false);			// Обнуляем вектор посещения
				vector<int> possibleStrongComponent = algor.bfs(visited, i);// Ищем возможную компоненту сильной связности
				set<int> strongComponent;									// В этом множество будут вершины, которые точно принадлежат сильной компоненте
				strongComponent.insert(i);
				for (int j = 0; j < graph.countVertex; j++)
				{
					vector<bool> inverseVisited(graph.countVertex, false);	// Вектор посещаемости из всех достигнутых ранее вершин
					vector<int> inverseComponent;							// Вспомогательная компонента для проверки возможности достигнуть вершину из посещенных
					if (visited[j] && j != i)		// Если посещена
					{
						inverseComponent = algor.bfs(inverseVisited, j);
						// Если начальная вершина достижима из текущей - включаем в компоненту
						if (find(inverseComponent.begin(), inverseComponent.end(), i) != inverseComponent.end())
							strongComponent.insert(j);
					}
				}
				// Если такой компоненты еще нет - включаем в компоненты сильной связности
				if (find(components.begin(), components.end(), strongComponent) == components.end())
					components.push_back(strongComponent);
			}

			if (correlatedComponents.size() == 1)
			{
				fileOut << "Орграф связен" << endl;
				for (const auto& cur : correlatedComponents[0])
				{
					fileOut << cur + 1 << " ";
				}
				fileOut << endl;

			}
			else fileOut << "Орграф не связен" << endl;
			if (components.size() == 1) fileOut << "Орграф сильно связен, компонента сильной связности:" << endl;
			else fileOut << "Орграф слабо связен и содержит " << components.size() << " компонент связности:" << endl;
			for (const auto& comp : components)
			{
				for (const auto& cur : comp)
				{
					fileOut << cur + 1 << " ";
				}
				fileOut << endl;
			}

		}
		fileOut.close();
		return 0;
	}
	else
	{
		if (!graph.isDirected)
		{
			vector<bool> visited(graph.countVertex, false);
			vector<vector<int>> components;
			while (find(visited.begin(), visited.end(), false) != visited.end())
			{
				int numberNotVisited = 0;
				for (int i = 0; i < visited.size(); ++i)
				{
					if (visited[i] == false)
					{
						numberNotVisited = i;
						break;
					}
				}
				components.push_back(algor.bfs(visited, numberNotVisited));
			}
			if (components.size() == 1) cout << "Граф связен" << endl;
			else cout << "Граф не связен и содержит " << components.size() << " компонент связности:" << endl;
			for (const auto& component : components)
			{
				for (const auto& cur : component)
				{
					cout << cur + 1 << " ";
				}
				cout << endl;
			}
		}
		else
		{
			// Создаём соотнесенную матрицу
			vector<vector<int>> correlatedMatrix(graph.countVertex, vector<int>(graph.countVertex, 0));
			for (int i = 0; i < graph.countVertex; ++i)
			{
				for (int j = 0; j < graph.countVertex; ++j)
				{
					if (graph.adjacency_matrix()[i][j] == 0)
					{
						correlatedMatrix[i][j] = graph.adjacency_matrix()[j][i];
					}
					else {
						correlatedMatrix[i][j] = graph.adjacency_matrix()[i][j];
					}
				}
			}
			// Соотнесенный граф
			Graph correlatedGraph(correlatedMatrix);
			BFS correlatedAlgor (correlatedGraph);				// Алгоритм

			vector<bool> visited(graph.countVertex, false);		// Вектор посещения
			vector<vector<int>> correlatedComponents;			// Компоненты связности

			// BFS для соотнесенного графа
			while (find(visited.begin(), visited.end(), false) != visited.end())
			{
				int numberNotVisited = 0;
				for (int i = 0; i < visited.size(); ++i)
				{
					if (visited[i] == false)
					{
						numberNotVisited = i;
						break;
					}
				}
				correlatedComponents.push_back(correlatedAlgor.bfs(visited, numberNotVisited));
			}

			vector<set<int>> components;									// Компоненты сильной связности
			for (int i = 0; i < graph.countVertex; ++i)
			{
				visited = vector<bool>(graph.countVertex, false);			// Обнуляем вектор посещения
				vector<int> possibleStrongComponent = algor.bfs(visited, i);// Ищем возможную компоненту сильной связности
				set<int> strongComponent;									// В этом множество будут вершины, которые точно принадлежат сильной компоненте
				strongComponent.insert(i);
				for (int j = 0; j < graph.countVertex; j++)
				{
					vector<bool> inverseVisited(graph.countVertex, false);	// Вектор посещаемости из всех достигнутых ранее вершин
					vector<int> inverseComponent;							// Вспомогательная компонента для проверки возможности достигнуть вершину из посещенных
					if (visited[j] && j != i)		// Если посещена и не проверяемая вершина
					{
						inverseComponent = algor.bfs(inverseVisited, j);
						// Если начальная вершина достижима из текущей - включаем в компоненту
						if (find(inverseComponent.begin(), inverseComponent.end(), i) != inverseComponent.end())
							strongComponent.insert(j);
					}
				}
				// Если такой компоненты еще нет - включаем в компоненты сильной связности
				if (find(components.begin(), components.end(), strongComponent) == components.end())
					components.push_back(strongComponent);
			}

			if (correlatedComponents.size() == 1)
			{
				cout << "Орграф связен" << endl;
				for (const auto& cur : correlatedComponents[0])
				{
					cout << cur + 1 << " ";
				}
				cout << endl;

			}
			else cout << "Орграф не связен" << endl;
			if (components.size() == 1) cout << "Орграф сильно связен, компонента сильной связности:" << endl;
			else cout << "Орграф слабо связен и содержит " << components.size() << " компонент связности:" << endl;
			for (const auto& comp : components)
			{
				for (const auto& cur : comp)
				{
					cout << cur + 1 << " ";
				}
				cout << endl;
			}

		}
		return 0;
	}
}