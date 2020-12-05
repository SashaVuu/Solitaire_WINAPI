#include "CardDeck.h"
#include "Generator.h"

CardDeck::CardDeck(Generator* generator)
{
	int suit;
	int num;

	// ������ ������
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

	if (viewed�ards.size() != 0) {
		viewed�ards.back()->DrawCard(hWnd);
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


	if (cards.size() == 0 && viewed�ards.size()!=0) 
	{
		viewed�ards.back()->isActive = false;
		viewed�ards.back()->x = x;

		Swap(&cards,&viewed�ards);
	}
	else
	{
		//�������� ����� ������ �������� 
		if (viewed�ards.size() != 0)
		{
			viewed�ards.back()->x = x;
			viewed�ards.back()->isActive = false;
		}

		if (cards.size() != 0)
		{
			//��������� ������ �����, ����� �� ��������
			cards.front()->isActive = true;
			cards.front()->x = newX;

			viewed�ards.push_back(cards.front());

			cards.erase(cards.begin() + 0);

		}
	}
}

Card* CardDeck::TopCard() 
{
	return viewed�ards.back();
}

Card* CardDeck::PopCard()
{
	Card* card = NULL;
	if (viewed�ards.size() != 0)
	{
		card = viewed�ards.back();

		viewed�ards.pop_back();

		if (viewed�ards.size() != 0) {

			viewed�ards.back()->x = x + Card::widht + offsetX;
			viewed�ards.back()->isActive = true;
		}
	}

	return card;

}
