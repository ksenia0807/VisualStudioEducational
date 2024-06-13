/**************************************************************************
*                      К  У  Р  С      О  О  П                            *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  : labaclass                                               *
* Project Type  : Win32 Console application                               *
* File Name     : main.cpp                                                *
* Language      : Visual C++           MS VS 2019                         *
* Programmer(s) : Кадырова К.Д.                                           *
* Modified By   : Кадырова К.Д.                                           *
* Created       : 28 / 04 / 2023                                          *
* Last Revision : 02 / 06 / 2023                                          *
* Comment(s)    : Лабораторная работа                                     *
*                                                                         *
*                                                                         *
***************************************************************************/

#pragma once                  
#include <windows.h>
#include <conio.h>
#include <iostream>    
#include <vector>
using namespace std;           // Пространство имен std
#include "class.h"

bool Collision(Chandelier* inputChandelier, Man* inputMan, vector<int> GetLoc);
//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

HDC hdc;// Объявим контекст устройства
		// Контекст устройства по сути это структура,
		// содержащая описание видеокарты на вашем компьютере
		// и всех необходимых графических элементов

/*---------------------------------------------------------------------*/
/*               П Р О Т О Т И П Ы    Ф У Н К Ц И Й                    */
/*---------------------------------------------------------------------*/
HWND GetConcolWindow(); //указатель на консольное окно

/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
int main()
{
	//объявление и инициализация переменных
	int x0 = 500;	//стартовые координаты точки/люстры
	int y0 = 200;
	int x1 = 225;	//стартовые координаты человека
	int y1 = 350;
	int x2 = 750;	//стартовые координаты переключателя
	int y2 = 450;

	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	system("color F0");

	//если дескриптор существует
	if (hwnd != NULL)
	{
		//получим контекст устройства для консольного окна
		hdc = GetWindowDC(hwnd);

		//если контекст существует - можем работать
		if (hdc != 0)
		{
			//===================================================================
			//	М Е С Т О    В С Т А В К И 	

			//инициализация люстр
			Chandelier AChandelier(x0, y0);  
			LChand ALChand(x0, y0);
			RChand ARChand(x0, y0);
			NoChand ANoChand(x0, y0);
			
			//инициализация конфликтующих объектов
			Man AMan(x1, y1);
			Man1 AMan1(x1+200, y1);
			SwitchOff ASwitchOff(x2, y2);
			SwitchOn ASwitchOn(x2+100, y2);

			Chandelier* BufChandelier[4];  //массив люстр
			BufChandelier[0] = &AChandelier;
			BufChandelier[1] = &ALChand;
			BufChandelier[2] = &ARChand;
			BufChandelier[3] = &ANoChand;

			Man* BufObjects[4];    //массив конфликтующих объектов
			BufObjects[0] = &AMan;
			BufObjects[1] = &AMan1;
			BufObjects[2] = &ASwitchOff;
			BufObjects[3] = &ASwitchOn;


			int MatrCollision[4][4] = { {1,3,3,0}, 
										{2,3,3,1}, 
										{0,1,2,3}, 
										{0,1,2,3} };  //матрица переходов
			
			vector<int> Stop = AChandelier.Loc();  //вектор, который возвращает границы люстры

			Chandelier* CurChandelier = BufChandelier[0]; //инициализируем указатель на объекты классов с люстрами
		
			Man* pointerMan = &AMan; //инициализируем указатель на объекты классов с люстрами
			Man* pointerMan1 = &AMan1; //инициализируем указатель на объекты классов с люстрами
			Man* SwOff = &ASwitchOff;  //инициализируем указатель на объекты классов с люстрами
			Man* SwOn = &ASwitchOn;        //инициализируем указатель на объекты классов с люстрами
			while (1)
			{
				if (KEY_DOWN(VK_ESCAPE))   //выход из цикла по Esc
					break;
			
				//показать объекты в окне
				CurChandelier->Show();  
				pointerMan->Show();
				pointerMan1->Show();
				SwOff->Show();
				SwOn->Show();
				
				CurChandelier->Drag(50, Stop);  //перемещение люстры
				
				//возможные столкновения с люстрой
				for (int i = 0; i < 4; i++)  //цикл по объектам
				{
					bool res = Collision(CurChandelier, BufObjects[i], Stop);  //проверка на столкновение
					
					if ((res == true) && (i != 2) && (i != 3))  //конфликтующий объект не является переключателем
					{
						int icol = CurChandelier->id;
						int irow = BufObjects[i]->idm;

						int IndCurChandelier = MatrCollision[irow][icol];
						CurChandelier = BufChandelier[IndCurChandelier];
						break;
						//CurChandelier->Show();
					}//end if
					if ((res == true) && ((i == 2) || (i == 3)))  //конфликтующий объект переключатель
					{
						if (i == 2)
							CurChandelier->Off();  //выключаем люстру
						if (i == 3)
							CurChandelier->On();   //ключаем люстру
					}//end if
				}//end for 
				Sleep(50);
			}//end while
			
			while (1)
				if (KEY_DOWN(48))  //цифра 0 ВЫХОД ИЗ ПРОГРАММЫ
					break;

			

			//===================================================================
		}//end if
	}//end if
	return 0;
}//end main()

/*---------------------------------------------------------------------*/
/*               Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й                   */
/*---------------------------------------------------------------------*/
bool Collision(Chandelier* inputChandelier, Man* inputMan,  vector<int> GetLoc)  //проверка на столкновение объектов
{
	if ((inputChandelier->GetX() < inputMan->GetX() + 50) && (inputChandelier->GetX() > inputMan->GetX() -
		50) && (inputChandelier->GetY() < inputMan->GetY() + 55) && (inputChandelier->GetY() > inputMan->GetY() - 55))
	{
		inputChandelier->Hide(); //скрыть лампу
		inputChandelier->SetX(500);
		inputChandelier->SetY(200);
		return true;
	}//end if
	else
	{
		return false;
	}//end else
}//end Collision()
/*----------------------------------------------------------------------*/
/*  Создать консольное окно  */
/*---------------------------*/
HWND GetConcolWindow()
{
	char str[128];
	//char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()

/**********************  End Of main.cpp File ********************/

