#pragma once
#include <windows.h>

#define BUBA 4
#define CHIRVA 3
#define PIKA 2
#define TREFA 1

#define KING 13
#define QUEEN 12
#define ACE 1
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
	bool isActive;   //����� � 2�� ���������� ������������ � �� ������������


	static HBITMAP hbitmapActiveCard; //������ ���� ������ ����������� �����
	static HBITMAP hbitmapNotActiveCard; //������ ���� ������ ����������� ������������ �����

	Card(int suit, int num, bool _isActive,int x,int y);


};