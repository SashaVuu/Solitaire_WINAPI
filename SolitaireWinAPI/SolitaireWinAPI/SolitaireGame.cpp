#include "SolitaireGame.h"


	SolitaireGame::SolitaireGame(const HWND hwnd)
	{
		hWnd = hwnd;

		activeCardImage = new Gdiplus::Image(ACTIVECARD_PIC_PATH);
		notActiveCardImage = new Gdiplus::Image(NOTACTIVECARD_PIC_PATH);
		backgroundImage = new Gdiplus::Image(BACKGROUND_PIC_PATH);


		generator = new Generator();

		//Инициализация нижних 7 колонок
		int x = 0;
		for (int i = 1;i <= COLUMN_AMOUNT;i++)
		{
			x = (offsetX + Card::widht) * i;
			columns.push_back(new CardColumn(i, x, generator));
		}

		//Инициализация верхних 4 стопок	
		suitCells.push_back(new SuitCell(TREFA, 300 + 1 * (offsetX + Card::widht), SUITCELL_Y));
		suitCells.push_back(new SuitCell(PIKA, 300 + 2 * (offsetX + Card::widht), SUITCELL_Y));
		suitCells.push_back(new SuitCell(CHIRVA, 300 + 3 * (offsetX + Card::widht), SUITCELL_Y));
		suitCells.push_back(new SuitCell(BUBA, 300 + 4 * (offsetX + Card::widht), SUITCELL_Y));

		cardDeck  = new CardDeck (generator);
	
	}


	//true - две точки на экране найден
	//false - одна из точек не найдена
	bool SolitaireGame::ChangeCards(POINT first,POINT second)
	{

		//Deck -> to Cell or Column
		if (isCardDeck(first))
		{
			CardColumn* cc = isCardColumn(second);
			if (cc!=NULL)
			{
				FromDeckToCardColumn(cc);
				return true;
			}

			SuitCell* sc= isSuitCell(second);
			if (sc != NULL)
			{
				FromDeckToSuitCell(sc);
				return true;

			}

		}


		CardColumn* cc1 = isLastCardInCardColumn(first);
		//CardColumn -> to CardColumn or SuitCell 
		if (cc1 != NULL)
		{
			SuitCell* sc2 = isSuitCell(second);
			if (sc2 != NULL)
			{
				FromCardColumnToSuitCell(cc1, sc2);
				return true;
			}
		}


		CardColumn* cc11 = isCardColumn(first);
		//CardColumn -> to CardColumn or SuitCell 
		if (cc11!=NULL)
		{
			//тут может быть вектор карт, надо отслеживать
			CardColumn* cc2 = isCardColumn(second);
			if (cc2 != NULL)
			{
				FromCardColumnToCardColumn(cc11,cc2,first);
				return true;
			}

		}

		SuitCell* sc1 = isSuitCell(first);

		//SuitCell -> to CardColumn 
		if (sc1!=NULL)
		{
			CardColumn* cc2 = isCardColumn(second);
			if (cc2 != NULL)
			{
				FromSuitCellToCardColumn(sc1,cc2);
				return true;

			}
		}

		return  false;
	}



	bool SolitaireGame::isGameOver()
	{
		bool result = true;
		for (int i=0;i<CELL_AMOUNT;i++)
		{
			//Если хоть одна из стопок незаполнена
			if (!suitCells[i]->IsFilled())
			{
				result = false;
				break;
			}
		}
		return result;
	}


	bool SolitaireGame::DeckClick(POINT first)
	{
		bool result = false;
		//Если первая нажатая точка попала на колоду
		if ((cardDeck->x <= first.x) && (cardDeck->x + Card::widht >= first.x) &&
			(cardDeck->y <= first.y) && (cardDeck->y + Card::height >= first.y))
		{
			cardDeck->Next();
			result = true;
		}

		return result;
	}


	SuitCell* SolitaireGame::isSuitCell(POINT point)
	{
		SuitCell* result = NULL;
		for (int i=0; i<CELL_AMOUNT;i++)
		{
			if ((suitCells[i]->x <= point.x) && (suitCells[i]->x + Card::widht >= point.x) &&
				(suitCells[i]->y <= point.y) && (suitCells[i]->y + Card::height >= point.y))
			{
				result = suitCells[i];
			}
		}
		return result;

	}

	CardColumn* SolitaireGame::isCardColumn(POINT point)
	{
		CardColumn* result = NULL;
		for (int i = 0; i < COLUMN_AMOUNT ;i++)
		{
			if ((columns[i]->x <= point.x) && (columns[i]->x + Card::widht >= point.x) &&
				(columns[i]->y <= point.y))//(columns[i]->y + Card::height* >= point.y)
			{
				result = columns[i];
			}
		}
		return result;
	}

	CardColumn* SolitaireGame::isLastCardInCardColumn(POINT point) {

		CardColumn* result = NULL;
		Card* card;
		for (int i = 0; i < COLUMN_AMOUNT;i++)
		{
			if (columns[i]->cardsInColumn.size()!=0) {
				card = columns[i]->cardsInColumn.back();
				if ((card->x <= point.x) && (card->x + Card::widht >= point.x) &&
					(card->y <= point.y) && (card->y + Card::height >= point.y))
				{
					result = columns[i];
				}
			}
		}
		return result;

	}

	bool  SolitaireGame::isCardDeck(POINT point)
	{
		int leftX = cardDeck->x + Card::widht + cardDeck->offsetX;
		int rightX = leftX + Card::widht;

		bool result = false;
		if ((leftX <= point.x) && (rightX >= point.x) &&
			(cardDeck->y <= point.y) && (cardDeck->y + Card::height >= point.y))
		{
			result = true;
		}
		return result;
	}



	bool SolitaireGame::FromDeckToSuitCell(SuitCell* cell) {

		bool result = false;

		Card* card = cardDeck->TopCard();
		
		if (card!=NULL) {
			//Если удачно положили 
			if (cell->PushCard(card)) 
			{
				cardDeck->PopCard();
				result = true;
			}
		}

		return  result;
	}

	bool SolitaireGame::FromDeckToCardColumn(CardColumn* column) {
		
		bool result = false;

		Card* card = cardDeck->TopCard();

		if (card != NULL) {

			//Если удачно положили 
			if (column->PushCard(card))
			{
				cardDeck->PopCard();
				result = true;
			}
		}

		return  result;

	}

	bool SolitaireGame::FromSuitCellToCardColumn(SuitCell* cell, CardColumn* column) {
		
	
		bool result = false;

		Card* card = cell->TopCard();

		if (card != NULL) {

			//Если удачно положили 
			if (column->PushCard(card))
			{
				cell->PopCard();
				result = true;
			}

		}

		return  result;
	}

	bool SolitaireGame::FromCardColumnToSuitCell(CardColumn* column, SuitCell* cell) {
		
		bool result = false;

		Card* card = column->TopCard();

		if (card != NULL) {

			//Если удачно положили 
			if (cell->PushCard(card))
			{
				column->PopCard();
				result = true;
			}
		}
		return  result;
	}


	//vector<Cards> 
	bool SolitaireGame::FromCardColumnToCardColumn(CardColumn* columnFrom, CardColumn* columnTo,POINT pointFrom) {	
		
		bool result = false;

		vector<Card*> cards= columnFrom->DefineCardVector(pointFrom);
		
		if (cards.size() != 0) {

			//Если удачно положили 
			if (columnTo->PushCardVector(cards))
			{
				columnFrom->PopCardVector(cards[0]);
				result = true;
			}

		}

		return  result;
	}




	// Отрисовка состояния игры
	void  SolitaireGame::DrawGameState(HWND hWnd) 
	{
		InitPaint();

		graphics->DrawImage(backgroundImage, 0, 0, WIN_WIDTH, WIN_HEIGHT);

		Card* card;
		for (int i = 0;i < CELL_AMOUNT;i++) {
			for (int j = 0;j < suitCells[i]->cards.size();j++) {
				card = suitCells[i]->cards[j];
				DrawCard(card);
			}
		}

		for (int i = 0;i < COLUMN_AMOUNT;i++) {
			for (int j = 0;j < columns[i]->cardsInColumn.size();j++) {
				card = columns[i]->cardsInColumn[j];
				DrawCard(card);
			}
		}


		card = cardDeck->GetOpenCard();
		if (card != NULL) {
			DrawCard(card);
		}

		card = cardDeck->GetClosedCard();
		if (card != NULL) {
			DrawCard(card);
		}

		ReleaseGraphicsResources();
	}
	

	void  SolitaireGame::DrawCard(Card* card)
	{
		if (card->isActive) {

			int srcX = Card::widht * (card->card_num - 1);
			int srcY = Card::height * (card->card_suit - 1);

			Gdiplus::RectF destRect(card->x, card->y, Card::widht, Card::height);

			graphics->DrawImage(activeCardImage,
				destRect,
				srcX, srcY, Card::widht, Card::height,
				Gdiplus::Unit::UnitPixel,
				NULL,
				NULL,
				NULL);

		}
		else {

			int srcX = 0;
			int srcY = 0;

			Gdiplus::RectF destRect(card->x, card->y, Card::widht, Card::height);

			graphics->DrawImage(notActiveCardImage,
				destRect,
				srcX, srcY, Card::widht, Card::height,
				Gdiplus::Unit::UnitPixel,
				NULL,
				NULL,
				NULL);

		}
	}


	void SolitaireGame::InitPaint() {

		hdc = BeginPaint(hWnd, &ps);

		memDC = CreateCompatibleDC(hdc);
		hBM = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
		oldBmp = (HBITMAP)SelectObject(memDC, hBM);
		graphics = new Gdiplus::Graphics(memDC);
		BitBlt(memDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, hdc, 0, 0, SRCCOPY);

	}

	void SolitaireGame::ReleaseGraphicsResources() {

		BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, memDC, 0, 0, SRCCOPY);
		ValidateRect(hWnd, &ps.rcPaint);
		DeleteObject(SelectObject(memDC, oldBmp));
		DeleteObject(hBM);
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		delete graphics;
	}
