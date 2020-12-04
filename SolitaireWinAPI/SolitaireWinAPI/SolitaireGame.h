#pragma once
#include "GameField.h" 
#include "SuitField.h"
#include "CardDeck.h"
#include "Generator.h"


using namespace std;

class SolitaireGame
{

public:

	GameField* gameField;	// Нижнее поле с 7 столбцами карт
	SuitField* suitField;	// Верхнее поле с 4 стопками карт,каждая стопка содержит 1 масть
	CardDeck* cardDeck;		// Колода, которая распологается в верхнем левом углу
	
	Generator* generator;	// Генератор для карт

	Card* fromCard;			// Карта(1), которую нужно переложить
	Card* toCard;			// Карта(2), на которую нужно положить карту

	SolitaireGame();

	void DrawGameState(HWND hWnd);			// Отрисовка состояния игры

	Card* CheckCollisions(int X,int Y);		// Ищет по координатом точки, на которую мышью
											// нажал пользователь, соотв. карту, если такой нет вернет null

	void InitializeSystem();				// Создает все игровые объекты, раздает всем координаты x,y
											// затем отрисовывает всё по уже инциализированным координатам
};