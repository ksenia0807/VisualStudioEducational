#include <windows.h>
#include "class4.h"
#include <iostream>
#include <vector>
using namespace std;
//���������� ����������
extern HDC hdc;  //�������� ����������
//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//���������� ������� �������
//����� Location

//�����������
Location::Location(int InitX, int InitY)
{
	//std::cout << "\nLocation";
	X = InitX;
	Y = InitY;
}

//����������
Location::~Location()
{
	//������ ����
}

//�������� �������� ����
int Location::GetX()
{
	return X;
}

int Location::GetY()
{
	return Y;
}

//������ ������ Point
//�����������
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//std::cout << "\nPoint";
	Visible = false;
}

//����������
Point::~Point()
{
	//empty body
};

bool Point::IsVisible()
{
	return Visible;
}

//������ ������ Body
//�����������
Body::Body()
{

}

//����������
Body::~Body()
{
	//empty body
};

//void SetVisible(bool NewVisible) {Visible = NewVisible;};
void Point::Show()
{
	Visible = true;  //����� �����
	//RED color
	SetPixel(hdc, X, Y, RGB(255, 0, 0)); //������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

void Point::Hide()
{
	Visible = false;  //����� �� �����
	//BLACK color
	SetPixel(hdc, X, Y, RGB(0, 0, 0)); //������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));
}

void Point::MoveTo(int NewX, int NewY)  //����������� ������
{
	Hide();  //������ ������ �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ������ �� ����� �����������
}

//****************������ ������ Chandelier*********************************************

//�����������
Chandelier::Chandelier(int InitX, int InitY) : Point(InitX, InitY)
{
	lv1 = 173; //173, 216, 230
	lv2 = 216;
	lv3 = 230; //135, 206, 235
	lvn1 = 135;
	lvn2 = 206;
	lvn3 = 235;
	b1 = 101;
	b2 = 57;
	b3 = 0;
	id = 0;
};
//����������
Chandelier::~Chandelier() {/* empty body*/ };

vector<int> Chandelier::Loc()  //������� �������� ������ ������
{
	vector<int> GetLoc;
	GetLoc.push_back(GetX() - 5);
	GetLoc.push_back(GetY() - 50);
	GetLoc.push_back(GetX() + 5);
	GetLoc.push_back(GetY());
	return GetLoc;
}

//������ ����� �����
void Chandelier::LeftStick(int b1, int b2, int b3)
{
	HBRUSH brush;
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle1, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

//������ ������ �����
void Chandelier::RightStick(int b1, int b2, int b3)
{
	HBRUSH brush;
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

//������ ��������� ������
void Chandelier::Base(int b1, int b2, int b3)
{
	HPEN pen;
	pen = CreatePen(PS_SOLID, 1, RGB(b1, b2, b3));
	SelectObject(hdc, pen);
	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(b1, b2, b3));  //(101, 57, 0)
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
	DeleteObject(pen);
}

//������� ����� �����
void Chandelier::vlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3)
{
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - pX, Y - pY1, X - (pX - width), Y - (pY1 - length));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - (pX + 20), Y - (pY1 - 10), X - (pX - width - 20), Y + (pY1 - length - 20));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - (pX + 10), Y, X - (pX - width - 10), Y + (pY1 - length - 20));
	DeleteObject(brush);
}

//������� ������ �����
void Chandelier::vrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3)
{
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + pX, Y - pY1, X + (pX - width), Y - (pY1 - length));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + (pX + 20), Y - (pY1 - 10), X + (pX - width - 20), Y + (pY1 - length - 20));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + (pX + 10), Y, X + (pX - width - 10), Y + (pY1 - length - 20));
	DeleteObject(brush);
}

//������ ����� �����
void Chandelier::nlLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3)
{
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - pX, Y + pY2, X - (pX - width), Y + (pY2 + length));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - (pX + 20), Y + (pY2 + 10), X - (pX - width - 20), Y + (pY1 - length - 20) * 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - (pX + 10), Y + pY1 * 2, X - (pX - width - 10), Y + (pY1 - length - 20) * 10);
	DeleteObject(brush);
}

