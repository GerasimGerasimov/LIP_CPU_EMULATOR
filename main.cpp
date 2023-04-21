// WindowsProject1.cpp : Определяет точку входа для приложения.
//

//WindowsProject1
#include "framework.h"
#include "main.h"
#include <string> 
#include "MainPage.h"
#include <thread>
#include "mcu_main_thread.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, MainPage::szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, MainPage::szWindowClass, MAX_LOADSTRING);
    MainPage::MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!MainPage::InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    create_mcu_main_thread();

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    close_mcu_main_thread();
    return (int) msg.wParam;
}
