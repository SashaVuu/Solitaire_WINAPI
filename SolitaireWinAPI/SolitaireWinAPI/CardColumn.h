#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"
#include "Generator.h"

using namespace std;

class CardColumn
{
public:

	int x;							//Координата x колонны на окне
	static const int y = 175;		//Координата y колонны на окне static ибо на одном уровне все по y
	static const int offsetY=20;	//расстояние между картами в колонее
	vector<Card*> cardsInColumn;
	
	CardColumn(int nCards,int x, Generator* generator);
	
	void DrawCardColumn(HWND hWnd);

	bool PushCard(Card* card);
	Card* PopCard();
	Card* TopCard();

	bool PushCardVector(vector<Card*> card);
	bool PopCardVector(Card* startingCard);

	vector<Card*> DefineCardVector(POINT point);

private:
	int columnSize;					//Кол-во карт при инициализации присваиваем в конструкторе, дальше может меняться
};