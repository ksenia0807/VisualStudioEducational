#pragma once
#include <vector>
using namespace std;
//���������� �������� �������

//������� �����
class Location
{
protected:
	int X;
	int Y;
public:
	Location(int InitX, int InitY); //�����������
	~Location();                    //����������
	int GetX();  //�������� �������� ���� �
	int GetY();  //�������� �������� ���� y
	void SetX(int NewX) { X = NewX; }; //�������� �������� ���� �
	void SetY(int NewY) { Y = NewY; };  //�������� �������� ���� y
};

//����������� �����
class Point : public Location
{
protected:
	bool Visible; //�������� ����� ��� ���
public:
	Point(int InitX, int InitY);
	~Point();      //����������
	bool IsVisible();    //������ ��� ���������� �����
	//void SetVisible(bool NewVisible) {Visible = NewVisible;};
	void MoveTo(int NewX, int NewY);   //����������� ����� �� ����� �����������
	/*void Show();
	void Hide();*/
	void Drag(int Step, vector<int> GetLoc); //���������� ������
	//����������� �������
	virtual void Show();  //�������� �����
	virtual void Hide();   //������ �����
	
};

//***************����� �����**************************
//����� ������
class Chandelier : public Point
{
public:
	int id;
protected:
	int lv1, lv2, lv3;   //����� ��������
	int lvn1, lvn2, lvn3; //����� ���� ��������
public:
	Chandelier(int InitX, int InitY);  //�����������
	~Chandelier();  //����������
	void MoveTo(int NewX, int NewY);
	void Show();   //�������� ������
	void Hide();   //������ ������
	void On();     //�������� ������
	void Off();    //��������� ������
	vector<int> Loc();  //������� �������� ������ ������
};

//��� ����� �����
class LChand : public Chandelier
{
public:
	LChand(int InitX, int InitY);
	~LChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //�������� ������
	void Hide();  //������ ������
};

//��� ������ �����
class RChand : public Chandelier
{
public:
	RChand(int InitX, int InitY);
	~RChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //�������� ������
	void Hide();  //������ ������
};

//��������� ������
class NoChand : public LChand
{
public:
	NoChand(int InitX, int InitY);
	~NoChand();
	void MoveTo(int NewX, int NewY);
	void Show();  //�������� ������
	void Hide();  //������ ������
};

//*********************************************************************
//����� �������� ��������
class Man : public Point 
{
protected:
	int body1, body2, body3;
public:
	int idm;
	Man(int InitX, int InitY);  //�����������
	~Man();  //����������
	void Show();  //�������� ��������
};

//����� �������� ��������
class Man1 : public Man
{
public:
	Man1(int InitX, int InitY);  //�����������
	~Man1();  //����������
	void Show();  //�������� ��������
};

//**********************************************************************
//����� �������������
class SwitchOff : public Man
{
public:
	SwitchOff(int InitX, int InitY);  //�����������
	~SwitchOff();  //����������
	void Show();  //�������� �������������
};

//������������� ���������
class SwitchOn : public SwitchOff
{
public:
	SwitchOn(int InitX, int InitY);  //�����������
	~SwitchOn();  //����������
	void Show();  //�������� �������������
};

/**********************  End Of class.h File ********************/