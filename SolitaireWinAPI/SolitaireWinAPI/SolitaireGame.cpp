#include "SolitaireGame.h"

	GameField* gameField;	// Нижнее поле с 7 столбцами карт
	SuitField* suitField;	// Верхнее поле с 4 стопками карт,каждая стопка содержит 1 масть
	CardDeck* cardDeck;		// Колода, которая распологается в верхнем левом углу

	Card* fromCard;			// Карта(1), которую нужно переложить
	Card* toCard;			// Карта(2), на которую нужно положить карту


	SolitaireGame::SolitaireGame()
	{
		gameField = new GameField();
		suitField = new SuitField();
		cardDeck  = new CardDeck();
	}

	// Отрисовка состояния игры
	void  SolitaireGame::DrawGameState(HWND hWnd) 
	{
		gameField->DrawColumns(hWnd);
		suitField->DrawSuitCell(hWnd);
		cardDeck->DrawCardDeck(hWnd);
	}

	// Ищет по координатом точки, на которую мышью
	// нажал пользователь, соотв. карту, если такой нет вернет null
	Card* SolitaireGame::CheckCollisions(int X, int Y)
	{
		Card* card = NULL;
		card= gameField->CheckCollisions(X, Y,card);
		card = suitField->CheckCollisions(X, Y,card);
		card = cardDeck->CheckCollisions(X, Y, card);
		return card;
	}
	
	
	// Создает все игровые объекты, раздает всем координаты x,y
	// затем отрисовывает всё по уже инциализированным координатам
	void SolitaireGame::InitializeSystem() 
	{

	}