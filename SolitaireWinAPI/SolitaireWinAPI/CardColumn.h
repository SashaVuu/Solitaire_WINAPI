#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"

using namespace std;

class CardColumn
{
public:
	vector<Card*> cardsInColumn;
	int columnSize;					//Кол-во карт при инициализации присваиваем в конструкторе, дальше может меняться
	int x;							//Координата x колонны на окне
	static const int y = 175;		//Координата y колонны на окне static ибо на одном уровне все по y
	static const int offsetY=20;	//расстояние между картами в колонее
	
	
	CardColumn(int nCards,int x);
	void DrawCardColumn(HWND hWnd);
	Card* CheckCollisions(int X, int Y, Card* card);
};