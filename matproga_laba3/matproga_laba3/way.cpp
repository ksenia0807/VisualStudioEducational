#include <iostream>
#include <iomanip>
using namespace std;
const int N = 4;
void NorthWestAngle();
void MinElem();
void AllSolutionSearchFunc();

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int choice = 0;
	cout << "Введите номер метода: \n1) Метод северо-западного угла;\n";
	cout << "2) Метод минимального элемента;\n";
	cout << "3) Вырожденная транспортная задача;\n";
	cin >> choice;

	switch (choice)
	{
		case 1:
		{
			NorthWestAngle();
			break;
		}
		case 2:
		{
			MinElem();
			break;
		}
		case 3:
		{
			AllSolutionSearchFunc();
			break;
		}
	}

	system("pause");
	return 0;
}

//Метод северо-западного угла
void NorthWestAngle()
{
	int PointDep[4] = { 60, 125, 40, 35 }; //Пункт отправления
	int PointDes[4] = { 85, 105, 30, 40 }; //Пункт назначения  30-найденное значение
	int Cost[4][4] = { {12, 3, 7, 10}, {3, 8, 15, 6}, {5, 2, 3, 12}, {9, 14, 8, 1} }; //Матрица транспортных тарифов
	//Матрица транспортных тарифов
	int i, j = 0; //Счетчики
	int m = 4; //Количество пунктов отправления
	int n = 4; //Количество пунктов назначения
	int count = 0; //количество итераций
	int check = 0;
	int Sum[4][4] = { 0 }; //Стоимость перевозки
	int TotalCost = 0;
	cout << "\t\tМетод северо-западного угла\n" << endl;
	cout << "\t\tВывод заданной матрицы\n" << endl;
	cout << setw(17) << PointDes[0] << setw(15) << PointDes[1] << setw(15) << PointDes[2]
		<< setw(15) << PointDes[3] << endl;

	for (i = 0; i < 4; i++)
	{
		if (PointDep[i] >= 100)
			cout << PointDep[i] << setw(14);
		if (PointDep[i] < 100 && PointDep[i] >= 10)
			cout << PointDep[i] << setw(15);
		if (PointDep[i] < 10)
			cout << PointDep[i] << setw(16);
		for (j = 0; j < 4; j++)
		{
			if (j == 3)
				cout << Cost[i][j];
			else
				cout << Cost[i][j] << setw(15);
		}
		cout << endl;
	}
	cout << endl;
	//Подсчитываем количество итераций
	count = m + n - 1;
	i = 0;
	j = 0;
	check = count;

	//Найдем опорный план задачи
	while (count > 0)
	{
		//определяем элемент опорного плана
		if ((PointDep[i] <= PointDes[j]) && (check == count))
		{
			PointDes[j] -= PointDep[i];
			Sum[i][j] = PointDep[i];
			TotalCost += PointDep[i] * Cost[i][j];
			PointDep[i] = 0;
			i++;
			count--;
		}
		if ((PointDep[i] > PointDes[j]) && (check == count))
		{
			PointDep[i] -= PointDes[j];
			Sum[i][j] = PointDes[j];
			TotalCost += PointDes[j] * Cost[i][j];
			PointDes[j] = 0;
			j++;
			count--;
		}

		//Вывод матрицы
		cout << setw(17) << PointDes[0] << setw(15) << PointDes[1] << setw(15) <<
			PointDes[2] << setw(15)
			<< PointDes[3] << endl;

		for (int p = 0; p < 4; p++)
		{
			if (PointDep[p] >= 100)
				cout << PointDep[p] << setw(14);
			if (PointDep[p] < 100 && PointDep[p] >= 10)
				cout << PointDep[p] << setw(15);
			if (PointDep[p] < 10)
				cout << PointDep[p] << setw(16);
			for (int t = 0; t < 4; t++)
			{
				if (t == 3)
					cout << Cost[p][t];
				else
					cout << Cost[p][t] << setw(15);
			}
			cout << endl;
		}
		cout << endl;
		check--;
	}
	//Вывод стоимости
	cout << "\t\tОпорный план\n";
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cout << setw(15) << Sum[i][j];
		}
		cout << endl;
	}
	cout << "Итоговая стоимость = " << TotalCost << endl;
}

