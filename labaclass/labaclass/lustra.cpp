#include <windows.h>
#include "class.h"
#include <iostream>
#include <vector>
using namespace std;
//глобальная переменная
extern HDC hdc;  //контекст устройства
//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//реализация методов классов
//класс Location

//конструктор
Location::Location(int InitX, int InitY)
{
	//std::cout << "\nLocation";
	X = InitX;
	Y = InitY;
}

//деструктор
Location::~Location()
{
	//пустое тело
}

//получить значение поля
int Location::GetX()
{
	return X;
}

int Location::GetY()
{
	return Y;
}

//методы класса Point
//конструктор
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//std::cout << "\nPoint";
	Visible = false;
}

//деструктор
Point::~Point()
{
	//empty body
};

bool Point::IsVisible()
{
	return Visible;
}

//void SetVisible(bool NewVisible) {Visible = NewVisible;};
void Point::Show()
{
	Visible = true;  //точку видно
	//RED color
	SetPixel(hdc, X, Y, RGB(255, 0, 0)); //рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

void Point::Hide()
{
	Visible = false;  //точку не видно
	//BLACK color
	SetPixel(hdc, X, Y, RGB(0, 0, 0)); //рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));
}

void Point::MoveTo(int NewX, int NewY)  //переместить фигуру
{
	Hide();  //скрыть фигуру по текущим координатам
	X = NewX; //меняем координату точки
	Y = NewY;
	Show();  //показать фигуру по новым координатам
}

//****************МЕТОДЫ КЛАССА Chandelier*********************************************

//конструктор
Chandelier::Chandelier(int InitX, int InitY) : Point(InitX, InitY) 
{
	//std::cout << "\nChand";
	lv1 = 173; //173, 216, 230
	lv2 = 216;
	lv3 = 230; //135, 206, 235
	lvn1 = 135;
	lvn2 = 206;
	lvn3 = 235;
	id = 0;
};
//деструктор
Chandelier::~Chandelier() {/* empty body*/ };

vector<int> Chandelier::Loc()  //функция возврата границ люстры
{
	vector<int> GetLoc;
	GetLoc.push_back(GetX() - 5);
	GetLoc.push_back(GetY() - 50);
	GetLoc.push_back(GetX() + 5);
	GetLoc.push_back(GetY());
	return GetLoc;
}

void Chandelier::Show() //показать круг
{
	Visible = true;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(101, 57, 0));  //(101, 57, 0)
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	//рисуем фигуре каркас
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //Массив координат для заполнения многоугольника
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //Массив координат для заполнения многоугольника
	Polygon(hdc, handle1, 4);
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний левый 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y - 45, X - 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y - 35, X - 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y, X - 140, Y + 10);
	DeleteObject(brush);

	//верхний правый 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y - 45, X + 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y - 35, X + 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y, X + 140, Y + 10);
	DeleteObject(brush);

	//левый нижний 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y + 47, X - 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y + 57, X - 130, Y + 100); 
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y + 90, X - 140, Y + 100);
	DeleteObject(brush);

	//правый нижний
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y + 47, X + 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y + 57, X + 130, Y + 100); 
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y + 90, X + 140, Y + 100);
	DeleteObject(brush); //уничтожим нами созданные объекты
}

void Chandelier::Hide()   //скрыть круг
{
	Visible = false;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//рисуем фигуре каркас
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //Массив координат для заполнения многоугольника
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //Массив координат для заполнения многоугольника
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//Сделаем кисть активной
	Polygon(hdc, handle1, 4);
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний левый 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y - 45, X - 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y - 35, X - 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y, X - 140, Y + 10);
	DeleteObject(brush);

	//верхний правый 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y - 45, X + 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y - 35, X + 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y, X + 140, Y + 10);
	DeleteObject(brush);

	//левый нижний 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y + 47, X - 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y + 57, X - 130, Y + 100); 
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y + 90, X - 140, Y + 100);
	DeleteObject(brush);

	//правый нижний
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y + 47, X + 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y + 57, X + 130, Y + 100); 
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y + 90, X + 140, Y + 100);
	DeleteObject(brush);  //уничтожим нами созданные объекты
}

void Chandelier::On()  //функция включения люстры
{
	lv1 = 255;
	lv2 = 255;
	lv3 = 0;  //255, 215, 0
	lvn1 = 255;
	lvn2 = 215;
	lvn3 = 0;
	//this->Hide();
	this->Show();
}

void Chandelier::Off()  //функция выключения люстры
{
	lv1 = 173; //173, 216, 230
	lv2 = 216;
	lv3 = 230; //135, 206, 235
	lvn1 = 135;
	lvn2 = 206;
	lvn3 = 235;
	//this->Hide();
	this->Show();
}

