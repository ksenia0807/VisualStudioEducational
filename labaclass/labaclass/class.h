#pragma once
#include <vector>
using namespace std;
//объявление иерархии классов

//базовый класс
class Location
{
protected:
	int X;
	int Y;
public:
	Location(int InitX, int InitY); //конструктор
	~Location();                    //деструктор
	int GetX();  //получить значение поля х
	int GetY();  //получить значение поля y
	void SetX(int NewX) { X = NewX; }; //поменять значение поля х
	void SetY(int NewY) { Y = NewY; };  //поменять значение поля y
};

//производный класс
class Point : public Location
{
protected:
	bool Visible; //светятся точки или нет
public:
	Point(int InitX, int InitY);
	~Point();      //деструктор
	bool IsVisible();    //узнать про светимость точки
	//void SetVisible(bool NewVisible) {Visible = NewVisible;};
	void MoveTo(int NewX, int NewY);   //переместить точку по новым координатам
	/*void Show();
	void Hide();*/
	void Drag(int Step, vector<int> GetLoc); //буксировка фигуры
	//виртуальные функции
	virtual void Show();  //показать точку
	virtual void Hide();   //скрыть точку
	
};

//***************новый класс**************************
//класс люстры
class Chandelier : public Point
{
public:
	int id;
protected:
	int lv1, lv2, lv3;   //цвета плафонов
	int lvn1, lvn2, lvn3; //цвета низа плафонов
public:
	Chandelier(int InitX, int InitY);  //конструктор
	~Chandelier();  //деструктор
	void MoveTo(int NewX, int NewY);
	void Show();   //показать люстру
	void Hide();   //скрыть люстру
	void On();     //включить люстру
	void Off();    //выключить люстру
	vector<int> Loc();  //функция возврата границ люстры
};

//без левой балки
class LChand : public Chandelier
{
public:
	LChand(int InitX, int InitY);
	~LChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //показать люстру
	void Hide();  //скрыть люстру
};

//без правой балки
class RChand : public Chandelier
{
public:
	RChand(int InitX, int InitY);
	~RChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //показать люстру
	void Hide();  //скрыть люстру
};

//основание люстры
class NoChand : public LChand
{
public:
	NoChand(int InitX, int InitY);
	~NoChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //показать люстру
	void Hide();  //скрыть люстру
};

//*********************************************************************
//класс розового человека
class Man : public Point 
{
protected:
	int body1, body2, body3;
public:
	int idm;
	Man(int InitX, int InitY);  //конструктор
	~Man();  //деструктор
	void Show();  //показать человека
};

//класс голубого человека
class Man1 : public Man
{
public:
	Man1(int InitX, int InitY);  //конструктор
	~Man1();  //деструктор
	void Show();  //показать человека
};

//**********************************************************************
//класс переключателя
class SwitchOff : public Man
{
public:
	SwitchOff(int InitX, int InitY);  //конструктор
	~SwitchOff();  //деструктор
	void Show();  //показать переключатель
};

//переключенное состояние
class SwitchOn : public SwitchOff
{
public:
	SwitchOn(int InitX, int InitY);  //конструктор
	~SwitchOn();  //деструктор
	void Show();  //показать переключатель
};

/**********************  End Of class.h File ********************/