//Метод минимального элемента
void MinElem()
{
	int PointDep[4] = { 60, 125, 40, 35 }; //Пункт отправления
	int PointDes[4] = { 85, 105, 30, 40 }; //Пункт назначения  30-найденное значение
	int Cost[4][4] = { {12, 3, 7, 10}, {3, 8, 15, 6}, {5, 2, 3, 12}, {9, 14, 8, 1} }; //Матрица транспортных тарифов
	int i, j, t, p = 0; //Счетчики
	int m = 4; //Количество пунктов отправления
	int n = 4; //Количество пунктов назначения
	int count = 0; //количество итераций
	int check = 0;
	int Sum[4][4] = { 0 }; //Стоимость перевозки
	int TotalCost = 0;
	int min = 1000000; //минимальный элемент

	cout << "\t\tМетод минимального элемента\n" << endl;
	//Вывод матрицы
	cout << setw(17) << PointDes[0] << setw(15) << PointDes[1] << setw(15) << PointDes[2] << setw(15)
		<< PointDes[3] << endl;

	for (i = 0; i < 4; i++)
	{
		if (PointDep[i] >= 100)
			cout << PointDep[i] << setw(14);
		if (PointDep[i] < 100 && PointDep[i] >= 10)
			cout << PointDep[i] << setw(15);
		if (PointDep[i] < 10)
			cout << PointDep[i] << setw(16);

		for (j = 0; j < 4; j++)
		{
			if (j == 3)
				cout << Cost[i][j];
			else
				cout << Cost[i][j] << setw(15);
		}
		cout << endl;
	}
	cout << endl;

	//Подсчитываем количество итераций
	count = m + n - 1;
	check = count;

	while (count > 0)
	{
		//Ищем минимальный элемент в матрице тарифов
		min = 1000000;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (Cost[i][j] < min && ((PointDep[i] != 0) && (PointDes[j] != 0)))
				{
					min = Cost[i][j];
					p = i;
					t = j;
				}
			}
		}

		//Определяем элемент опорного плана
		if ((PointDep[p] <= PointDes[t]) && (check == count))
		{
			PointDes[t] -= PointDep[p];
			Sum[p][t] = PointDep[p];
			TotalCost += PointDep[p] * Cost[p][t];
			PointDep[p] = 0;
			count--;
		}
		if ((PointDep[p] > PointDes[t]) && (check == count))
		{
			PointDep[p] -= PointDes[t];
			Sum[p][t] = PointDes[t];
			TotalCost += PointDes[t] * Cost[p][t];
			PointDes[t] = 0;
			count--;
		}

		Cost[p][t] = 1000000;
		//Вывод матрицы
		cout << setw(17) << PointDes[0] << setw(15) << PointDes[1] << setw(15) << PointDes[2] << setw(15)
			<< PointDes[3] << endl;

		for (i = 0; i < 4; i++)
		{
			if (PointDep[i] >= 100)
				cout << PointDep[i] << setw(14);
			if (PointDep[i] < 100 && PointDep[i] >= 10)
				cout << PointDep[i] << setw(15);
			if (PointDep[i] < 10)
				cout << PointDep[i] << setw(16);

			for (j = 0; j < 4; j++)
			{
				if (j == 3)
					cout << Cost[i][j];
				else
					cout << Cost[i][j] << setw(15);
			}
			cout << endl;
		}
		cout << endl;
		check--;
	}

	//Вывод стоимости
	cout << "\t\tОпорный план\n";

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cout << setw(15) << Sum[i][j];
		}
		cout << endl;
	}

	cout << "Итоговая стоимость = " << TotalCost << endl;
}

