#include <iostream>
#include <windows.h>
#include <string>
#include "SolitaireGame.h"
#include "Generator.h"


#define WIN_HEIGHT 610
#define WIN_WIDTH 900

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DrawBitmap(HWND hWnd);

HBRUSH brush = CreateSolidBrush(RGB(80, 150, 100)); // Зеленая кисть для фона


const CHAR* const BMP_PATH = "Cards/test.bmp";
const CHAR* const BMP_BG_PATH = "Cards/bg.bmp";

HBITMAP h1Bitmap;
HBITMAP BG_Bitmap;
bool isLeftButtonDown = false;

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
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"SomeWindowClass";
    wcex.hIconSm = wcex.hIcon;

    RegisterClassEx(&wcex);


    hWnd = CreateWindow(
        L"SomeWindowClass",
        L"Some Window",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIN_WIDTH,
        WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

SolitaireGame* game;
Card* card1;
Card* card2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;
    switch (message) 
    {
    case WM_CREATE:
        h1Bitmap = (HBITMAP)LoadImageA(NULL, (LPCSTR)BMP_PATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BG_Bitmap = (HBITMAP)LoadImageA(NULL, (LPCSTR)BMP_BG_PATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        game = new SolitaireGame();
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        //FillRect(ps.hdc, &ps.rcPaint, brush);

        DrawBitmap(hWnd);
        game->DrawGameState(hWnd); 

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN: {

        hdc = GetDC(hWnd);

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        cout << "x " << x << "y " << y << endl;

        card1 = game->CheckCollisions(x, y);
        if (card1==NULL) 
        {
            MessageBox(NULL,L"no", L"Both NULL " ,MB_OK);
            game->fromCard = NULL;
            game->toCard = NULL;        
        }
        else 
        {
            if (game->fromCard == NULL) { game->fromCard = card1; MessageBox(NULL, L"yes", L"first card init", MB_OK); }
            else if (game->fromCard != NULL) {
                game->toCard == card1;
                MessageBox(NULL, L"yes", L"both card init", MB_OK);
                //действия и потом занулить обе карты
                game->fromCard = NULL;
                game->toCard = NULL;
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