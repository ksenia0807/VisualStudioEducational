#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double function(double x1, double x2, double x3); // �������� �������
double grad_x1(double x1, double x2, double x3); // �� �� �1
double grad_x2(double x1, double x2, double x3); // �� �� �2
double grad_x3(double x1, double x2, double x3); // �� �� �3
double grad(double x1, double x2, double x3); // �������� �������
//������� �������� ����
double StepCalculator(double x1, double x2, double x3, double p_x1, double p_x2, double
	p_x3);
//����� ������������� ������
void FastestGradDescent(double current_x1, double current_x2, double current_x3);
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double x1 = 1;
	double x2 = 2;
	double x3 = 3;
	//����� ������������� ������
	FastestGradDescent(x1, x2, x3);
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
	grad_x1 = 10 * x1 - 2 * x2;         // �� �� �1
	grad_x2 = 4 * x2 - 2 * x1 + x3 - 7; // �� �� �2
	grad_x3 = 4 * x3 + x2;              // �� �� �3
	return (sqrt(grad_x1 * grad_x1 + grad_x2 * grad_x2 + grad_x3 * grad_x3));
}
//������� �������� ����
double StepCalculator(double x1, double x2, double x3, double p_x1, double p_x2, double p_x3)
{
	double step = 0;
	double numerator = 0;
	double denominator = 0;
	//������� ��������� ��� ����������� ����
	numerator = (-10 * x1 * p_x1 + 2 * x2 * p_x1 - 4 * x2 * p_x2 + 2 * x1 * p_x2 - 
		x3 * p_x2 + 7 * p_x2 - 4 * x3 * p_x3 - x2 * p_x3);
	denominator = (10 * p_x1 * p_x1 - 2 * p_x2 * p_x1 + 4 * p_x2 * p_x2 - 2 * p_x1 *
		p_x2 + p_x2 * p_x3 + 4 * p_x3 * p_x3 + p_x2 * p_x3);
	step = numerator / denominator;
	return step;
}
//����� ������������� ������
void FastestGradDescent(double current_x1, double current_x2, double current_x3)
{
	//��������� ���������
	double next_x1 = current_x1;
	double next_x2 = current_x2;
	double next_x3 = current_x3;
	double step = 0; //���
	int iterations = 0; //���������� ��������
	double eps = 0.001; //��������
	//�������� ������� P
	double p_x1 = 0;
	double p_x2 = 0;
	double p_x3 = 0;
	cout << "������������ �����:\n";
	cout << setw(11) << left << " ��������" << setw(12) << left << "x1 " << setw(12)
		<< left << "x2 " << setw(12) << left << "x3 "
		<< setw(16) << left << "||grad f(x^k)|| " << setw(12) << left << " f(x^k)\n" << endl;
	while (grad(next_x1, next_x2, next_x3) > eps)
	{
		//����������� ���������� ������� ��������
		current_x1 = next_x1;
		current_x2 = next_x2;
		current_x3 = next_x3;
		//������� �������� ��������� ������� P
		p_x1 = -grad_x1(current_x1, current_x2, current_x3);
		p_x2 = -grad_x2(current_x1, current_x2, current_x3);
		p_x3 = -grad_x3(current_x1, current_x2, current_x3);
		step = StepCalculator(current_x1, current_x2, current_x3, p_x1, p_x2,
			p_x3);
		//������ ��������� �������� ����������
		next_x1 = current_x1 + step * p_x1;
		next_x2 = current_x2 + step * p_x2;
		next_x3 = current_x3 + step * p_x3;
		iterations++;
		cout << " " << setw(10) << left << iterations << setw(12) << left <<
			next_x1 << setw(12) << left << next_x2 << setw(12) << left << next_x3
			<< setw(16) << left << grad(next_x1, next_x2, next_x3) << setw(12) <<
			left << function(next_x1, next_x2, next_x3) << endl;
	}
	cout << "\n���������� ����� ���������: (" << next_x1 << ", " << next_x2 << ", " <<
		next_x3 << ")" << endl;
	cout << "���������� ��������: " << iterations << endl;
}