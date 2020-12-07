#include <iostream>
#include <windows.h>
#include <string>
#include "SolitaireGame.h"
#include "Generator.h"
#include "resource.h"


#define WIN_HEIGHT 610
#define WIN_WIDTH 900

#define ID_BUTTON_NEWGAME 2001
#define ID_BUTTON_EXIT 2002

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const CHAR* const BMP_BG_PATH = "Cards/bg_true.bmp";
void CreateProgramMenu(HWND hwnd);


int WINAPI  WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)

{
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;


    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);


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


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
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
    case WM_CREATE: {

        CreateProgramMenu(hWnd);
        game = new SolitaireGame(hWnd);
        break;
    }
    case WM_ERASEBKGND:
    {
        return (LRESULT)1; // Say we handled it.
    }
    case WM_PAINT: {


        if (game!=NULL) {
            game->DrawGameState(hWnd);
        }

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
            case ID_BUTTON_NEWGAME:
            {
                delete game;
                game = NULL;

                game = new SolitaireGame(hWnd);
                game->DrawGameState(hWnd);

                InvalidateRect(hWnd, 0, TRUE);
                UpdateWindow(hWnd);

                break;
            }
            case ID_BUTTON_EXIT:
            {
                PostQuitMessage(0);
                break;
            }
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);

    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void CreateProgramMenu(HWND hwnd)
{
    HMENU mainMenu = CreateMenu();
    HMENU figuresPopupMenu = CreatePopupMenu();

    AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT)figuresPopupMenu, L"Menu");
    {
        AppendMenu(figuresPopupMenu, MF_STRING, ID_BUTTON_NEWGAME, L"New Game");
        AppendMenu(figuresPopupMenu, MF_SEPARATOR, NULL, NULL);
        AppendMenu(figuresPopupMenu, MF_STRING, ID_BUTTON_EXIT, L"Exit");
        AppendMenu(figuresPopupMenu, MF_SEPARATOR, NULL, NULL);
    }

    SetMenu(hwnd, mainMenu);
}