//������ ������ �����
void Chandelier::nrLamp(int b1, int b2, int b3, int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3)
{
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(b1, b2, b3));
	SelectObject(hdc, brush);
	Rectangle(hdc, X + pX, Y + pY2, X + (pX - width), Y + (pY2 + length));
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + (pX + 20), Y + (pY2 + 10), X + (pX - width - 20), Y + (pY1 - length - 20) * 10);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X + (pX + 10), Y + pY1 * 2, X + (pX - width - 10), Y + (pY1 - length - 20) * 10);
	DeleteObject(brush); //��������� ���� ��������� �������
}

//����������� �����
void Chandelier::centrLamp(int lv1, int lv2, int lv3, int lvn1, int lvn2, int lvn3)
{
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(lv1, lv2, lv3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 25, Y - 5, X + 25, Y + 38);
	DeleteObject(brush);
	brush = CreateSolidBrush(RGB(lvn1, lvn2, lvn3));
	SelectObject(hdc, brush);
	Ellipse(hdc, X - 15, Y + 25, X + 15, Y + 38);
	DeleteObject(brush);
}

void Chandelier::Show() //�������� ����
{
	Visible = true;

	Chandelier::Base(b1, b2, b3);
	Chandelier::LeftStick(b1, b2, b3);
	Chandelier::RightStick(b1, b2, b3);
	Chandelier::vlLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::vrLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::nlLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::nrLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
}

void Chandelier::Hide()   //������ ����
{
	Visible = false;

	Chandelier::Base(wc, wc, wc);
	Chandelier::LeftStick(wc, wc, wc);
	Chandelier::RightStick(wc, wc, wc);
	Chandelier::vlLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
	Chandelier::vrLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
	Chandelier::nlLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
	Chandelier::nrLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
}

void Chandelier::On()  //������� ��������� ������
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

void Chandelier::Off()  //������� ���������� ������
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
	Hide();  //������ ����� �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ����� �� ����� �����������
}

//��� ����� �����
//�����������
LChand::LChand(int InitX, int InitY) : Chandelier(InitX, InitY)
{
	id = 1;
};
//����������
LChand::~LChand() {/* empty body*/ };

void LChand::Show()
{
	Visible = true;

	Chandelier::Base(b1, b2, b3);
	Chandelier::LeftStick(b1, b2, b3);
	Chandelier::vlLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::nrLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
}

void LChand::Hide()
{
	Visible = false;

	Chandelier::Base(wc, wc, wc);
	Chandelier::LeftStick(wc, wc, wc);
	Chandelier::vlLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
	Chandelier::nrLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
}

void LChand::MoveTo(int NewX, int NewY)
{
	Hide();  //������ ����� �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ����� �� ����� �����������
}

//��� ������ �����
//�����������
RChand::RChand(int InitX, int InitY) : Chandelier(InitX, InitY) { id = 2; };
//����������
RChand::~RChand() {/* empty body*/ };

void RChand::Show()
{
	Visible = true;

	Chandelier::Base(b1, b2, b3);
	Chandelier::RightStick(b1, b2, b3);
	Chandelier::vrLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::nlLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
}

void RChand::Hide()
{
	Visible = false;

	Chandelier::Base(wc, wc, wc);
	Chandelier::RightStick(wc, wc, wc);
	Chandelier::vrLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
	Chandelier::nlLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
}

void RChand::MoveTo(int NewX, int NewY)
{
	Hide();  //������ ����� �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ����� �� ����� �����������
}

//��������� ������
//�����������
NoChand::NoChand(int InitX, int InitY) : LChand(InitX, InitY) { id = 3; };

//����������
NoChand::~NoChand() {/* empty body*/ };

void NoChand::Show()
{
	Visible = true;

	Chandelier::Base(b1, b2, b3);
	Chandelier::centrLamp(lv1, lv2, lv3, lvn1, lvn2, lvn3);
}

