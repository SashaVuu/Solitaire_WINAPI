#include "SuitCell.h"

using namespace std;

SuitCell::SuitCell(int Suit, int X, int Y)
{
	x = X;
	y = Y;
	suit = Suit;
	cards.push_back(new Card(1, 2, true,X,Y));
}

void SuitCell::DrawSuitCell(HWND hWnd)
{
	cards[0]->DrawCard(hWnd);
}

// Ищет по координатом точки, на которую мышью
// нажал пользователь, соотв. карту, если такой нет вернет null
Card* SuitCell::CheckCollisions(int X, int Y , Card* card)
{
	if (card == NULL) {
		if (!cards.empty())
		{
			if ((this->x <= X) && (this->x + cards[0]->widht >= X) && (this->y <= Y) && (this->y + cards[0]->height >= Y))
			{
				card = cards.back();
			}
		}
	}
	return card;
}