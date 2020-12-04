#pragma once
#include "GameField.h" 
#include "SuitField.h"
#include "CardDeck.h"
#include "Generator.h"


using namespace std;

class SolitaireGame
{

public:

	GameField* gameField;	// ������ ���� � 7 ��������� ����
	SuitField* suitField;	// ������� ���� � 4 �������� ����,������ ������ �������� 1 �����
	CardDeck* cardDeck;		// ������, ������� ������������� � ������� ����� ����
	
	Generator* generator;	// ��������� ��� ����

	Card* fromCard;			// �����(1), ������� ����� ����������
	Card* toCard;			// �����(2), �� ������� ����� �������� �����

	SolitaireGame();

	void DrawGameState(HWND hWnd);			// ��������� ��������� ����

	Card* CheckCollisions(int X,int Y);		// ���� �� ����������� �����, �� ������� �����
											// ����� ������������, �����. �����, ���� ����� ��� ������ null

	void InitializeSystem();				// ������� ��� ������� �������, ������� ���� ���������� x,y
											// ����� ������������ �� �� ��� ����������������� �����������
};