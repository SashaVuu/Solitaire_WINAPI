#include "SuitField.h"
#include "GameField.h"

SuitField::SuitField()
{
	for (int i = 1;i <= 4;i++) {
		suitCells.push_back(new SuitCell(i, 300 + i * (GameField::offsetX + Card::widht), 20));
	}
}

void SuitField::DrawSuitCell(HWND hWnd)
{
	for (int i = 0;i < 4;i++) {
		suitCells[i]->DrawSuitCell(hWnd);
	}
}

// Ищет по координатом точки, на которую мышью
// нажал пользователь, соотв. карту, если такой нет вернет null
Card* SuitField::CheckCollisions(int X, int Y, Card* card)
{
	for (int i = 0;i < suitCells.size();i++)
	{
		card = suitCells[i]->CheckCollisions(X, Y, card);
	}
	return card;
}
