#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"

using namespace std;

class CardDeck
{
public:

	vector<Card*> cards;

	static const int x = 100;		
	static const int y = 20;		
	static const int offsetX = 30;	 //расстояние между картами в колонне

	CardDeck();
	void DrawCardDeck(HWND hWnd);

	Card* CheckCollisions(int X, int Y, Card* card);

};