//void Viroj()
//{
//	//int PointDep[4] = { 60, 125, 40, 35 }; //Пункт отправления
//	//int PointDes[5] = { 85, 105, 30, 40, 5}; //Пункт назначения
//	//int Cost[4][5] = { {12, 3, 7, 10, 5}, {3, 8, 15, 6, 7}, {5, 2, 3, 12, 10}, {9, 14, 8, 1, 4} }; //Матрица транспортных тарифов
//	int PointDep[4] = { 100, 80, 55, 70 }; //Пункт отправления
//	int PointDes[5] = { 105, 75, 80, 5, 40 }; //Пункт назначения
//	int Cost[4][5] = { {3, 5, 11, 2, 3}, {7, 3, 9, 12, 5}, {18, 6, 3, 5, 1}, {1, 8, 10, 4, 10} }; //Матрица транспортных тарифов
//	int i = 0; int j = 0; int t = 0; int p = 0; int k = 0; int r = 0; //Счетчики
//	int m = 4; //Количество пунктов отправления
//	int n = 5; //Количество пунктов назначения
//	int count = 0; //количество итераций
//	int check = 0;
//	int Sum[4][5] = { {-1,-1, -1, -1,-1}, {-1,-1, -1, -1, -1}, {-1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1} }; //Стоимость перевозки
//	int TotalCost = 0;
//
//	//Составляем опорный план
//	count = m + n - 1;
//	cout << "Число базисных переменных = " << count << endl;
//	check = count;
//
//	while (count > 0)
//	{
//		//определяем элемент опорного плана
//		if ((PointDep[i] <= PointDes[j]) && (check == count))
//		{
//			if (PointDep[i] == 0)
//			{
//				Sum[i][j] = 0;
//				i++;
//				count--;
//			}
//			else
//			{
//				PointDes[j] -= PointDep[i];
//				Sum[i][j] = PointDep[i];
//				TotalCost += PointDep[i] * Cost[i][j];
//				PointDep[i] = 0;
//				i++;
//				count--;
//			}
//		}
//		if ((PointDep[i] > PointDes[j]) && (check == count))
//		{
//			if (PointDes[j] == 0)
//			{
//				k = i - 1;
//				r = j;
//				Sum[i][j] = 0;
//				j++;
//				count--;
//			}
//			else
//			{
//				PointDep[i] -= PointDes[j];
//				Sum[i][j] = PointDes[j];
//				TotalCost += PointDes[j] * Cost[i][j];
//				PointDes[j] = 0;
//				j++;
//				count--;
//			}
//		}
//
//		//Вывод матрицы
//		cout << setw(17) << PointDes[0] << setw(15) << PointDes[1] << setw(15) << PointDes[2] << setw(15) 
//			<< PointDes[3] << setw(15) << PointDes[4] << endl;
//
//		for (int p = 0; p < 4; p++)
//		{
//			if (PointDep[p] >= 100)
//				cout << PointDep[p] << setw(14);
//			if (PointDep[p] < 100 && PointDep[p] >= 10)
//				cout << PointDep[p] << setw(15);
//			if (PointDep[p] < 10)
//				cout << PointDep[p] << setw(16);
//
//			for (int t = 0; t < 5; t++)
//			{
//				if (t == 4)
//					cout << Cost[p][t];
//				else
//					cout << Cost[p][t] << setw(15);
//			}
//
//			cout << endl;
//
//		}
//		cout << endl;
//		check--;
//	}
//
//	//Вывод опорного плана
//	cout << "\t\tОпорный план 1:\n";
//
//	for (i = 0; i < 4; i++)
//	{
//		for (j = 0; j < 5; j++)
//		{
//			cout << setw(15) << Sum[i][j];
//			if (Sum[i][j] == 0)
//				Sum[i][j] = -1;
//		}
//		cout << endl;
//	}
//
//
//	if (Sum[k - 1][r] == -1)
//	{
//		cout << "\t\tОпорный план 2:\n";
//		Sum[k - 1][r] = 0;
//		for (i = 0; i < 4; i++)
//		{
//			for (j = 0; j < 5; j++)
//			{
//				cout << setw(15) << Sum[i][j];
//				if (Sum[i][j] == 0)
//					Sum[i][j] = -1;
//			}
//			cout << endl;
//		}
//	}
//
//	if (Sum[k][r + 1] == -1)
//	{
//		cout << "\t\tОпорный план 3:\n";
//		Sum[k][r + 1] = 0;
//		for (i = 0; i < 4; i++)
//		{
//			for (j = 0; j < 5; j++)
//			{
//				cout << setw(15) << Sum[i][j];
//				if (Sum[i][j] == 0)
//					Sum[i][j] = -1;
//			}
//			cout << endl;
//		}
//	}
//
//	if (Sum[k][r - 1] == -1)
//	{
//		cout << "\t\tОпорный план 4:\n";
//		Sum[k][r - 1] = 0;
//		for (i = 0; i < 4; i++)
//		{
//			for (j = 0; j < 5; j++)
//			{
//				cout << setw(15) << Sum[i][j];
//				if (Sum[i][j] == 0)
//					Sum[i][j] = -1;
//			}
//			cout << endl;
//		}
//	}
//}

