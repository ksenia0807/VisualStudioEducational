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
	cout << "������� ����� ������: \n1) ����� ������-��������� ����;\n";
	cout << "2) ����� ������������ ��������;\n";
	cout << "3) ����������� ������������ ������;\n";
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

//����� ������-��������� ����
void NorthWestAngle()
{
	int PointDep[4] = { 60, 125, 40, 35 }; //����� �����������
	int PointDes[4] = { 85, 105, 30, 40 }; //����� ����������  30-��������� ��������
	int Cost[4][4] = { {12, 3, 7, 10}, {3, 8, 15, 6}, {5, 2, 3, 12}, {9, 14, 8, 1} }; //������� ������������ �������
	//������� ������������ �������
	int i, j = 0; //��������
	int m = 4; //���������� ������� �����������
	int n = 4; //���������� ������� ����������
	int count = 0; //���������� ��������
	int check = 0;
	int Sum[4][4] = { 0 }; //��������� ���������
	int TotalCost = 0;
	cout << "\t\t����� ������-��������� ����\n" << endl;
	cout << "\t\t����� �������� �������\n" << endl;
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
	//������������ ���������� ��������
	count = m + n - 1;
	i = 0;
	j = 0;
	check = count;

	//������ ������� ���� ������
	while (count > 0)
	{
		//���������� ������� �������� �����
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

		//����� �������
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
	//����� ���������
	cout << "\t\t������� ����\n";
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cout << setw(15) << Sum[i][j];
		}
		cout << endl;
	}
	cout << "�������� ��������� = " << TotalCost << endl;
}

//����� ������������ ��������
void MinElem()
{
	int PointDep[4] = { 60, 125, 40, 35 }; //����� �����������
	int PointDes[4] = { 85, 105, 30, 40 }; //����� ����������  30-��������� ��������
	int Cost[4][4] = { {12, 3, 7, 10}, {3, 8, 15, 6}, {5, 2, 3, 12}, {9, 14, 8, 1} }; //������� ������������ �������
	int i, j, t, p = 0; //��������
	int m = 4; //���������� ������� �����������
	int n = 4; //���������� ������� ����������
	int count = 0; //���������� ��������
	int check = 0;
	int Sum[4][4] = { 0 }; //��������� ���������
	int TotalCost = 0;
	int min = 1000000; //����������� �������

	cout << "\t\t����� ������������ ��������\n" << endl;
	//����� �������
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

	//������������ ���������� ��������
	count = m + n - 1;
	check = count;

	while (count > 0)
	{
		//���� ����������� ������� � ������� �������
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

		//���������� ������� �������� �����
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
		//����� �������
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

	//����� ���������
	cout << "\t\t������� ����\n";

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cout << setw(15) << Sum[i][j];
		}
		cout << endl;
	}

	cout << "�������� ��������� = " << TotalCost << endl;
}

//void Viroj()
//{
//	//int PointDep[4] = { 60, 125, 40, 35 }; //����� �����������
//	//int PointDes[5] = { 85, 105, 30, 40, 5}; //����� ����������
//	//int Cost[4][5] = { {12, 3, 7, 10, 5}, {3, 8, 15, 6, 7}, {5, 2, 3, 12, 10}, {9, 14, 8, 1, 4} }; //������� ������������ �������
//	int PointDep[4] = { 100, 80, 55, 70 }; //����� �����������
//	int PointDes[5] = { 105, 75, 80, 5, 40 }; //����� ����������
//	int Cost[4][5] = { {3, 5, 11, 2, 3}, {7, 3, 9, 12, 5}, {18, 6, 3, 5, 1}, {1, 8, 10, 4, 10} }; //������� ������������ �������
//	int i = 0; int j = 0; int t = 0; int p = 0; int k = 0; int r = 0; //��������
//	int m = 4; //���������� ������� �����������
//	int n = 5; //���������� ������� ����������
//	int count = 0; //���������� ��������
//	int check = 0;
//	int Sum[4][5] = { {-1,-1, -1, -1,-1}, {-1,-1, -1, -1, -1}, {-1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1} }; //��������� ���������
//	int TotalCost = 0;
//
//	//���������� ������� ����
//	count = m + n - 1;
//	cout << "����� �������� ���������� = " << count << endl;
//	check = count;
//
//	while (count > 0)
//	{
//		//���������� ������� �������� �����
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
//		//����� �������
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
//	//����� �������� �����
//	cout << "\t\t������� ���� 1:\n";
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
//		cout << "\t\t������� ���� 2:\n";
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
//		cout << "\t\t������� ���� 3:\n";
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
//		cout << "\t\t������� ���� 4:\n";
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
	{ 6,6,8,5,4,3,2,4,3,9,8,5,3,5,7,9,6,11,3,5,4,4,2,1,2,5,6,3,2,8 }; //������� ����������
	int Demand[6] = { 130, 75, 65, 60, 75, 60 }; //�����������
	int Reserve[5] = { 130, 55,80,65, 135 }; //������
	int Flags[5][6] = { 0 };
	//��������
	short i = 0; short j = 0; short p = 0; short k = 0; short l = 0;
	int helper1; int helper2;
	int Result[5][6] = { 0 }; //���������
	int IterNumber = 0; //����� ����������� ��������
	int TotalCost = 0; //�������� ���������
	int CountBasicVar = 0;
	//������� ����� ��������
	IterNumber = 5 + 6 - 1;
	//���� ������ ���������
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
		//�������� ���������
		if ((i + j) == IterNumber)
			break;
	}
	//������ ����������
	cout << " ���������� ������� ����:\n";
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
	cout << " ������� ���� ��������.\n ����� ������� ����� = " << CountBasicVar << ", �� ������ ���� ����� = " << IterNumber << endl;
	cout << " ������� ����������� ����� ����� � ������� ���������.\n";
	i = 0;
	j = 0;
	while (1)
	{
		//����� ����� ������������ ������� ���������
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
		//����������� ������������� ���� ��� ����������� ����� ������� �����
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
	//��������� ���������
	i = 0;
	j = 0;
	p = 0;
	//����� �������
	while (p < N)
	{
		cout << " ������� " << p + 1 << endl;
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
		//�������������� ������
		Flags[i + 1][j] = -1;
		Flags[i][j + 1] = -1;
		Flags[helper1 + 1][helper2] = -1;
		Flags[helper1][helper2 + 1] = -1;
		p++;
	}
}