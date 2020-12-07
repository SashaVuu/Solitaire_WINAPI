#include "CardColumn.h"
#include "Generator.h"

using namespace std;

CardColumn::CardColumn(int nCards,int x, Generator* generator) 
{
	this->x = x;
	columnSize = nCards;
	int suit;
	int num;
	for (int i=0;i<nCards;i++)
	{
		if (i != columnSize-1)
		{
			generator->GetSuitAndNum(suit, num);
			cardsInColumn.push_back(new Card(suit, num, false,x, y + offsetY * i));

		}
		else
		{
			generator->GetSuitAndNum(suit, num);
			cardsInColumn.push_back(new Card(suit, num, true,x, y + offsetY * i));
			
		}
	}
	
}


bool CardColumn::PushCard(Card* card)
{
	bool result = false;
	bool isSuitRight = false;


	//Если король то можно ложить на пустое место
	if (cardsInColumn.size() == 0 && card->card_num == 13)
	{
		card->x = x;
		card->y = y;
		cardsInColumn.push_back(card);
		result = true;
	}
	//Если не пустое место
	else if (cardsInColumn.size() != 0)
	{
		//Масть чередуется и значение на 1 меньше 
		if (card->card_suit == BUBA || card->card_suit == CHIRVA)
		{
			isSuitRight = (cardsInColumn.back()->card_suit == PIKA || cardsInColumn.back()->card_suit == TREFA);
		}

		if (card->card_suit == PIKA || card->card_suit == TREFA)
		{
			isSuitRight = (cardsInColumn.back()->card_suit == BUBA || cardsInColumn.back()->card_suit == CHIRVA);
		}

		//Если масть чередуется и значение на 1 меньше 
		if (card->card_num + 1 == cardsInColumn.back()->card_num && isSuitRight) {
			card->x = x;
			card->y = cardsInColumn.back()->y + offsetY;
			cardsInColumn.push_back(card);
			result = true;
		}

		//Если король то можно ложить на пустое место
		if (cardsInColumn.size() == 0 && card->card_num == 13)
		{
			card->x = x;
			card->y = y;
			cardsInColumn.push_back(card);
			result = true;
		}
	}
	return result;
}


Card* CardColumn::TopCard()
{
	Card* card = NULL;
	if (cardsInColumn.size()!=0) {
		card = cardsInColumn.back();
	}
	return card;
}


Card* CardColumn::PopCard()
{
	Card* card = NULL;
	if (cardsInColumn.size() != 0) {
		card = cardsInColumn.back();
		cardsInColumn.pop_back();


		if (cardsInColumn.size() != 0){
			cardsInColumn.back()->isActive = true;
		}
	}
	return card;
}


bool CardColumn::PushCardVector(vector<Card*> cards)
{
	bool result = false;

	for (int i=0;i<cards.size();i++) 
	{
		result=PushCard(cards[i]);
		if (result == false)
			break;
	}

	return result;

}


bool CardColumn::PopCardVector(Card* startingCard)
{
	bool result = false;
	for (int i= cardsInColumn.size()-1;i>=0;i--)
	{
		if (cardsInColumn[i]==startingCard)
		{
			PopCard();

			result = true;
			break;
		}
		PopCard();
	}
	return result;
}


vector<Card*> CardColumn::DefineCardVector(POINT point)
{
	vector<Card*> cards;
	if (cardsInColumn.size() != 0)
	{
		//Если нажато на крайнюю карту
		Card* card = cardsInColumn.back();
		if ( (card->x <= point.x) && (card->x + Card::widht >= point.x) &&
			(card->y <= point.y) &&(card->y + Card::height >= point.y))
		{
			cards.push_back(card);
			return cards;

		}

		//Если нажато на верхнюю(видимую) часть не крайней карты
		else 
		{
			for (int i = 0;i < cardsInColumn.size();i++)
			{
				if ((cardsInColumn[i]->x <= point.x) && (cardsInColumn[i]->x + Card::widht >= point.x) &&
					(cardsInColumn[i]->y <= point.y) && (cardsInColumn[i]->y + offsetY >= point.y))
				{
					if (cardsInColumn[i]->isActive==true)
					{
						for (int j = i; j<cardsInColumn.size(); j++) 
						{
							cards.push_back(cardsInColumn[j]);
						}
						return cards;
					}
				}
			}
		}
	}
	return cards;
}