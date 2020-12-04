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

// »щет по координатом точки, на которую мышью
// нажал пользователь, соотв. карту, если такой нет вернет null
Card* Card::CheckCollision(int X, int Y, Card* card)
{   
    std::cout << "real x " << x <<"|"<< this->x+this->widht << " real y " << y<<"|"<< this->y+ this->height<< std::endl;
    std::cout << " x " << X << " y " << Y << std::endl;
    if (card == NULL) {
        if ((this->x <= X) && (this->x + this->widht >= X) && (this->y <= Y) && (this->y + this->height >= Y))
        {
            card = this;
        }
    }
    return card;
}

void Card::DrawCard(HWND hWnd)
{
    if (this->isActive) 
        DrawActiveCard(hWnd);
    else
        DrawNotActiveCard(hWnd);
}

void Card::DrawActiveCard(HWND hWnd)
{

    HBITMAP hbitmap = hbitmapActiveCard;

    BITMAP bitmap;

    GetObject(hbitmap, sizeof(bitmap), &bitmap);

    HDC winDC = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(winDC);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hbitmap);
    RECT clientRect;

    //‘ункци€ GetClientRect извлекает координаты рабочей области окна.
    //–абочие координаты определ€ют левый верхний и нижний правый углы рабочей области. 
    GetClientRect(hWnd, &clientRect);


    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    /*‘ункци€ StretchBlt копирует точечный рисунок из
    исходного пр€моугольника в целевой пр€моугольник,
    раст€гива€ или сжима€ его, чтобы, в случае необходимости,
    подогнать под  размеры целевого пр€моугольника.
    —истема раст€гивает или сжимает точечный рисунок согласно режиму раст€жени€,
    который в текущий момент установлен в приемном контексте устройства.*/

    StretchBlt(winDC, x, y,
        this->widht, this->height,
        memDC, this->widht * (this->card_num - 1), this->height * (this->card_suit - 1),
        bitmap.bmWidth / 13, bitmap.bmHeight / 4, SRCCOPY);

    SelectObject(memDC, oldBmp);

    DeleteDC(memDC);

    ReleaseDC(hWnd, winDC);
}

void Card::DrawNotActiveCard(HWND hWnd)
{

    HBITMAP hbitmap = hbitmapNotActiveCard;

    BITMAP bitmap;

    GetObject(hbitmap, sizeof(bitmap), &bitmap);

    HDC winDC = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(winDC);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hbitmap);
    RECT clientRect;

    GetClientRect(hWnd, &clientRect);

    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    StretchBlt(winDC, x, y,
        this->widht, this->height,
        memDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

    SelectObject(memDC, oldBmp);

    DeleteDC(memDC);

    ReleaseDC(hWnd, winDC);
}