void NoChand::Hide()
{
	Visible = false;

	Chandelier::Base(wc, wc, wc);
	Chandelier::centrLamp(wc, wc, wc, wc, wc, wc);
}

void NoChand::MoveTo(int NewX, int NewY)
{
	Hide();  //������ ����� �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ����� �� ����� �����������
}

//�����������
ChandDop::ChandDop(int InitX, int InitY) : RChand(InitX, InitY) { id = 4; };

//����������
ChandDop::~ChandDop() {/* empty body*/ };

void ChandDop::Show()
{
	Visible = true;

	Chandelier::Base(b1, b2, b3);
	Chandelier::nlLamp(b1, b2, b3, lv1, lv2, lv3, lvn1, lvn2, lvn3);
	Chandelier::RightStick(b1, b2, b3);
}

void ChandDop::Hide()
{
	Visible = false;

	Chandelier::Base(wc, wc, wc);
	Chandelier::RightStick(wc, wc, wc);
	Chandelier::nlLamp(wc, wc, wc, wc, wc, wc, wc, wc, wc);
}

void ChandDop::MoveTo(int NewX, int NewY)
{
	Hide();  //������ ����� �� ������� �����������
	X = NewX; //������ ���������� �����
	Y = NewY;
	Show();  //�������� ����� �� ����� �����������
}

void Point::Drag(int Step, vector<int> GetLoc) //���������� ������
{
	int FigX;
	int FigY;  //����� ���������� ������
	FigX = GetX();   //��������� ���������� ������
	FigY = GetY();

	//����� ����������� �������� ������
	if (KEY_DOWN(VK_LEFT))  //37 ������� ����� 
	{
		FigX = FigX - Step;
		MoveTo(FigX, FigY);
		Sleep(50);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_RIGHT))  //39 ������� ������
	{
		FigX = FigX + Step;
		MoveTo(FigX, FigY);
		Sleep(50);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_DOWN))  //40 ������� ����
	{
		FigY = FigY + Step;
		MoveTo(FigX, FigY);
		Sleep(50);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_UP))  //38 ������� �����
	{
		FigY = FigY - Step;
		MoveTo(FigX, FigY);
		Sleep(50);  //�������� �� 500 ��
	}
}

//****************������ ������ Man*********************************************

//������� �������
//�����������
Man::Man(int InitX, int InitY) : Point(InitX, InitY)
{
	body1 = 255;
	body2 = 192;
	body3 = 203;
	idm = 0;
};
//����������
Man::~Man() {/* empty body*/ };

