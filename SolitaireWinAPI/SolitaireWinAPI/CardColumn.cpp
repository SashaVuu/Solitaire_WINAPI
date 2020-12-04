#include "CardColumn.h"
#include "Generator.h"
#include <vector>

using namespace std;

CardColumn::CardColumn(int nCards,int x) 
{
	columnSize = nCards;
	int suit;
	int num;
	for (int i=0;i<nCards;i++)
	{
		if (i != columnSize-1)
		{
			gen->GetSuitAndNum(suit, num);
			cardsInColumn.push_back(new Card(suit, num, false,x, y + offsetY * i));

		}
		else
		{
			gen->GetSuitAndNum(suit, num);
			cardsInColumn.push_back(new Card(suit, num, true,x, y + offsetY * i));
			
		}
	}
	
}

void CardColumn::DrawCardColumn(HWND hWnd) 
{
	for (int i=0;i< columnSize;i++)
	{
		cardsInColumn[i]->DrawCard(hWnd);
	}

	
}

// Ищет по координатом точки, на которую мышью
// нажал пользователь, соотв. карту, если такой нет вернет null
Card* CardColumn::CheckCollisions(int X, int Y, Card* card)
{
	for (int i = 0;i < cardsInColumn.size();i++)
	{
		card = cardsInColumn[i]->CheckCollision(X, Y,card);
	}
	return card;
}