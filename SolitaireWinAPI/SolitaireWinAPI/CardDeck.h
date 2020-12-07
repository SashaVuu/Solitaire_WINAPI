#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"
#include "Generator.h"

using namespace std;

class CardDeck
{
public:

	static const int x = 100;		
	static const int y = 20;		
	static const int offsetX = 30;	 //расстояние между картами в колонне

	CardDeck(Generator* generator);

	Card* GetOpenCard();

	Card* GetClosedCard();

	void Next();

	Card* PopCard();
	Card* TopCard();

private:

	vector<Card*> cards;
	vector<Card*> viewedСards;
	void Swap(vector<Card*>* p1, vector<Card*>* p2);

};