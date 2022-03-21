// Lab3(4).cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab3(4).h"
#include "windows.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void gist(int x, int y, HDC& hdc, int startx, int starty) {
    COLORREF color;
    int R, G, B;
    for (int i = 0; i < y; i++) {
        int Intensity = 0;
        for (int j = 0; j < x; j++) {
            color = GetPixel(hdc,j+startx, i+starty);
            R = GetRValue(color);
            G = GetGValue(color);
            B = GetBValue(color);
            Intensity = Intensity + (R + G + B) / 3;
        }
        Intensity = Intensity / (x*5);
        MoveToEx(hdc, startx+5+x , starty+i, NULL);
        LineTo(hdc, startx+5+x+Intensity, starty+i);
    }
}
void Smoothing(int x, int y, HDC& hdc, int startx, int starty, int movex, int movey ) {
    COLORREF color, color1, color2;
    //for (int c = 0; c < y; c++) {
    //    int R = 0, G = 0, B = 0;
    //    for (int k = -1; k < 1; k++) {
    //        color = GetPixel(hdc, - k + startx, c - 1 + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //        if (k != 0) {
    //            color = GetPixel(hdc, - k + startx, c + starty);
    //            R = R + GetRValue(color);
    //            G = G + GetGValue(color);
    //            B = B + GetBValue(color);
    //        }
    //        color = GetPixel(hdc,  - k + startx, c + 1 + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //    }
    //    R = R / 5;
    //    G = G / 5;
    //    B = B / 5;
    //    color = RGB(R, G, B);
    //    SetPixel(hdc, startx + 300, c + starty, color);
    //}
    //for (int c = 0; c < y; c++) {
    //    int R = 0, G = 0, B = 0;
    //    for (int k = 0; k < 2; k++) {
    //        color = GetPixel(hdc, -k + startx+ x, c - 1 + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //        if (k != 0) {
    //            color = GetPixel(hdc, -k + startx + x, c + starty);
    //            R = R + GetRValue(color);
    //            G = G + GetGValue(color);
    //            B = B + GetBValue(color);
    //        }
    //        color = GetPixel(hdc, -k + startx + x, c + 1 + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //    }
    //    R = R / 5;
    //    G = G / 5;
    //    B = B / 5;
    //    color = RGB(R, G, B);
    //    SetPixel(hdc, startx + 300+ x, c + starty, color);
    //}
    //for (int c = 0; c < x; c++) {
    //    int R = 0, G = 0, B = 0;
    //    for (int k = -1; k < 1; k++) {
    //        color = GetPixel(hdc, c-1 + startx, -k + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //        if (k != 0) {
    //            color = GetPixel(hdc, c-1 + startx, -k + starty);
    //            R = R + GetRValue(color);
    //            G = G + GetGValue(color);
    //            B = B + GetBValue(color);
    //        }
    //        color = GetPixel(hdc, c-1 + startx, -k + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //    }
    //    R = R / 5;
    //    G = G / 5;
    //    B = B / 5;
    //    color = RGB(R, G, B);
    //    SetPixel(hdc, startx + 300 + c,  starty, color);
    //}
    //for (int c = 0; c < x; c++) {
    //    int R = 0, G = 0, B = 0;
    //    for (int k = 0; k < 2; k++) {
    //        color = GetPixel(hdc, c - 1 + startx, -k + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //        if (k != 0) {
    //            color = GetPixel(hdc, c - 1 + startx, -k + starty);
    //            R = R + GetRValue(color);
    //            G = G + GetGValue(color);
    //            B = B + GetBValue(color);
    //        }
    //        color = GetPixel(hdc, c - 1 + startx, -k + starty);
    //        R = R + GetRValue(color);
    //        G = G + GetGValue(color);
    //        B = B + GetBValue(color);
    //    }
    //    R = R / 5;
    //    G = G / 5;
    //    B = B / 5;
    //    color = RGB(R, G, B);
    //    SetPixel(hdc, startx + 300 + c, starty+ y, color);
    //}
    for (int i = 1; i < x-1; i++) {
        for (int j = 1; j < y-1; j++) {
            int R = 0, G = 0, B = 0;
            for (int k = -1; k < 2; k++) {
                color = GetPixel(hdc, i - k + startx, j-1 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);
                
                    color = GetPixel(hdc, i - k + startx, j + starty);
                    R = R + GetRValue(color);
                    G = G + GetGValue(color);
                    B = B + GetBValue(color);
      
                color = GetPixel(hdc, i - k + startx, j+1 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);
            }
            color = GetPixel(hdc, i + startx, j + starty);
            R = R - GetRValue(color);
            G = G - GetGValue(color);
            B = B - GetBValue(color);
            R = R / 8;
            G = G / 8;
            B = B / 8;
            color = RGB(R, G, B);
            SetPixel(hdc, i+movex-1, j+movey-1, color);
        }
    }
}

