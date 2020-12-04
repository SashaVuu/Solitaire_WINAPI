#include "SolitaireGame.h"

	GameField* gameField;	// ������ ���� � 7 ��������� ����
	SuitField* suitField;	// ������� ���� � 4 �������� ����,������ ������ �������� 1 �����
	CardDeck* cardDeck;		// ������, ������� ������������� � ������� ����� ����

	Card* fromCard;			// �����(1), ������� ����� ����������
	Card* toCard;			// �����(2), �� ������� ����� �������� �����


	SolitaireGame::SolitaireGame()
	{
		gameField = new GameField();
		suitField = new SuitField();
		cardDeck  = new CardDeck();
	}

	// ��������� ��������� ����
	void  SolitaireGame::DrawGameState(HWND hWnd) 
	{
		gameField->DrawColumns(hWnd);
		suitField->DrawSuitCell(hWnd);
		cardDeck->DrawCardDeck(hWnd);
	}

	// ���� �� ����������� �����, �� ������� �����
	// ����� ������������, �����. �����, ���� ����� ��� ������ null
	Card* SolitaireGame::CheckCollisions(int X, int Y)
	{
		Card* card = NULL;
		card= gameField->CheckCollisions(X, Y,card);
		card = suitField->CheckCollisions(X, Y,card);
		card = cardDeck->CheckCollisions(X, Y, card);
		return card;
	}
	
	
	// ������� ��� ������� �������, ������� ���� ���������� x,y
	// ����� ������������ �� �� ��� ����������������� �����������
	void SolitaireGame::InitializeSystem() 
	{

	}