void AllSolutionSearchFunc()
{
	int Matrix[5][6] =
	{ 6,6,8,5,4,3,2,4,3,9,8,5,3,5,7,9,6,11,3,5,4,4,2,1,2,5,6,3,2,8 }; //матрица стоимостей
	int Demand[6] = { 130, 75, 65, 60, 75, 60 }; //потребности
	int Reserve[5] = { 130, 55,80,65, 135 }; //запасы
	int Flags[5][6] = { 0 };
	//счётчики
	short i = 0; short j = 0; short p = 0; short k = 0; short l = 0;
	int helper1; int helper2;
	int Result[5][6] = { 0 }; //результат
	int IterNumber = 0; //число необходимых итераций
	int TotalCost = 0; //итоговая стоимость
	int CountBasicVar = 0;
	//считаем число итераций
	IterNumber = 5 + 6 - 1;
	//цикл работы алгоритма
	while (1)
	{
		if (Reserve[i] <= Demand[j])
		{
			Result[i][j] = Reserve[i];
			Demand[j] -= Reserve[i];
			Reserve[i] -= Reserve[i];
			++i;
		}
		else if (Demand[j] <= Reserve[i])
		{
			Result[i][j] = Demand[j];
			Reserve[i] -= Demand[j];
			Demand[j] -= Demand[j];
			++j;
		}
		//критерий остановки
		if ((i + j) == IterNumber)
			break;
	}
	//печать результата
	cout << " Полученный опорный план:\n";
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 6; j++)
			if (Result[i][j] != 0)
			{
				CountBasicVar++;
				cout << setw(4) << Matrix[i][j];
				Flags[i][j] = Matrix[i][j];
			}
			else
			{
				cout << setw(4) << "-";
				Flags[i][j] = -2;
			}
		cout << endl;
	}
	cout << " Опорный план вырожден.\n Число базовых ячеек = " << CountBasicVar << ", но должно быть равно = " << IterNumber << endl;
	cout << " Добавим недостающее число ячеек с нулевым значением.\n";
	i = 0;
	j = 0;
	while (1)
	{
		//поиск места расположения базовых элементов
		for (p = 0; p < 5; p++)
		{
			int controller = 0;
			for (k = 0; k < 6; k++)
			{
				if (Result[p][k] > 0)
				{
					controller = 1;
					break;
				}
			}
			if (controller == 1)
				break;
		}
		i = p;
		j = k;
		//определение потенциальных мест для подстановки новых базовых ячеек
		if ((Result[i + 1][j] == 0) && (Result[j + 1][i] == 0))
		{
			Flags[i + 1][j] = -1;
			Flags[i][j + 1] = -1;
			helper1 = i;
			helper2 = j;
			CountBasicVar++;
		}
		Result[p][k] = -100;
		if (CountBasicVar == IterNumber)
			break;
	}
	//обнуление счетчиков
	i = 0;
	j = 0;
	p = 0;
	//вывод решений
	while (p < N)
	{
		cout << " Решение " << p + 1 << endl;
		if (p == 0)
		{
			Flags[i][j + 1] = 0;
			Flags[helper1 + 1][helper2] = 0;
		}
		if (p == 1)
		{
			Flags[i + 1][j] = 0;
			Flags[helper1][helper2 + 1] = 0;
		}
		if (p == 2)
		{
			Flags[i + 1][j] = 0;
			Flags[helper1 + 1][helper2] = 0;
		}
		if (p == 3)
		{
			Flags[i][j + 1] = 0;
			Flags[helper1][helper2 + 1] = 0;
		}
		for (l = 0; l < 5; l++)
		{
			for (k = 0; k < 6; k++)
			{
				if (Flags[l][k] >= 0)
					cout << setw(4) << Flags[l][k];
				else
					cout << setw(4) << "-";
			}
			cout << endl;
		}
		cout << endl;
		//восстановление флагов
		Flags[i + 1][j] = -1;
		Flags[i][j + 1] = -1;
		Flags[helper1 + 1][helper2] = -1;
		Flags[helper1][helper2 + 1] = -1;
		p++;
	}
}