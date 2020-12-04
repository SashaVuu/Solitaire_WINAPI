#pragma once
#include <vector>
#include "CardColumn.h"

using namespace std;

class GameField
{
public:

	GameField();
	const static int offsetX = 30;   //Отступ между колоннами
	const int COLUMN_AMOUNT = 7;	 //Количество игровых колонн

	vector <CardColumn*> columns;	

	void DrawColumns(HWND hwnd);

	Card* CheckCollisions(int X, int Y, Card* card);

};