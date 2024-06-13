#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double function(double x1, double x2, double x3); // исходная функция
double grad_x1(double x1, double x2, double x3); // чп по х1
double grad_x2(double x1, double x2, double x3); // чп по х2
double grad_x3(double x1, double x2, double x3); // чп по х3
double grad(double x1, double x2, double x3); // градиент функции
//Метод градиентного спуска с дроблением шага
void GradDescentStep(double current_x1, double current_x2, double current_x3);
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double x1 = 1;
	double x2 = 2;
	double x3 = 3;
	//Метод градиентного спуска с дроблением шага
	GradDescentStep(x1, x2, x3);
	cout << endl;
	system("pause");
	return 0;
}
double function(double x1, double x2, double x3)
{
	return -(-5 * x1 * x1 - 2 * x2 * x2 - 2 * x3 * x3 + 2 * x1 * x2 - x2 * x3 + 7 * x2);
}
double grad_x1(double x1, double x2, double x3)
{
	return -(-10 * x1 + 2 * x2);
}
double grad_x2(double x1, double x2, double x3)
{
	return -(-4 * x2 + 2 * x1 - x3 + 7);
}
double grad_x3(double x1, double x2, double x3)
{
	return -(-4 * x3 - x2);
}
double grad(double x1, double x2, double x3)
{
	double grad_x1 = 0;
	double grad_x2 = 0;
	double grad_x3 = 0;
	grad_x1 = 10 * x1 - 2 * x2;         // чп по х1
	grad_x2 = 4 * x2 - 2 * x1 + x3 - 7; // чп по х2
	grad_x3 = 4 * x3 + x2;              // чп по х3
	return (sqrt(grad_x1 * grad_x1 + grad_x2 * grad_x2 + grad_x3 * grad_x3));
}
//Метод градиентного спуска с дроблением шага
void GradDescentStep(double current_x1, double current_x2, double current_x3)
{
	//начальная установка
	double next_x1 = current_x1;
	double next_x2 = current_x2;
	double next_x3 = current_x3;
	double step = 1; //шаг
	int iterations = 0; //количество итераций
	double eps = 0.001; //точность
	double f = 0;
	double f_delta = 0;
	cout << "Градиентный спуск с дроблением шага:\n";
	cout << setw(11) << left << " Итерация" << setw(12) << left << "x1 " << setw(12)
		<< left << "x2 " << setw(12) << left << "x3 "
		<< setw(16) << left << "||gradf(x^k)|| " << setw(12) << left << " f(x^k)\n"
		<< endl;
	while (grad(next_x1, next_x2, next_x3) > eps)
	{
		current_x1 = next_x1; //определение переменных текущей итерации
		current_x2 = next_x2;
		current_x3 = next_x3;
		//получение значений функции и функции с учетом градиента
		f = function(next_x1, next_x2, next_x3);
		f_delta = function(next_x1 - step * grad_x1(current_x1, current_x2,
			current_x3), next_x2 - step * grad_x2(current_x1, current_x2, current_x3), next_x3 - step
			* grad_x3(current_x1, current_x2, current_x3));
		if (f > f_delta)
		{
			next_x1 = current_x1 - step * grad_x1(current_x1, current_x2,
				current_x3);
			next_x2 = current_x2 - step * grad_x2(current_x1, current_x2,
				current_x3);
			next_x3 = current_x3 - step * grad_x3(current_x1, current_x2,
				current_x3);
		}
		else
			step = step * 0.5; //уменьшение шага
		iterations++;
		cout << " " << setw(10) << left << iterations << setw(12) << left <<
			next_x1 << setw(12) << left << next_x2 << setw(12) << left << next_x3
			<< setw(16) << left << grad(next_x1, next_x2, next_x3) << setw(12) <<
			left << function(next_x1, next_x2, next_x3) << endl;
	}
	cout << "\nПолученная точка максимума: (" << next_x1 << ", " << next_x2 << ", " <<
		next_x3 << ")" << endl;
	cout << "Количество итераций: " << iterations << endl;
}