#include <windows.h>
#include <vector>
#include "GameField.h"

using namespace std;


GameField::GameField()
{
	int x = 0;
	for (int i = 1;i <= COLUMN_AMOUNT;i++)
	{
		x = (offsetX + Card::widht) * i;
		columns.push_back(new CardColumn(i,x));
	}
}

void GameField::DrawColumns(HWND hwnd)
{
	for (int i=0; i<COLUMN_AMOUNT;i++)
	{
		columns[i]->DrawCardColumn(hwnd);
	}
}

// Ищет по координатом точки, на которую мышью
	// нажал пользователь, соотв. карту, если такой нет вернет null
Card* GameField::CheckCollisions(int X, int Y,Card* card)
{
	for (int i=0;i<columns.size();i++)
	{
		card = columns[i]->CheckCollisions(X,Y,card);
	}
	return card;
}