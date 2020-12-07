#include <iostream>
#include "Card.h"


Card::Card(int suit, int num, bool _isActive,int X,int Y)
{
    card_suit = suit;
    card_num = num;
    x = X;
    y = Y;
    isActive = _isActive;
}

HBITMAP Card::hbitmapActiveCard = (HBITMAP)LoadImageA(NULL, (LPCSTR)"Cards/test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP Card::hbitmapNotActiveCard = (HBITMAP)LoadImageA(NULL, (LPCSTR)"Cards/non.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
