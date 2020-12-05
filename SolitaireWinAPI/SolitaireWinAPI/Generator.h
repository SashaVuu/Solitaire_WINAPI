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

	bool Generate();
	void InitVectorOfPair();

};



