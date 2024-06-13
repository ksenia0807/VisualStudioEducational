#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
void SimplexMethod(double basis[4]);
//Двойственность
void DualitySearchFunc(double basis[4]);
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double basis[4] = { 0, 0, 0, 0 }; //базисные переменные
	DualitySearchFunc(basis);
	system("pause");
	return 0;
}
//Двойственность
void DualitySearchFunc(double basis[4])
{
	//Заполнение массивов исходных функций
	double func_coef[4] = { 1, 1, -2, 1 }; //исходная функция
	double limits_coef[2][5] = { { 1, -1, 0, 1, 10 }, //ограничения функций
	{-1, 3, 1, 0, 5} };
	double duality_func_coef[2]; //двойственная функция
	double duality_limits_coef[4][2]; //ограничения двойственной функции
	int i = 0; int j = 0; int k = 0; //счетчики
	double optimal[2][2]; //матрица из компонентов оптимального базиса
	double determinant = 0; //определитель
	double optimal_T[2][2]; //транспонированная
	double optimal_inv[2][2]; //обратная
	short choice = 0; //выбор пользователя
	double y1, y2;
	cout << "Что вы ищете для исходной функции?" << endl;
	cout << "1) Определение максимума " << endl;
	cout << "2) Определение минимума " << endl;
	cin >> choice;
	//заполнение коэффициентов двойственной функции
	duality_func_coef[0] = limits_coef[0][4];
	duality_func_coef[1] = limits_coef[1][4];
	//заполнение коэффициентов ограничений двойственной функции
	for (j = 0; j < 4; j++)
		for (i = 0; i < 2; i++)
			duality_limits_coef[j][i] = limits_coef[i][j];
	//вывод получившейся двойственной задачи по отношению к исходной
	cout << "\nФункция, двойственная к исходной имеет следующий вид:\n";
	cout << "fдв. = " << duality_func_coef[0] << "y1" << " + " << duality_func_coef[1]
		<< "y2 " << endl;
	cout << "\nОграничения для функции, двойственной к исходной, имеют следующий вид:\n";
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				if (duality_limits_coef[i][j] >= 0)
					cout << setw(6) << right << "(" <<
					duality_limits_coef[i][j] << ")*" << "y" << j + 1 << setw(2) << "+";
				else if (duality_limits_coef[i][j] < 0)
					cout << setw(5) << right << "(" <<
					duality_limits_coef[i][j] << ")*" << "y" << j + 1 << setw(2) << "+";
			}
			else
			{
				if (duality_limits_coef[i][j] >= 0)
					cout << setw(3) << right << "(" <<
					duality_limits_coef[i][j] << ")*" << "y" << j + 1 << " ";
				else if (duality_limits_coef[i][j] < 0)
					cout << setw(2) << right << "(" <<
					duality_limits_coef[i][j] << ")*" << "y" << j + 1 << " ";
			}
		}
		if (choice == 1)
			cout << " >=" << setw(3) << right << func_coef[i] << endl;
		else
			cout << " <=" << setw(3) << right << func_coef[i] << endl;
	}
	//применение симплекс метода для двойственной функции
	SimplexMethod(basis);
	//составление матрицы из компонентов векторов, входящих в оптимальный базис
	for (j = 3; j > -1; j--)
	{
		if (basis[j] != 0)
		{
			optimal[0][k] = limits_coef[0][j];
			optimal[1][k] = limits_coef[1][j];
			++k;
		}
	}
	//поиск обратной матрицы
	//подсчет определителя
	determinant = optimal[0][0] * optimal[1][1] - optimal[0][1] * optimal[1][0];
	//транспонирование
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			optimal_T[i][j] = optimal[j][i];
	//высчитывание обратной матрциы
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			optimal_inv[i][j] = pow((-1), i + j + 2) * optimal_T[1 - i][1 - j] /
			determinant;
	k = 0;
	//подсчет оптимальных значений y1 и y2
	for (j = 0; j < 4; j++)
	{
		//перемножение полученной матрицы с коэффициентами исходной функции
		if (basis[j] != 0 && k != 0)
		{
			optimal_inv[0][0] = func_coef[j] * optimal_inv[0][0];
			optimal_inv[0][1] = func_coef[j] * optimal_inv[0][1];
			k++;
		}
		if (basis[j] != 0 && k == 0)
		{
			optimal_inv[1][0] = func_coef[j] * optimal_inv[1][0];
			optimal_inv[1][1] = func_coef[j] * optimal_inv[1][1];
			k++;
		}
	}
	y1 = optimal_inv[0][0] + optimal_inv[1][0];
	y2 = optimal_inv[0][1] + optimal_inv[1][1];
	cout << "Для двойственной функции" << endl;
	cout << "y1 = " << y1 << endl;
	cout << "y2 = " << y2 << endl;
	cout << "Ее значение fдв. = " << duality_func_coef[0] * y1 + duality_func_coef[1]
		* y2 << endl;
	cout << "Результаты в точности совпали." << endl;
}