void Smoothing5(int x, int y, HDC& hdc, int startx, int starty, int movex, int movey) {
    COLORREF color, color1, color2;
    
    for (int i = 3; i < x - 3; i++) {
        for (int j = 3; j < y - 3; j++) {
            int R = 0, G = 0, B = 0;
            for (int k = -2; k < 3; k++) {
                color = GetPixel(hdc, i - k + startx, j - 2 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);

                color = GetPixel(hdc, i - k + startx, j - 1 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);


                color = GetPixel(hdc, i - k + startx, j + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);

                color = GetPixel(hdc, i - k + startx, j + 1 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);

                color = GetPixel(hdc, i - k + startx, j + 2 + starty);
                R = R + GetRValue(color);
                G = G + GetGValue(color);
                B = B + GetBValue(color);
            }
            color = GetPixel(hdc, i + startx, j + starty);
            R = R - GetRValue(color);
            G = G - GetGValue(color);
            B = B - GetBValue(color);
            R = R / 24;
            G = G / 24;
            B = B / 24;
            color = RGB(R, G, B);
            SetPixel(hdc, i + movex - 3, j + movey - 3, color);
        }
    }
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB34, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB34));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    // Hello world
    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB34));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB34);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, /*CW_USEDEFAULT */1920 , 1080, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBITMAP bmw = NULL;
            HDC memdc;
            bmw = (HBITMAP)LoadImage(NULL, L"OREXYS2.bmp", IMAGE_BITMAP,
                0, 0, LR_LOADFROMFILE);
            int height = 200;
            int weight = 200;
            memdc = CreateCompatibleDC(hdc);
      
            SelectObject(memdc, bmw);
            BitBlt(hdc, 0, 0, weight, height, memdc, 0, 0, SRCCOPY);
            COLORREF color;
            int R, G, B;
           
            for(int x = 0; x< weight; x++)
                for (int y = 0; y < height; y++) {
                    color = GetPixel(memdc, x, y);
                    R = (GetRValue(color) * 2);
                    if (R > 255) R = 255;
                    G = (GetGValue(color) * 2);
                    if (G > 255) G = 255;
                    B = (GetBValue(color) * 2);
                    if (B > 255) B = 255;
                    color = RGB(R,G,B);
                    SetPixel(hdc, x+weight+100 , y, color);
                }
            color = GetPixel(hdc, 20, 20);
            R = GetRValue(color) ;
           
            G = GetGValue(color);
          
            B = GetBValue(color) ;
            gist(weight, height, hdc, 0, 0);
            gist(weight, height, hdc, 100 + weight, 0);

            Smoothing(weight,height,hdc,0, 0, 0, 250);
             gist(weight-2, height-2, hdc, 0, 250);
            Smoothing(weight-2, height-2, hdc, 0, 250, weight+100,250);
            gist(weight - 4, height - 4, hdc, weight + 100, 250);
            Smoothing(weight - 4, height - 4, hdc, weight+100, 250, (weight + 100)+ weight + 100, 250);
            gist(weight - 6, height - 6, hdc, (weight + 100) + weight + 100, 250);

            Smoothing5(weight, height, hdc, 0, 0, 0, 500);
            gist(weight - 6, height - 6, hdc, 0, 500);
            Smoothing5(weight-4, height-4, hdc, 0, 500, weight+ 100, 500);
            gist(weight - 12, height - 12, hdc, weight + 100, 500);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
