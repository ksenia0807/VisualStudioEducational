#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Ford-Fulkerson.cpp"		// Заголовок алгоритма

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
	FordFulkerson FF (graph);


	int source = -1;		// Исток
	int sink = -1;			// Сток

	pair<int, int> ss(source, sink);

	ss = FF.findSourceSink();	// Ищем исток и сток

	if (ss.first == -1 || ss.second == -1)
	{
		if (outFileFlag)
		{
			fileOut.open(fileOutName, std::ofstream::out | std::ofstream::trunc);	// Открываем файл для записи
			fileOut << "В графе нет истока или стока!" << endl;
			fileOut.close();
			return 0;
		}
		else
		{
			cout << "В графе нет истока или стока!" << endl;
			return 0;
		}
	}

	pair<vector<Edge>, int> res(vector<Edge>(), 0);

	// Ищем максимальный поток и получаем список рёбер с их потоками
	res = FF.fordFulkerson(ss.first, ss.second);

	if (outFileFlag)
	{
		fileOut.open(fileOutName, std::ofstream::out | std::ofstream::trunc);	// Открываем файл для записи
		fileOut << res.second << " - максимальный поток из " << ss.first + 1 << " в " << ss.second + 1 << endl;
		// Выводим список ребер с величиной потока через каждое ребро
		for (const auto& edge : res.first) {
			fileOut << edge.start.index + 1 << " -> " << edge.end.index + 1 << ": " << edge.flow << "/" << edge.weight << endl;
		}
		fileOut.close();
		return 0;
	}
	else
	{
		cout << res.second << " - максимальный поток из " << ss.first + 1 << " в " << ss.second + 1 << endl;
		// Выводим список ребер с величиной потока через каждое ребро
		for (const auto& edge : res.first) {
			cout << edge.start.index + 1 << " -> " << edge.end.index + 1 << ": " << edge.flow << "/" << edge.weight << endl;
		}
		return 0;
	}

}