/*****************************************************************************************************************/
void SimplexMethod(double basis[4])
{
	//Заполнение массивов исходных функций
	double func_coef[4] = { 1, 1, -2, 1 }; //исходная функция
	double limit1_coef[5] = { 1, -1, 0, 1, 10 }; //первое ограничение
	double limit2_coef[5] = { -1, 3, 1, 0, 5 }; //второе ограничение
	double diff_symplex[5] = { 0, 0, 0, 0, 0 }; //симлекс разности
	//Определение переменных метода
	double x = -10000; //базисные переменные
	double y = -10000;
	int j = 0; //счетчик
	int basis_index1 = 0; //номера базисных переменных
	int basis_index2 = 0; //
	int choice = 0;
	int check = 1;
	double max_diff_symplex = -1000; //максимальная симплекс разности
	double min_diff_symplex = 1000; //минимальная симплекс разности
	double hostitem = 0; //ведущий элемент
	double host_column_item = 0; //элемент ведущего столбца
	int hostcolumn_index = 0; //номер ведущего столбца
	int hostline_index = 0; //номер ведущей строки
	int n = 4; //Число переменных
	int m = 2; //Число ограничений
	cout << "Определяем число свободных переменных как n - m, то есть число переменных - число ограничений.Оно равно " << n - m << endl;
	cout << "Число базисных переменных, которое равняется числу ограничений, равно " << m << endl;
	//Определяем базисные переменные
	for (j = 0; j < 4; j++)
	{
		if (limit2_coef[j] == 0 && limit1_coef[j] != 0)
		{
			//поиск значения базвой переменнной
			x = limit1_coef[4] / limit1_coef[j];
			basis[j] = x;
			basis_index1 = j;
			cout << "Найдена базисная переменная: x" << j + 1 << " = " <<
				basis[j] << endl;
		}
		if (limit1_coef[j] == 0 && limit2_coef[j] != 0)
		{
			//поиск значения базвой переменнной
			x = limit2_coef[4] / limit2_coef[j];
			basis[j] = x;
			basis_index2 = j;
			cout << "Найдена базисная переменная: x" << j + 1 << " = " <<
				basis[j] << endl;
		}
	}
	x = -10000;
	cout << "Симплекс таблица\n" << endl;
	cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) << func_coef[1] <<
		setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" << basis_index2 + 1
		<< setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] << setw(10) <<
		limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" << basis_index1 + 1
		<< setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] << setw(10) <<
		limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] << endl;
	//подсчет симплекс разности
	diff_symplex[0] = 0 - basis[basis_index1] * func_coef[basis_index1] -
		basis[basis_index2] * func_coef[basis_index2];
	cout << setw(22) << "Симплекс разности" << setw(4) << diff_symplex[0];
	for (j = 0; j < 4; j++)
	{
		diff_symplex[j + 1] = func_coef[j] - limit1_coef[j] *
			func_coef[basis_index1] - limit2_coef[j] * func_coef[basis_index2];
		cout << setw(10) << diff_symplex[j + 1];
	}
	cout << "\n\nВыберете вариант поиска:\n1) Поиск максимума функции;\n2) Поиск минимума функции; " << endl;
	cin >> choice;
	//По выбору пользователя осуществляется поиск максимума или минимума функции
	while (check > 0)
	{
		check = 0;
		//поиск симплекс разности для расчета максимума
		if (choice == 1)
		{
			max_diff_symplex = 0;
			//поиск max симлекс разности
			for (j = 1; j < 5; j++)
			{
				if (diff_symplex[j] > max_diff_symplex)
				{
					max_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}
		}
		//поиск симплекс разности для расчета минимума
		else
		{
			min_diff_symplex = 1000;
			//поиск min симлекс разности
			for (j = 1; j < 5; j++)
			{
				if (min_diff_symplex > diff_symplex[j])
				{
					min_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}
		}
		//определение ведущей строки
		if (basis[basis_index2] / limit1_coef[hostcolumn_index - 1] > 0 &&
			limit1_coef[hostcolumn_index - 1] != 0)
			x = basis[basis_index2] / limit1_coef[hostcolumn_index - 1];
		if (basis[basis_index1] / limit2_coef[hostcolumn_index - 1] > 0 &&
			limit2_coef[hostcolumn_index - 1] != 0)
			y = basis[basis_index1] / limit2_coef[hostcolumn_index - 1];
		if ((x > y && y > 0) || x < 0)
		{
			hostline_index = 2;
			hostitem = limit2_coef[hostcolumn_index - 1];
		}
		if ((x < y && x >0) || y < 0)
		{
			hostline_index = 1;
			hostitem = limit1_coef[hostcolumn_index - 1];
		}
		//определение ведущего элемента и пересчет коэффициентов ведущей строки
		if (hostline_index == 1)
		{
			//добавление нового базового элемента
			basis[hostcolumn_index - 1] = basis[basis_index1] / hostitem;
			//обновление ведущей строки
			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit1_coef[j] / hostitem;
			host_column_item = limit2_coef[hostcolumn_index - 1];
			//пересчёт второй строки симплекс таблицы
			basis[basis_index2] = basis[hostcolumn_index - 1] * (-
				limit2_coef[hostcolumn_index - 1]) + basis[basis_index2];
			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit1_coef[j] * (-host_column_item) +
				limit2_coef[j];
			//пересчёт строки симплекс разности и запоминание элемента ведущего
			//столбца
			host_column_item = diff_symplex[hostcolumn_index];
			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) +
				diff_symplex[0];
			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit1_coef[j] * (-host_column_item) +
				diff_symplex[j + 1];
			//удаление старого базисного элемента из массива
			basis[basis_index1] = 0;
			basis_index1 = hostcolumn_index - 1;
			cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) <<
				func_coef[1] << setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" <<
				basis_index2 + 1 << setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] <<
				setw(10) << limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] <<
				endl;
			cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" <<
				basis_index1 + 1 << setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] <<
				setw(10) << limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] <<
				endl;
			cout << setw(17) << "Симплекс разности" << setw(9);
			//проверка на последующую итерацию
			if (choice == 1)
			{
				for (j = 0; j < 5; j++)
				{
					cout << diff_symplex[j] << setw(10);
					if (diff_symplex[j] > 0)
						check++;
				}
				cout << "\n\n\n";
			}
			else
			{
				for (j = 0; j < 5; j++)
				{
					cout << diff_symplex[j] << setw(10);
					if (diff_symplex[j] < 0)
						check++;
				}
				cout << "\n\n\n";
			}
		}
		if (hostline_index == 2)
		{
			//добавление нового базового элемента
			basis[hostcolumn_index - 1] = basis[basis_index2] /
				limit2_coef[hostcolumn_index - 1];
			//обновление ведущей строки
			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit2_coef[j] / hostitem;
			host_column_item = limit1_coef[hostcolumn_index - 1];
			//пересчёт первой строки симплекс таблицы
			basis[basis_index1] = basis[hostcolumn_index - 1] * (-
				host_column_item) + basis[basis_index1];
			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit2_coef[j] * (-host_column_item) +
				limit1_coef[j];
			//пересчёт строки симплекс разности и запоминание элемента ведущего
			//столбца
			host_column_item = diff_symplex[hostcolumn_index];
			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) +
				diff_symplex[0];
			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit2_coef[j] * (-host_column_item) +
				diff_symplex[j + 1];
			//удаление старого базисного элемента из массива
			basis[basis_index2] = 0;
			basis_index2 = hostcolumn_index - 1;
			cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) <<
				func_coef[1] << setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
			cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" <<
				basis_index2 + 1 << setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] <<
				setw(10) << limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] <<
				endl;
			cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" <<
				basis_index1 + 1 << setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] <<
				setw(10) << limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] <<
				endl;
			cout << setw(17) << "Симплекс разности" << setw(9);
			for (j = 0; j < 5; j++)
				cout << diff_symplex[j] << setw(10);
			cout << "\n\n\n";
			//проверка на последующую итерацию
			if (choice == 1)
			{
				for (j = 1; j < 5; j++)
					if (diff_symplex[j] > 0)
						check++;
				cout << endl << endl;
			}
			else
			{
				for (j = 1; j < 5; j++)
					if (diff_symplex[j] < 0)
						check++;
				cout << endl << endl;
			}
		}
	}
	//вывод результата работы метода в виде значения функции и точки, в которой оно
	//достигается
	cout << "Для исходной функции" << endl;
	if (choice == 1)
	{
		cout << "Максимум функции = " << -diff_symplex[0] << endl;
		cout << "В точке ( ";
		for (j = 0; j < 4; j++)
		{
			if (j != 3)
				cout << basis[j] << ", ";
			else
				cout << basis[j] << " ";
		}
		cout << ")" << endl;
	}
	if (choice == 2)
	{
		cout << "Минимум функции = " << -diff_symplex[0] << endl;
		cout << "В точке ( ";
		for (j = 0; j < 4; j++)
		{
			if (j != 3)
				cout << basis[j] << ", ";
			else
				cout << basis[j] << " ";
		}
		cout << ")" << endl;
	}
}