void Chandelier::MoveTo(int NewX, int NewY)
{
	Hide();  //скрыть точку по текущим координатам
	X = NewX; //меняем координату точки
	Y = NewY;
	Show();  //показать точку по новым координатам
}

//без левой балки
//конструктор
LChand::LChand(int InitX, int InitY) : Chandelier(InitX, InitY)
{
	id = 1;
};
//деструктор
LChand::~LChand() {/* empty body*/ };

void LChand::Show()
{
	Visible = true;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//рисуем фигуре каркас
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //Массив координат для заполнения многоугольника
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);	//Сделаем кисть активной
	Polygon(hdc, handle1, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний левый 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y - 45, X - 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y - 35, X - 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y, X - 140, Y + 10);
	DeleteObject(brush);

	//правый нижний
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y + 47, X + 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y + 57, X + 130, Y + 100);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y + 90, X + 140, Y + 100);
	DeleteObject(brush); //уничтожим нами созданные объекты
	//std::cout << "LChand show\n";
}

void LChand::Hide()
{
	Visible = false;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//рисуем фигуре каркас
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //Массив координат для заполнения многоугольника
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//Сделаем кисть активной
	Polygon(hdc, handle1, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний левый 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y - 45, X - 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y - 35, X - 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y, X - 140, Y + 10);
	DeleteObject(brush);

	//правый нижний
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y + 47, X + 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y + 57, X + 130, Y + 100);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y + 90, X + 140, Y + 100);
	DeleteObject(brush); //уничтожим нами созданные объекты
	//std::cout << "LChand show\n";
}

void LChand::MoveTo(int NewX, int NewY)
{
	Hide();  //скрыть точку по текущим координатам
	X = NewX; //меняем координату точки
	Y = NewY;
	Show();  //показать точку по новым координатам
}

//без правой балки
//конструктор
RChand::RChand(int InitX, int InitY) : Chandelier(InitX, InitY) { id = 2; };
//деструктор
RChand::~RChand() {/* empty body*/ };

void RChand::Show()
{
	Visible = true;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//рисуем фигуре каркас
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //Массив координат для заполнения многоугольника
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);	//Сделаем кисть активной
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний правый 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y - 45, X + 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y - 35, X + 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y, X + 140, Y + 10);
	DeleteObject(brush);

	//левый нижний 
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y + 47, X - 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y + 57, X - 130, Y + 100);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y + 90, X - 140, Y + 100);
	DeleteObject(brush);
	DeleteObject(brush);  //уничтожим нами созданные объекты
	//std::cout << "RChand show\n";
}

void RChand::Hide()
{
	Visible = false;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//рисуем фигуре каркас
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //Массив координат для заполнения многоугольника
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//Сделаем кисть активной
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 

	//рисуем фигуре плафоны
	//верхний правый 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + 160, Y - 45, X + 150, Y - 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 180, Y - 35, X + 130, Y + 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + 170, Y, X + 140, Y + 10);
	DeleteObject(brush);

	//левый нижний 
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 160, Y + 47, X - 150, Y + 82);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 180, Y + 57, X - 130, Y + 100);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 170, Y + 90, X - 140, Y + 100);
	DeleteObject(brush);
	DeleteObject(brush);  //уничтожим нами созданные объекты
	//std::cout << "RChand show\n";
}

void RChand::MoveTo(int NewX, int NewY)
{
	Hide();  //скрыть точку по текущим координатам
	X = NewX; //меняем координату точки
	Y = NewY;
	Show();  //показать точку по новым координатам
}

//основание люстры
//конструктор
NoChand::NoChand(int InitX, int InitY) : LChand(InitX, InitY) { id = 3; };

//деструктор
NoChand::~NoChand() {/* empty body*/ };

void NoChand::Show()
{
	Visible = true;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 25, Y, X + 25, Y + 43);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 15, Y + 30, X + 15, Y + 43);
	DeleteObject(brush);
}

void NoChand::Hide()
{
	Visible = false;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 25, Y, X + 25, Y + 43);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 15, Y + 30, X + 15, Y + 43);
	DeleteObject(brush);
}

void NoChand::MoveTo(int NewX, int NewY)
{
	Hide();  //скрыть точку по текущим координатам
	X = NewX; //меняем координату точки
	Y = NewY;
	Show();  //показать точку по новым координатам
}

void Point::Drag(int Step, vector<int> GetLoc) //буксировка фигуры
{
	int FigX;
	int FigY;  //новые координаты фигуры
	FigX = GetX();   //начальные координаты фигуры
	FigY = GetY();

	//выбор направления движения фигуры
	if (KEY_DOWN(VK_LEFT))  //37 стрелка влево 
	{
		FigX = FigX - Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //задержка на 500 мс
	}

	if (KEY_DOWN(VK_RIGHT))  //39 стрелка вправо
	{
		FigX = FigX + Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //задержка на 500 мс
	}

	if (KEY_DOWN(VK_DOWN))  //40 стрелка вниз
	{
		FigY = FigY + Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //задержка на 500 мс
	}

	if (KEY_DOWN(VK_UP))  //38 стрелка вверх
	{
		FigY = FigY - Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //задержка на 500 мс
	}
}

