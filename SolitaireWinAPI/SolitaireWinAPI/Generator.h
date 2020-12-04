#pragma once
#include <vector>

using namespace std;

class Pair
{

public:

	Pair(int suit, int num);
	int suit;
	int num;

};

class Generator
{

public:
	Generator();
	void GetSuitAndNum(int &suit,int &num);
	vector<Pair*> PairVector;

private:
	//vector<Pair*> PairVector;
	bool Generate();
	void ShowArray(); //для отладки
	void InitVectorOfPair();
};


static Generator* gen = new Generator();


