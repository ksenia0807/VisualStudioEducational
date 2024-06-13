#include <iostream>
#include "class.h"
using namespace std;

//обращение по значению
void byValue() {
    Task a;

    a.value = 1;
    a.staticValue = 10;

    cout << "Значение a: ";
    a.printValue();
    cout << "Статическое значение a: ";
    a.printStaticValue();

    cout << "Доступ к пространсту имен: ";
    Task::printStaticValue();
}

//обращение по указателю
void byPointer() {
    Task a;

    a.value = 1;
    a.staticValue = 10;

    Task* ptr = &a;

    cout << "Значение a: ";
    ptr->printValue();
    cout << "Статическое значение a: ";
    ptr->printStaticValue();

    cout << "Доступ к пространсту имен: ";
    Task::printStaticValue();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "*****Обращение по значению*****" << endl;
    byValue();

    cout << "*****Обращение по указателю*****" << endl;
    byPointer();
}

