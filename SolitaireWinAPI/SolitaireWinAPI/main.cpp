#include <iostream>
#include <windows.h>
#include <string>
#include "SolitaireGame.h"
#include "Generator.h"
#include "resource.h"


#define WIN_HEIGHT 610
#define WIN_WIDTH 900

#define WM_NEWGAME_BUTTON 10001

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DrawBitmap(HWND hWnd);

const CHAR* const BMP_BG_PATH = "Cards/bg_true.bmp";

HBITMAP BG_Bitmap;
HWND NewGameButton;



int WINAPI  WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)

{
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"SomeWindowClass";
    wcex.hIconSm = wcex.hIcon;

    RegisterClassEx(&wcex);


    hWnd = CreateWindow(
        L"SomeWindowClass",
        L"Solitaire",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIN_WIDTH,
        WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);


    //Кнопка ОК- которая изменяет запись после заполнения всех полей
    NewGameButton = CreateWindow(
        L"BUTTON",
        L"Новая игра",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        103,
        WIN_HEIGHT-100,
        100,
        40,
        hWnd,
        (HMENU)(WM_NEWGAME_BUTTON),
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL
    );

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

SolitaireGame* game;
POINT* point1 = NULL;
POINT* point2 = NULL;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;
    switch (message) 
    {
    case WM_CREATE:
        BG_Bitmap = (HBITMAP)LoadImageA(NULL, (LPCSTR)BMP_BG_PATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        game = new SolitaireGame();
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);

        DrawBitmap(hWnd);
        if (game!=NULL) {
            game->DrawGameState(hWnd);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN: {

        hdc = GetDC(hWnd);

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);


        if (point1 != NULL && point2 == NULL)
        {
            point2 = new POINT();
            point2->x = x;
            point2->y = y;
        }

        if (point1 == NULL)
        {
            point1 = new POINT();
            point1->x = x;
            point1->y = y;

        }


        if (game->DeckClick(*point1)) {
            point1 = NULL;
            point2 = NULL;
        }

        if (point1 != NULL && point2 != NULL) {
            game->ChangeCards(*point1,*point2);
            point1 = NULL;
            point2 = NULL;
        }

        game->DrawGameState(hWnd);

        if (game->isGameOver()) {
            MessageBoxA(
                NULL,
                "Поздравляем игра закончена. Можете начать новую нажав на кнопку новая игра.",
                "Game Over",
                MB_OK | MB_ICONINFORMATION
            );
        }

        InvalidateRect(hWnd, 0, TRUE);
        UpdateWindow(hWnd);

        break;
    }


    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);

        // Разобрать выбор в меню:
        switch (wmId)
        {
            case WM_NEWGAME_BUTTON:
            {
                delete game;
                game = NULL;

                game = new SolitaireGame();
                game->DrawGameState(hWnd);

                InvalidateRect(hWnd, 0, TRUE);
                UpdateWindow(hWnd);

                break;
            }
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void DrawBitmap(HWND hWnd)
{

    HBITMAP hbitmap = BG_Bitmap;

    BITMAP bitmap;

    GetObject(hbitmap, sizeof(bitmap), &bitmap);

    HDC winDC = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(winDC);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, hbitmap);
    RECT clientRect;

    GetClientRect(hWnd, &clientRect);

    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    StretchBlt(winDC, 0, 0,
        WIN_WIDTH, WIN_HEIGHT,
        memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

    SelectObject(memDC, oldBmp);

    DeleteDC(memDC);

    ReleaseDC(hWnd, winDC);
}