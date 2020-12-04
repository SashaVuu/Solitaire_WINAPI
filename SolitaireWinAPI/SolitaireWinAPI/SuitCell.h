#pragma once
#include <vector>
#include "Card.h"
using namespace std;

class SuitCell
{

public:

	int x;
	int y;
	int suit;
	vector <Card*> cards;
	SuitCell(int Suit, int X, int Y);

	void DrawSuitCell(HWND hWnd);
	Card* CheckCollisions(int X, int Y, Card* card);
};