//****************МЕТОДЫ КЛАССА Man*********************************************

//розовый человек
//конструктор
Man::Man(int InitX, int InitY) : Point(InitX, InitY)
{
	body1 = 255;
	body2 = 192;
	body3 = 203;
	idm = 0;
};
//деструктор
Man::~Man() {/* empty body*/ };

void Man::Show() //показать человека
{
	Visible = true;

	HBRUSH brush;
	// рисуем фигуре основание
	brush = CreateSolidBrush(RGB(body1, body2, body3));
	SelectObject(hdc, brush);   //Сделаем кисть активной
	Ellipse(hdc, X - 50, Y - 55, X + 50, Y + 55);  //голова
	
	Rectangle(hdc, X - 5, Y + 55, X + 5, Y + 200); //тело
	//рисуем ноги
	POINT leg1[4] = { {X - 15, Y + 200},{X - 5,Y + 200},{X - 30,Y + 300},{X - 40,Y + 300} }; //Массив координат для заполнения фигуры
	POINT leg2[4] = { {X + 5, Y + 200},{X + 15,Y + 200},{X + 40,Y + 300},{X + 30,Y + 300} }; 
	Polygon(hdc, leg1, 4);
	Polygon(hdc, leg2, 4);
	//рисуем руки
	POINT hand1[4] = { {X - 15, Y + 80},{X - 5,Y + 80},{X - 40,Y + 180},{X - 50,Y + 180} }; //Массив координат для заполнения многоугольника
	POINT hand2[4] = { {X + 5, Y + 80},{X + 15,Y + 80},{X + 50,Y + 180},{X + 40,Y + 180} }; //Массив координат для заполнения многоугольника
	Polygon(hdc, hand1, 4);
	Polygon(hdc, hand2, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 
}

//голубой человек
//конструктор
Man1::Man1(int InitX, int InitY) : Man(InitX, InitY)
{
	body1 = 135;
	body2 = 206;
	body3 = 250;
	idm = 1;
};
//деструктор
Man1::~Man1() {/* empty body*/ };

void Man1::Show() //показать человека
{
	Visible = true;
	Man::Show();
}

//****************МЕТОДЫ КЛАССА Switch*********************************************

//выключен
//конструктор
SwitchOff::SwitchOff(int InitX, int InitY) : Man(InitX, InitY) { idm = 2; };
//деструктор
SwitchOff::~SwitchOff() {/* empty body*/ };

void SwitchOff::Show()
{
	Visible = true;

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(220, 220, 220));
	SelectObject(hdc, brush);   //Сделаем кисть активной
	Rectangle(hdc, X - 20, Y - 35, X + 20, Y + 35);
	Rectangle(hdc, X - 12, Y - 20, X + 12, Y + 20);  
	DeleteObject(brush);

	POINT off[4] = { {X - 12, Y - 20},{X + 12, Y - 20},{X + 19, Y + 10},{X - 5, Y + 10} };
	Polygon(hdc, off, 4);

	brush = CreateSolidBrush(RGB(169, 169, 169));
	SelectObject(hdc, brush);   //Сделаем кисть активной
	POINT off1[4] = { {X - 5, Y + 10},{X + 19, Y + 10},{X + 12, Y + 20},{X - 12, Y + 20} };
	Polygon(hdc, off1, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 
}

//включен
//конструктор
SwitchOn::SwitchOn(int InitX, int InitY) : SwitchOff(InitX, InitY) { idm = 3; };
//деструктор
SwitchOn::~SwitchOn() {/* empty body*/ };

void SwitchOn::Show()
{
	Visible = true;

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(220, 220, 220));
	SelectObject(hdc, brush);   //Сделаем кисть активной
	Rectangle(hdc, X - 20, Y - 35, X + 20, Y + 35);
	Rectangle(hdc, X - 12, Y - 20, X + 12, Y + 20);  
	DeleteObject(brush);

	POINT off[4] = { {X - 12, Y - 20},{X + 12, Y - 20},{X + 19, Y - 10},{X - 5, Y - 10} };
	Polygon(hdc, off, 4);

	brush = CreateSolidBrush(RGB(169, 169, 169));
	SelectObject(hdc, brush);   //Сделаем кисть активной
	POINT off1[4] = { {X - 5, Y - 10},{X + 19, Y - 10},{X + 12, Y + 20},{X - 12, Y + 20} };
	Polygon(hdc, off1, 4);
	DeleteObject(brush);		//Уничтожим нами созданный объект 
}

/**********************  End Of lustra.cpp File ********************/