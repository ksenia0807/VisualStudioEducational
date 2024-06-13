#include <iostream>
#include "class.h"
using namespace std;

//��������� �� ��������
void byValue() {
    Task a;

    a.value = 1;
    a.staticValue = 10;

    cout << "�������� a: ";
    a.printValue();
    cout << "����������� �������� a: ";
    a.printStaticValue();

    cout << "������ � ����������� ����: ";
    Task::printStaticValue();
}

//��������� �� ���������
void byPointer() {
    Task a;

    a.value = 1;
    a.staticValue = 10;

    Task* ptr = &a;

    cout << "�������� a: ";
    ptr->printValue();
    cout << "����������� �������� a: ";
    ptr->printStaticValue();

    cout << "������ � ����������� ����: ";
    Task::printStaticValue();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "*****��������� �� ��������*****" << endl;
    byValue();

    cout << "*****��������� �� ���������*****" << endl;
    byPointer();
}

