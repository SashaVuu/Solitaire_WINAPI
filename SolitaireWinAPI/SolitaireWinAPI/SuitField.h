#pragma once
#include <vector>
#include "SuitCell.h"
using namespace std;

class SuitField
{

public:

	vector <SuitCell*> suitCells;
	SuitField();
	void DrawSuitCell(HWND hWnd);
	Card* CheckCollisions(int X, int Y, Card* card);

};
