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
	int x; //Координата x карты на окне
	int y; //Координата y карты на окне
	int card_suit;
	int card_num;
	bool isActive;   //Карта в 2ух состояниях перевернутом и не перевернутом


	static HBITMAP hbitmapActiveCard; //Битмап куда грузим изображение карты
	static HBITMAP hbitmapNotActiveCard; //Битмап куда грузим изображение перевернутой карты

	Card(int suit, int num, bool _isActive,int x,int y);


};