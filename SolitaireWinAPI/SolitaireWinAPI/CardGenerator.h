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

	CardGenerator();				//���������� ������� � ������� ������ (1-4)(1-13)� ����� ������������
	
	CardParam* GetCard();			//����� �������� �������������� ��������� ������ �����,
									//�� ������ ���������� ������� �� �������

private:
	void RandomizeCardVector();		//������������� ������� ���������������������� � ������������

};