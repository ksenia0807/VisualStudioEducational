#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
//�������� �����
void SimplexMethod(double basis[4]);
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double basis[4] = { 0, 0, 0, 0 }; //�������� ����������
	SimplexMethod(basis);
	system("pause");
	return 0;
}
//�������� �����
void SimplexMethod(double basis[4])
{
	//���������� �������� �������� �������
	double func_coef[4] = { 1, 1, -2, 1 }; //�������� �������
	double limit1_coef[5] = { 1, -1, 0, 1, 10 }; //������ �����������
	double limit2_coef[5] = { -1, 3, 1, 0, 5 }; //������ �����������
	double diff_symplex[5] = { 0, 0, 0, 0, 0 }; //������� ��������
	//����������� ���������� ������
	double x = -10000; //�������� ����������
	double y = -10000;
	int j = 0; //�������
	int basis_index1 = 0; //������ �������� ����������
	int basis_index2 = 0; //
	int choice = 0;
	int check = 1;
	double max_diff_symplex = -1000; //������������ �������� ��������
	double min_diff_symplex = 1000; //����������� �������� ��������
	double hostitem = 0; //������� �������
	double host_column_item = 0; //������� �������� �������
	int hostcolumn_index = 0; //����� �������� �������
	int hostline_index = 0; //����� ������� ������
	int n = 4; //����� ����������
	int m = 2; //����� �����������
	cout << "���������� ����� ��������� ���������� ��� n - m, �� ���� ����� ���������� - ����� �����������.��� ����� " << n - m << endl;
	cout << "����� �������� ����������, ������� ��������� ����� �����������, ����� " << m << endl;
	//���������� �������� ����������
	for (j = 0; j < 4; j++)
	{
		if (limit2_coef[j] == 0 && limit1_coef[j] != 0)
		{
			//����� �������� ������ �����������
			x = limit1_coef[4] / limit1_coef[j];
			basis[j] = x;
			basis_index1 = j;
			cout << "������� �������� ����������: x" << j + 1 << " = " <<
				basis[j] << endl;
		}
		if (limit1_coef[j] == 0 && limit2_coef[j] != 0)
		{
			//����� �������� ������ �����������
			x = limit2_coef[4] / limit2_coef[j];
			basis[j] = x;
			basis_index2 = j;
			cout << "������� �������� ����������: x" << j + 1 << " = " <<
				basis[j] << endl;
		}
	}
	x = -10000;
	cout << "�������� �������\n" << endl;
	cout << setw(26) << 0 << setw(10) << func_coef[0] << setw(10) << func_coef[1] <<
		setw(10) << func_coef[2] << setw(10) << func_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index2] << setw(5) << "x" << basis_index2 + 1
		<< setw(10) << basis[basis_index2] << setw(10) << limit1_coef[0] << setw(10) <<
		limit1_coef[1] << setw(10) << limit1_coef[2] << setw(10) << limit1_coef[3] << endl;
	cout << setw(10) << func_coef[basis_index1] << setw(5) << "x" << basis_index1 + 1
		<< setw(10) << basis[basis_index1] << setw(10) << limit2_coef[0] << setw(10) <<
		limit2_coef[1] << setw(10) << limit2_coef[2] << setw(10) << limit2_coef[3] << endl;
	//������� �������� ��������
	diff_symplex[0] = 0 - basis[basis_index1] * func_coef[basis_index1] -
		basis[basis_index2] * func_coef[basis_index2];
	cout << setw(22) << "�������� ��������" << setw(4) << diff_symplex[0];
	for (j = 0; j < 4; j++)
	{
		diff_symplex[j + 1] = func_coef[j] - limit1_coef[j] *
			func_coef[basis_index1] - limit2_coef[j] * func_coef[basis_index2];
		cout << setw(10) << diff_symplex[j + 1];
	}
	cout << "\n\n�������� ������� ������:\n1) ����� ��������� �������;\n2) ����� �������� �������; " << endl;
	cin >> choice;
	//�� ������ ������������ �������������� ����� ��������� ��� �������� �������
	while (check > 0)
	{
		check = 0;
		//����� �������� �������� ��� ������� ���������
		if (choice == 1)
		{
			max_diff_symplex = 0;
			//����� max ������� ��������
			for (j = 1; j < 5; j++)
			{
				if (diff_symplex[j] > max_diff_symplex)
				{
					max_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}
		}
		//����� �������� �������� ��� ������� ��������
		else
		{
			min_diff_symplex = 1000;
			//����� min ������� ��������
			for (j = 1; j < 5; j++)
			{
				if (min_diff_symplex > diff_symplex[j])
				{
					min_diff_symplex = diff_symplex[j];
					hostcolumn_index = j;
				}
			}
		}
		//����������� ������� ������
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
		//����������� �������� �������� � �������� ������������� ������� ������
		if (hostline_index == 1)
		{
			//���������� ������ �������� ��������
			basis[hostcolumn_index - 1] = basis[basis_index1] / hostitem;
			//���������� ������� ������
			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit1_coef[j] / hostitem;
			host_column_item = limit2_coef[hostcolumn_index - 1];
			//�������� ������ ������ �������� �������
			basis[basis_index2] = basis[hostcolumn_index - 1] * (-
				limit2_coef[hostcolumn_index - 1]) + basis[basis_index2];
			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit1_coef[j] * (-host_column_item) +
				limit2_coef[j];
			//�������� ������ �������� �������� � ����������� �������� ��������
			//�������
				host_column_item = diff_symplex[hostcolumn_index];
			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) +
				diff_symplex[0];
			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit1_coef[j] * (-host_column_item) +
				diff_symplex[j + 1];
			//�������� ������� ��������� �������� �� �������
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
			cout << setw(17) << "�������� ��������" << setw(9);
			//�������� �� ����������� ��������
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
			//���������� ������ �������� ��������
			basis[hostcolumn_index - 1] = basis[basis_index2] /
				limit2_coef[hostcolumn_index - 1];
			//���������� ������� ������
			for (j = 0; j < 4; j++)
				limit2_coef[j] = limit2_coef[j] / hostitem;
			host_column_item = limit1_coef[hostcolumn_index - 1];
			//�������� ������ ������ �������� �������
			basis[basis_index1] = basis[hostcolumn_index - 1] * (-
				host_column_item) + basis[basis_index1];
			for (j = 0; j < 4; j++)
				limit1_coef[j] = limit2_coef[j] * (-host_column_item) +
				limit1_coef[j];
			//�������� ������ �������� �������� � ����������� �������� ��������
			//�������
				host_column_item = diff_symplex[hostcolumn_index];
			diff_symplex[0] = basis[hostcolumn_index - 1] * (-host_column_item) +
				diff_symplex[0];
			for (j = 0; j < 4; j++)
				diff_symplex[j + 1] = limit2_coef[j] * (-host_column_item) +
				diff_symplex[j + 1];
			//�������� ������� ��������� �������� �� �������
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
			cout << setw(17) << "�������� ��������" << setw(9);
			for (j = 0; j < 5; j++)
				cout << diff_symplex[j] << setw(10);
			cout << "\n\n\n";
			//�������� �� ����������� ��������
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
	//����� ���������� ������ ������ � ���� �������� ������� � �����, � ������� ���
	//�����������
		cout << "��� �������� �������" << endl;
	if (choice == 1)
	{
		cout << "�������� ������� = " << -diff_symplex[0] << endl;
		cout << "� ����� ( ";
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
		cout << "������� ������� = " << -diff_symplex[0] << endl;
		cout << "� ����� ( ";
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