void Man::Show() //�������� ��������
{
	Visible = true;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(body1, body2, body3));
	SelectObject(hdc, brush);   //������� ����� ��������
	Ellipse(hdc, X - 50, Y - 55, X + 50, Y + 55);  //������

	Rectangle(hdc, X - 5, Y + 55, X + 5, Y + 200); //����
	//������ ����
	POINT leg1[4] = { {X - 15, Y + 200},{X - 5,Y + 200},{X - 30,Y + 300},{X - 40,Y + 300} }; //������ ��������� ��� ���������� ������
	POINT leg2[4] = { {X + 5, Y + 200},{X + 15,Y + 200},{X + 40,Y + 300},{X + 30,Y + 300} };
	Polygon(hdc, leg1, 4);
	Polygon(hdc, leg2, 4);
	//������ ����
	POINT hand1[4] = { {X - 15, Y + 80},{X - 5,Y + 80},{X - 40,Y + 180},{X - 50,Y + 180} }; //������ ��������� ��� ���������� ��������������
	POINT hand2[4] = { {X + 5, Y + 80},{X + 15,Y + 80},{X + 50,Y + 180},{X + 40,Y + 180} }; //������ ��������� ��� ���������� ��������������
	Polygon(hdc, hand1, 4);
	Polygon(hdc, hand2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

//������� �������
//�����������
Man1::Man1(int InitX, int InitY) : Man(InitX, InitY)
{
	body1 = 135;
	body2 = 206;
	body3 = 250;
	idm = 1;
};
//����������
Man1::~Man1() {/* empty body*/ };

void Man1::Show() //�������� ��������
{
	Visible = true;
	Man::Show();
}

//�����������
ManDop::ManDop(int InitX, int InitY) : Man(InitX, InitY)
{
	idm = 4;
};
//����������
ManDop::~ManDop() {/* empty body*/ };

void ManDop::Show() //�������� ��������
{
	Visible = true;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(body1, body2, body3));
	SelectObject(hdc, brush);   //������� ����� ��������
	Rectangle(hdc, X - 50, Y - 55, X + 50, Y + 55);  //������

	Rectangle(hdc, X - 5, Y + 55, X + 5, Y + 200); //����
	//������ ����
	POINT leg1[4] = { {X - 15, Y + 200},{X - 5,Y + 200},{X - 30,Y + 300},{X - 40,Y + 300} }; //������ ��������� ��� ���������� ������
	POINT leg2[4] = { {X + 5, Y + 200},{X + 15,Y + 200},{X + 40,Y + 300},{X + 30,Y + 300} };
	Polygon(hdc, leg1, 4);
	Polygon(hdc, leg2, 4);
	//������ ����
	POINT hand1[4] = { {X - 15, Y + 80},{X - 5,Y + 80},{X - 40,Y + 180},{X - 50,Y + 180} }; //������ ��������� ��� ���������� ��������������
	POINT hand2[4] = { {X + 5, Y + 80},{X + 15,Y + 80},{X + 50,Y + 180},{X + 40,Y + 180} }; //������ ��������� ��� ���������� ��������������
	Polygon(hdc, hand1, 4);
	Polygon(hdc, hand2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

//****************������ ������ Switch*********************************************

//��������
//�����������
SwitchOff::SwitchOff(int InitX, int InitY) : Man(InitX, InitY) { idm = 2; };
//����������
SwitchOff::~SwitchOff() {/* empty body*/ };

void SwitchOff::Show()
{
	Visible = true;

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(220, 220, 220));
	SelectObject(hdc, brush);   //������� ����� ��������
	Rectangle(hdc, X - 20, Y - 35, X + 20, Y + 35);
	Rectangle(hdc, X - 12, Y - 20, X + 12, Y + 20);
	DeleteObject(brush);

	POINT off[4] = { {X - 12, Y - 20},{X + 12, Y - 20},{X + 19, Y + 10},{X - 5, Y + 10} };
	Polygon(hdc, off, 4);

	brush = CreateSolidBrush(RGB(169, 169, 169));
	SelectObject(hdc, brush);   //������� ����� ��������
	POINT off1[4] = { {X - 5, Y + 10},{X + 19, Y + 10},{X + 12, Y + 20},{X - 12, Y + 20} };
	Polygon(hdc, off1, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

//�������
//�����������
SwitchOn::SwitchOn(int InitX, int InitY) : SwitchOff(InitX, InitY) { idm = 3; };
//����������
SwitchOn::~SwitchOn() {/* empty body*/ };

void SwitchOn::Show()
{
	Visible = true;

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(220, 220, 220));
	SelectObject(hdc, brush);   //������� ����� ��������
	Rectangle(hdc, X - 20, Y - 35, X + 20, Y + 35);
	Rectangle(hdc, X - 12, Y - 20, X + 12, Y + 20);
	DeleteObject(brush);

	POINT off[4] = { {X - 12, Y - 20},{X + 12, Y - 20},{X + 19, Y - 10},{X - 5, Y - 10} };
	Polygon(hdc, off, 4);

	brush = CreateSolidBrush(RGB(169, 169, 169));
	SelectObject(hdc, brush);   //������� ����� ��������
	POINT off1[4] = { {X - 5, Y - 10},{X + 19, Y - 10},{X + 12, Y + 20},{X - 12, Y + 20} };
	Polygon(hdc, off1, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 
}

/**********************  End Of lustra.cpp File ********************/