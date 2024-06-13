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

/*---------------------------------------------------------------------*/
/*              интерфейс IChand для классов люстры                    */
/*---------------------------------------------------------------------*/
class IChand
{
public:
	virtual void LeftStick(int b1, int b2, int b3) = 0;  //рисуем левую балку
	virtual void RightStick(int b1, int b2, int b3) = 0; //рисуем правую балку
	virtual void Base(int b1, int b2, int b3) = 0;       //рисуем основание люстры
	//верхняя левая лампа
	virtual void vlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//верхняя правая лампа
	virtual void vrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//нижняя левая лампа
	virtual void nlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//нижняя правая лампа
	virtual void nrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//центральная лампа
	virtual void centrLamp(int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
};

//***************новый класс**************************
//класс люстры
class Chandelier : public Point, public IChand
{
public:
	int id;
protected:
	int lv1, lv2, lv3;    //цвета плафонов
	int lvn1, lvn2, lvn3; //цвета низа плафонов
	int b1, b2, b3;       //цвета основы люстры
	int width = 10;       //ширина палки
	int length = 15;      //длина палки
	int wc = 255;         //белый цвет
	//начальные координаты
	int pX = 160;        
	int pY1 = 45;
	int pY2 = pY1 + 2;
public:
	Chandelier(int InitX, int InitY);  //конструктор
	~Chandelier();  //деструктор
	void MoveTo(int NewX, int NewY);
	void Show();   //показать люстру
	void Hide();   //скрыть люстру
	void On();     //включить люстру
	void Off();    //выключить люстру
	void LeftStick(int b1, int b2, int b3);
	void RightStick(int b1, int b2, int b3);
	void Base(int b1, int b2, int b3);
	void vlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void vrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void nlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void nrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void centrLamp(int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
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

class ChandDop : public RChand
{
public:
	ChandDop(int InitX, int InitY);
	~ChandDop();
	void MoveTo(int NewX, int NewY);
	void Show();  //показать люстру
	void Hide();  //скрыть люстру
};

//*********************************************************************
/*---------------------------------------------------------------------*/
/*             абстрактный базовый класс для класса людей              */
/*---------------------------------------------------------------------*/
class Body
{
protected:
	int body1, body2, body3;
public:
	Body();
	~Body();
	virtual void Show() = 0;
};

//класс розового человека
class Man : public Point, public Body
{
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

class ManDop : public Man
{
public:
	ManDop(int InitX, int InitY);  //конструктор
	~ManDop();  //деструктор
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
