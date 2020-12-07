#include "SuitCell.h"

using namespace std;

SuitCell::SuitCell(int Suit, int X, int Y)
{
	x = X;
	y = Y;
	suit = Suit;
}

bool SuitCell::PushCard(Card* card)
{
	bool isPushed = false;

	//Если  масть карты совпадает с мастью стопки
	if (card->card_suit == suit) {

		//Если стопка не пуста, и значение предыдущей карты на 1 меньше пришедшей
		if (cards.size() > 0 && cards.size() <= 13 && (cards.back()->card_num+1 == card->card_num) ) {
			
				card->x = x;
				card->y = y;
				cards.push_back(card);
				isPushed = true;
		}

		//Если стопка пуста, карта - Туз
		else if (cards.size() == 0  && card->card_num == ACE) {

			card->x = x;
			card->y = y;
			cards.push_back(card);
			isPushed = true;
		}

	}

	return isPushed;

}

Card* SuitCell::PopCard()
{
	Card* result = NULL;
	//Если стопка не пустая возращаем верхнюю карту
	if (cards.size() != 0)
	{
		 result = cards.back();
		cards.pop_back();
	}
	return result;

}

Card* SuitCell::TopCard()
{
	Card* card = NULL;
	if (cards.size()!=0) {
		card = cards.back();
	}
	return card;

}

bool SuitCell::IsFilled()
{
	bool result = false;
	if (cards.size()==13) 
	{
		result = true;
	}
	return result;
}