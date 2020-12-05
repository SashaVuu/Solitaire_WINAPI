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
	
	Generator* generator;					// Генератор для карт

	SolitaireGame();

	void DrawGameState(HWND hWnd);			// Отрисовка состояния игры


	bool ChangeCards(POINT first, POINT second);

	bool DeckClick(POINT p);

	bool isGameOver();


private:

	//Стопки карт - 4
	const int SUITCELL_Y = 20;	 
	const int CELL_AMOUNT = 4;			//Количество игровых колонн

	std::vector<SuitCell*> suitCells;   // Верхнее поле с 4 стопками карт,каждая стопка содержит 1 масть
	
	void DrawSuitCells(HWND hWnd); 


	//Колонны карт - 7
	const static int offsetX = 30;      //Отступ между колоннами
	const int COLUMN_AMOUNT = 7;		//Количество игровых колонн

	std::vector<CardColumn*> columns;	// Нижнее поле с 7 столбцами карт
	
	void DrawColumns(HWND hwnd);


	CardDeck* cardDeck;					// Колода, которая распологается в верхнем левом углу


	//Определение на что нажал пользователь
	SuitCell* isSuitCell(POINT point);
	
	CardColumn* isCardColumn(POINT point);
	
	CardColumn* isLastCardInCardColumn(POINT point);
	
	bool isCardDeck(POINT point);



	//Перетаскивание карты с X -> в Y 
	bool FromDeckToSuitCell(SuitCell*  cell);

	bool FromDeckToCardColumn(CardColumn* column);

	bool FromSuitCellToCardColumn(SuitCell* cell, CardColumn* column);

	bool FromCardColumnToSuitCell(CardColumn* column, SuitCell* cell);

	bool FromCardColumnToCardColumn(CardColumn* column1, CardColumn* column2, POINT pointFrom);

};