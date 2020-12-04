#pragma once
#include <windows.h>


#define BUBA 4
#define CHIRVA 3
#define PIKA 2
#define TREFA 1

#define KING 13
#define QUEEN 12
#define ACE 14
#define JACK 11


class Card
{
public:

	static const int widht = 73; 
	static const int height = 98;
	int x; //���������� x ����� �� ����
	int y; //���������� y ����� �� ����
	int card_suit;
	int card_num;



	static HBITMAP hbitmapActiveCard; //������ ���� ������ ����������� �����
	static HBITMAP hbitmapNotActiveCard; //������ ���� ������ ����������� ������������ �����

	bool isActive;   //����� � 2�� ���������� ������������ � �� ������������

	Card(int suit, int num, bool _isActive,int x,int y);

	void DrawCard(HWND hWnd);
	Card* CheckCollision(int X, int Y, Card* card);

private:

	void DrawActiveCard(HWND hWnd);
	void DrawNotActiveCard(HWND hWnd);

};