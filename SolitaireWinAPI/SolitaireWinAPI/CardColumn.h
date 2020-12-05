#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"
#include "Generator.h"

using namespace std;

class CardColumn
{
public:

	int x;							//���������� x ������� �� ����
	static const int y = 175;		//���������� y ������� �� ���� static ��� �� ����� ������ ��� �� y
	static const int offsetY=20;	//���������� ����� ������� � �������
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
	int columnSize;					//���-�� ���� ��� ������������� ����������� � ������������, ������ ����� ��������
};