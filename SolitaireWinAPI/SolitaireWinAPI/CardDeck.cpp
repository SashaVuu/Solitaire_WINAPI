#include "CardDeck.h"
#include "Generator.h"

CardDeck::CardDeck() 
{
	int suit;
	int num;
	for (int i=1; i<= 52-28 ;i++) 
	{
		gen->GetSuitAndNum(suit,num);
		cards.push_back(new Card(suit, num, false, x , y));
	}

	gen->GetSuitAndNum(suit, num);
	cards.push_back(new Card(suit, num, true, x + Card::widht + offsetX, y));

}


void CardDeck::DrawCardDeck(HWND hWnd) 
{
	cards.back()->DrawCard(hWnd);
	cards.front()->DrawCard(hWnd);
}


Card* CardDeck::CheckCollisions(int X, int Y, Card* card)
{
	if (card == NULL) {
		if (!cards.empty())
		{
			if ((this->x <= X) && (this->x + cards[0]->widht>=X) && (this->y <= Y) && (this->y + cards[0]->height >= Y))
			{
				card = cards.back();
			}
		}
	}
	return card;
}