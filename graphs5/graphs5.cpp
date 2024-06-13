#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Dijkstra.cpp"		// Заголовок алгоритма

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
	int startVertex = 0;			// Старт
	int endVertex = 0;				// Финиш
	bool chooseStart = false;		// Флаг выбора старта
	bool chooseEnd = false;			// Флаг выбора финиша
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
			cout << "-n : Начальная вершина" << endl;
			cout << "-d : Конечная вершина" << endl;
			cout << "-o : Результат выводится в файл" << endl;
			cout << "-----------------------------------------------------" << endl << endl;
			continue;
		}
		if (id != "-h" && id != "-l" && id != "-e" && id != "-m" && id != "-o" && id != "-n" && id != "-d")
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
			if (!chooseStart || !chooseEnd) continue;
			break;
		}
		if (chooseFile && (id == "-e" || id == "-l" || id == "-m"))
		{
			cout << "Файл уже был выбран!" << endl;
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
			if (!chooseFile || !chooseEnd)	continue;
			break;
		}
		if (chooseStart && id == "-n")
		{
			cout << "Старт уже был выбран!" << endl;
			continue;
		}
		if (!chooseEnd && id == "-d")
		{
			line >> endVertex;
			if (!line.eof())
			{
				cin.clear();		// Очищаем буффер
				cout << "В 1 запросе нельзя указывать несколько ключей!" << endl;
				continue;
			}
			chooseEnd = true;
			if (!chooseFile || !chooseStart) continue;
			break;
		}
		if (chooseEnd && id == "-d")
		{
			cout << "Финиш уже был выбран!" << endl;
			cin.clear();		// Очищаем буффер
			continue;
		}
	}

	// В моей проге номера приводятся к индексам для удобства
	--startVertex;
	--endVertex;

	Graph graph(file_path, dataType);	// Создаём граф
	Dijkstra dijkstra (graph);			// Алгоритм

	// Ищем путь и расстояние
	pair<vector<Edge>, int> path_destination = dijkstra.DijkstraShortestPath(startVertex, endVertex);

	if (outFileFlag)	// Файл
	{
		fileOut.open(fileOutName, std::ofstream::out | std::ofstream::trunc);	// Открываем файл для записи
		if (path_destination.first.size() == 0)
		{
			fileOut << "Нет пути между вершинами!" << endl;
		}
		else
		{
			fileOut << "Кратчайший путь: " << endl;
			for (const auto& edge : path_destination.first) {
				fileOut << "(" << edge.start.index + 1 << " - " << edge.end.index + 1 << ")\t" << edge.weight << endl;
			}
			fileOut << endl;
			fileOut << "Длина пути: " << path_destination.second << endl;
		}
		fileOut.close();
		return 0;
	}
	else  // Консоль
	{
		if (path_destination.first.size() == 0)
		{
			cout << "Нет пути между вершинами!" << endl;
		}
		else
		{
			cout << "Кратчайший путь: " << endl;
			for (const auto& edge : path_destination.first) {
				cout << "(" << edge.start.index + 1 << " - " << edge.end.index + 1 << ")\t" << edge.weight << endl;
			}
			cout << endl;
			cout << "Длина пути: " << path_destination.second << endl;
		}
		return 0;
	}
}