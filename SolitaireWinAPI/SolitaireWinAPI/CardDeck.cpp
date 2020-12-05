#include "CardDeck.h"
#include "Generator.h"

CardDeck::CardDeck(Generator* generator)
{
	int suit;
	int num;

	// Ğàíäîì êîëîäû
	for (int i=1; i<= 52-28 ;i++) 
	{
		generator->GetSuitAndNum(suit,num);
		cards.push_back(new Card(suit, num, false, x , y));
	}

}


void CardDeck::DrawCardDeck(HWND hWnd) 
{

	if (cards.size() != 0) {
		cards.front()->DrawCard(hWnd);
	}

	if (viewedÑards.size() != 0) {
		viewedÑards.back()->DrawCard(hWnd);
	}

}

void CardDeck::Swap(vector<Card*>* p1, vector<Card*>* p2)
{
	vector<Card*> tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void CardDeck::Next()
{
	int newX = x + Card::widht + offsetX;


	if (cards.size() == 0 && viewedÑards.size()!=0) 
	{
		viewedÑards.back()->isActive = false;
		viewedÑards.back()->x = x;

		Swap(&cards,&viewedÑards);
	}
	else
	{
		//Îòêğûòóş êàğòó äåëàåì çàêğûòîé 
		if (viewedÑards.size() != 0)
		{
			viewedÑards.back()->x = x;
			viewedÑards.back()->isActive = false;
		}

		if (cards.size() != 0)
		{
			//Ïåğåíîñèì äğóãóş êàğòó, äåëàÿ åå îòêğûòîé
			cards.front()->isActive = true;
			cards.front()->x = newX;

			viewedÑards.push_back(cards.front());

			cards.erase(cards.begin() + 0);

		}
	}
}

Card* CardDeck::TopCard() 
{
	return viewedÑards.back();
}

Card* CardDeck::PopCard()
{
	Card* card = NULL;
	if (viewedÑards.size() != 0)
	{
		card = viewedÑards.back();

		viewedÑards.pop_back();

		if (viewedÑards.size() != 0) {

			viewedÑards.back()->x = x + Card::widht + offsetX;
			viewedÑards.back()->isActive = true;
		}
	}

	return card;

}
