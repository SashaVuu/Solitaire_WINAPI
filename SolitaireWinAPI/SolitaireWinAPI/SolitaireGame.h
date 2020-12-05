#pragma once
#include <vector>
#include "CardDeck.h"
#include "SuitCell.h"
#include "CardColumn.h"
#include "Generator.h"


using namespace std;

class SolitaireGame
{

public:
	
	Generator* generator;					// ��������� ��� ����

	SolitaireGame();

	void DrawGameState(HWND hWnd);			// ��������� ��������� ����


	bool ChangeCards(POINT first, POINT second);

	bool DeckClick(POINT p);

	bool isGameOver();


private:

	//������ ���� - 4
	const int SUITCELL_Y = 20;	 
	const int CELL_AMOUNT = 4;			//���������� ������� ������

	std::vector<SuitCell*> suitCells;   // ������� ���� � 4 �������� ����,������ ������ �������� 1 �����
	
	void DrawSuitCells(HWND hWnd); 


	//������� ���� - 7
	const static int offsetX = 30;      //������ ����� ���������
	const int COLUMN_AMOUNT = 7;		//���������� ������� ������

	std::vector<CardColumn*> columns;	// ������ ���� � 7 ��������� ����
	
	void DrawColumns(HWND hwnd);


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

};