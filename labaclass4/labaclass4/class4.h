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

/*---------------------------------------------------------------------*/
/*              ��������� IChand ��� ������� ������                    */
/*---------------------------------------------------------------------*/
class IChand
{
public:
	virtual void LeftStick(int b1, int b2, int b3) = 0;  //������ ����� �����
	virtual void RightStick(int b1, int b2, int b3) = 0; //������ ������ �����
	virtual void Base(int b1, int b2, int b3) = 0;       //������ ��������� ������
	//������� ����� �����
	virtual void vlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//������� ������ �����
	virtual void vrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//������ ����� �����
	virtual void nlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//������ ������ �����
	virtual void nrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
	//����������� �����
	virtual void centrLamp(int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3) = 0;
};

//***************����� �����**************************
//����� ������
class Chandelier : public Point, public IChand
{
public:
	int id;
protected:
	int lv1, lv2, lv3;    //����� ��������
	int lvn1, lvn2, lvn3; //����� ���� ��������
	int b1, b2, b3;       //����� ������ ������
	int width = 10;       //������ �����
	int length = 15;      //����� �����
	int wc = 255;         //����� ����
	//��������� ����������
	int pX = 160;        
	int pY1 = 45;
	int pY2 = pY1 + 2;
public:
	Chandelier(int InitX, int InitY);  //�����������
	~Chandelier();  //����������
	void MoveTo(int NewX, int NewY);
	void Show();   //�������� ������
	void Hide();   //������ ������
	void On();     //�������� ������
	void Off();    //��������� ������
	void LeftStick(int b1, int b2, int b3);
	void RightStick(int b1, int b2, int b3);
	void Base(int b1, int b2, int b3);
	void vlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void vrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void nlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void nrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
	void centrLamp(int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3);
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

class ChandDop : public RChand
{
public:
	ChandDop(int InitX, int InitY);
	~ChandDop();
	void MoveTo(int NewX, int NewY);
	void Show();  //�������� ������
	void Hide();  //������ ������
};

//*********************************************************************
/*---------------------------------------------------------------------*/
/*             ����������� ������� ����� ��� ������ �����              */
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

//����� �������� ��������
class Man : public Point, public Body
{
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

class ManDop : public Man
{
public:
	ManDop(int InitX, int InitY);  //�����������
	~ManDop();  //����������
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
