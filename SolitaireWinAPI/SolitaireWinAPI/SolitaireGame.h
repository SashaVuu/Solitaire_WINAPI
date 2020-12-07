#pragma once
#pragma comment(lib, "gdiplus.lib")

#include <vector>
#include <windows.h>
#include "gdiplus.h"
#include "CardDeck.h"
#include "SuitCell.h"
#include "CardColumn.h"
#include "Generator.h"



#define BACKGROUND_PIC_PATH L"Cards\\bg_true.bmp"
#define ACTIVECARD_PIC_PATH L"Cards\\test.bmp"
#define NOTACTIVECARD_PIC_PATH L"Cards\\non.bmp"


#define WIN_HEIGHT 610
#define WIN_WIDTH 900

using namespace std;

class SolitaireGame
{

public:
	
	Generator* generator;					// ��������� ��� ����

	SolitaireGame(HWND hwnd);

	void DrawGameState(HWND hWnd);			// ��������� ��������� ����


	bool ChangeCards(POINT first, POINT second);

	bool DeckClick(POINT p);

	bool isGameOver();



private:

	//������ ���� - 4
	const int SUITCELL_Y = 20;	 
	const int CELL_AMOUNT = 4;			//���������� ������� ������

	std::vector<SuitCell*> suitCells;   // ������� ���� � 4 �������� ����,������ ������ �������� 1 �����
	

	//������� ���� - 7
	const static int offsetX = 30;      //������ ����� ���������
	const int COLUMN_AMOUNT = 7;		//���������� ������� ������

	std::vector<CardColumn*> columns;	// ������ ���� � 7 ��������� ����


	CardDeck* cardDeck;					// ������, ������� ������������� � ������� ����� ����


	//����������� �� ��� ����� ������������
	SuitCell* isSuitCell(POINT point);
	
	CardColumn* isCardColumn(POINT point);
	
	CardColumn* isLastCardInCardColumn(POINT point);
	
	bool isCardDeck(POINT point);



	//�������������� ����� � X -> � Y 
	bool FromDeckToSuitCell(SuitCell*  cell);

	bool FromDeckToCardColumn(CardColumn* column);

	bool FromSuitCellToCardColumn(SuitCell* cell, CardColumn* column);

	bool FromCardColumnToSuitCell(CardColumn* column, SuitCell* cell);

	bool FromCardColumnToCardColumn(CardColumn* column1, CardColumn* column2, POINT pointFrom);



	//��� ���������
	HWND hWnd;
	HDC hdc, memDC;
	PAINTSTRUCT ps;
	HBITMAP oldBmp, hBM;

	Gdiplus::Graphics* graphics;

	Gdiplus::Image* activeCardImage;
	Gdiplus::Image* notActiveCardImage;
	Gdiplus::Image* backgroundImage;


	float clientWidth, clientHeight;
	float scale;

	void InitPaint();
	void ReleaseGraphicsResources();
	void DrawCard(Card* card);

};