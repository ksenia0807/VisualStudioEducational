#pragma once
#include <iostream>
using namespace std;

class Task {
public:
    int value = 1;             //�������� ��������
    static int staticValue;    //��������� ����������� ��������

    void printValue() {
        cout << value << endl;
    }

    static void printStaticValue() {
        cout << staticValue << endl;
    }
};

int Task::staticValue = 0;     
