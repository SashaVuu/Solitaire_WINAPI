#pragma once
#include <windows.h>
#include <vector>
#include "Card.h"

using namespace std;

class CardColumn
{
public:
	vector<Card*> cardsInColumn;
	int columnSize;					//���-�� ���� ��� ������������� ����������� � ������������, ������ ����� ��������
	int x;							//���������� x ������� �� ����
	static const int y = 175;		//���������� y ������� �� ���� static ��� �� ����� ������ ��� �� y
	static const int offsetY=20;	//���������� ����� ������� � �������
	
	
	CardColumn(int nCards,int x);
	void DrawCardColumn(HWND hWnd);
	Card* CheckCollisions(int X, int Y, Card* card);
};