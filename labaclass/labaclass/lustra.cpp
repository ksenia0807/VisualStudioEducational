#include <windows.h>
#include "class.h"
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
	//std::cout << "\nChand";
	lv1 = 173; //173, 216, 230
	lv2 = 216;
	lv3 = 230; //135, 206, 235
	lvn1 = 135;
	lvn2 = 206;
	lvn3 = 235;
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

void Chandelier::Show() //�������� ����
{
	Visible = true;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(101, 57, 0));  //(101, 57, 0)
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	//������ ������ ������
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	Polygon(hdc, handle1, 4);
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ����� 
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

	//������� ������ 
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

	//����� ������ 
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

	//������ ������
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
	DeleteObject(brush); //��������� ���� ��������� �������
}

void Chandelier::Hide()   //������ ����
{
	Visible = false;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//������ ������ ������
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle1, 4);
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ����� 
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

	//������� ������ 
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

	//����� ������ 
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

	//������ ������
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
	DeleteObject(brush);  //��������� ���� ��������� �������
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

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//������ ������ ������
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle1, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ����� 
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

	//������ ������
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
	DeleteObject(brush); //��������� ���� ��������� �������
	//std::cout << "LChand show\n";
}

void LChand::Hide()
{
	Visible = false;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//������ ������ ������
	POINT handle1[4] = { {X - 145, Y - 50},{X - 175,Y - 50},{X + 145,Y + 50},{X + 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle1, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ����� 
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

	//������ ������
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
	DeleteObject(brush); //��������� ���� ��������� �������
	//std::cout << "LChand show\n";
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

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//������ ������ ������
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(101, 57, 0));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ������ 
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

	//����� ������ 
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
	DeleteObject(brush);  //��������� ���� ��������� �������
	//std::cout << "RChand show\n";
}

void RChand::Hide()
{
	Visible = false;

	HBRUSH brush;
	// ������ ������ ���������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	Rectangle(hdc, X - 5, Y - 50, X + 5, Y);
	DeleteObject(brush);

	//������ ������ ������
	POINT handle2[4] = { {X + 145, Y - 50},{X + 175,Y - 50},{X - 145,Y + 50},{X - 175,Y + 50} }; //������ ��������� ��� ���������� ��������������
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);	//������� ����� ��������
	Polygon(hdc, handle2, 4);
	DeleteObject(brush);		//��������� ���� ��������� ������ 

	//������ ������ �������
	//������� ������ 
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

	//����� ������ 
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
	DeleteObject(brush);  //��������� ���� ��������� �������
	//std::cout << "RChand show\n";
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

	HBRUSH brush;
	// ������ ������ ���������
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
	// ������ ������ ���������
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
		Sleep(200);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_RIGHT))  //39 ������� ������
	{
		FigX = FigX + Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_DOWN))  //40 ������� ����
	{
		FigY = FigY + Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //�������� �� 500 ��
	}

	if (KEY_DOWN(VK_UP))  //38 ������� �����
	{
		FigY = FigY - Step;
		MoveTo(FigX, FigY);
		Sleep(200);  //�������� �� 500 ��
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