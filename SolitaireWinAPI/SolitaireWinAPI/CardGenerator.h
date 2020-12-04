#pragma once
#include <vector>
#include "Card.h"

using namespace std;


class CardParam
{
	int suit;
	int num;
};

class CardGenerator
{

public:
	vector<CardParam*> cardPairVector;

	CardGenerator();				//Заполнение вектора с картами парами (1-4)(1-13)и вызов рандомайзера
	
	CardParam* GetCard();			//Когда Игровому инициализатору требуется задать карту,
									//он просто вытягивает элемент из вектора

private:
	void RandomizeCardVector();		//Перемешивание вектора проинициализированного в конструкторе

};