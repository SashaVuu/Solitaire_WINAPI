#include "Generator.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

Generator::Generator()
{
	InitVectorOfPair();
	Generate();
}

Pair::Pair(int Suit,int Num)
{
	suit = Suit;
	num = Num;
}

//������� �� ���������������� ������� �������� ����� � ����� �����
void Generator::GetSuitAndNum(int& suit, int& num)
{
	Pair* pair = PairVector.back();
	suit = pair->suit;
	num = pair->num;
	PairVector.pop_back();

	cout<<PairVector.size()<<endl;
}

//���������� ������
bool Generator::Generate()
{	

	srand(time(NULL));						// ������������ ���������� ��������� �����
	int NumOfSwap = 101  + rand() % 200;	// ���������� ������ �� 100 �� 300
	int indexFirstElement;					// ������ ������� �������� ��� �����
	int indexSecondElement;					// ������ ������� �������� ��� �����

	Pair* temp;
	Pair* pair;

	for (int i = 1;i <= NumOfSwap;i++)
	{
		indexFirstElement = rand() % 52;
		indexSecondElement =  rand() % 52;

		temp = PairVector[indexFirstElement];
		PairVector[indexFirstElement] = PairVector[indexSecondElement];
		PairVector[indexSecondElement] = temp;

	}
	return true;
}



void Generator::InitVectorOfPair()
{
	for (int i = 0;i < 52;i++)
	{
		// 1- 1 2 3 4..13
		// 2- 1 2 3 4..13
		PairVector.push_back(new Pair(i / 13 + 1, i % 13 + 1));
	}
}
