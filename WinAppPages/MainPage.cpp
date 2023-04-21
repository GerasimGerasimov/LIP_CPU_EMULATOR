#include "MainPage.h"
#include "resource.h"
#include <string> 
#include "display_driver.h"
#include "consolelog.h"
#include "msg.h"
#include <com_master_driver.h>
#include "LedAlarms.h"
#include "LedWarnings.h"
#include "internal_din.h"

HINSTANCE MainPage::hInst = NULL;                                // текущий экземпл€р
WCHAR MainPage::szTitle[MAX_LOADSTRING];                  // “екст строки заголовка
WCHAR MainPage::szWindowClass[MAX_LOADSTRING];            // им€ класса главного окна

HWND MainPage::hWndMain = NULL;
HWND MainPage::hwndButton = NULL;
HWND MainPage::hwndKeyCodeText = NULL;
HWND MainPage::hwndDisplayEmulator = NULL;
HWND MainPage::hwndMemoLogger = NULL;
HWND MainPage::hwndTimer = NULL;
UINT MainPage::IDT_TIMER1 = 0;
bool MainPage::isHadlersFilled = false;

//
//  ‘”Ќ ÷»я: MyRegisterClass()
//
//  ÷≈Ћ№: –егистрирует класс окна.
//
ATOM MainPage::MyRegisterClass(HINSTANCE hInstance)
{
    TGraphics::init();
    
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra =  DLGWINDOWEXTRA;//0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = (LPCWSTR)L"MainWndClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
};

//
//   ‘”Ќ ÷»я: InitInstance(HINSTANCE, int)
//
//   ÷≈Ћ№: —охран€ет маркер экземпл€ра и создает главное окно
//
//    ќћћ≈Ќ“ј–»»:
//
//        ¬ этой функции маркер экземпл€ра сохран€етс€ в глобальной переменной, а также
//        создаетс€ и выводитс€ главное окно программы.
//
BOOL MainPage::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // —охранить маркер экземпл€ра в глобальной переменной

    hWndMain = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, (DLGPROC)WndProc);
    if (!hWndMain)
    {
        return FALSE;
    };

    SetTimer(hWndMain,             // handle to main window 
        IDT_TIMER1,            // timer identifier 
        100,                 // 10-second interval 
        (TIMERPROC)MyTimerProc);     // no timer callback 

    ShowWindow(hWndMain, nCmdShow);
    UpdateWindow(hWndMain);

    return TRUE;
}

static UINT COUNT = 0;
VOID CALLBACK MainPage::MyTimerProc(
    HWND hwnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{
    Msg::send_message((u32)EventSrc::TIMER, 0, 0);
    //console::log(L"TIMER\n");
}

void MainPage::fillHandlersByID(void) {
    if (isHadlersFilled) return;
    hwndDisplayEmulator = GetDlgItem(hWndMain, ID_DISPLAY_EMULATOR);
    HDC hdc_dem = GetDC(hwndDisplayEmulator);
    TDisplayDriver::setDC(hdc_dem);
    console::hwnd = hwndMemoLogger = GetDlgItem(hWndMain, ID_MEMO_LOGGER);
    LedAlarms::init(hWndMain);
    LedWarnings::init(hWndMain);
    InternalDIN::init();
    isHadlersFilled = true;
    ComMasterDriver::open();
}

//  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ÷≈Ћ№: ќбрабатывает сообщени€ в главном окне.
//  WM_COMMAND  - обработать меню приложени€
//  WM_PAINT    - ќтрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернутьс€

LRESULT CALLBACK MainPage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    u16 x = 0;
    switch (message)
    {
    case WM_CREATE:

        break;
    case WM_SHOWWINDOW:
        fillHandlersByID();
        break;

    case WM_COMMAND:
    {
        if (lParam == (LPARAM)hwndButton) {
            //обработка нажати€ кнопки
            MessageBox(hWnd, (LPCWSTR)L"You pressed my button", (LPCWSTR)L"MessageBox", MB_OK | MB_ICONWARNING);
            return 0;
        }

        int wmId = LOWORD(wParam);
        keyBoardControlMCU(wmId);
        DINControlMCU(wmId);
        // –азобрать выбор в меню:
        switch (wmId)
        {
        case ID_BUTTON_CLEAR: 
            console::clear();
            console::log(L"ID_BUTTON_CLEAR\n");
            break;
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


void MainPage::DINControlMCU(int cmd) {
    switch (LOWORD(cmd)) {
    case IDC_CHECK_DI0:
        setDIN(IDC_CHECK_DI0, 0);
        break;
    case IDC_CHECK_DI1:
        setDIN(IDC_CHECK_DI1, 1);
        break;
    case IDC_CHECK_DI2:
        setDIN(IDC_CHECK_DI2, 2);
        break;
    case IDC_CHECK_DI3:
        setDIN(IDC_CHECK_DI3, 3);
        break;
    case IDC_CHECK_DI4:
        setDIN(IDC_CHECK_DI4, 4);
        break;
    case IDC_CHECK_DI5:
        setDIN(IDC_CHECK_DI5, 5);
        break;
    }
    
}

void MainPage::setDIN(int ID, int input_number) {
    if (SendDlgItemMessage(hWndMain, ID, BM_GETCHECK, 0, 0)) {
        InternalDIN::DIN |= (1 << input_number);
        console::log(L"DIN CHECKED\n");
    }
    else {
        InternalDIN::DIN &= ~(1 << input_number);
        console::log(L"DIN0 UNCHECKED\n");
    }
}

void MainPage::keyBoardControlMCU(int cmd) {
    switch (LOWORD(cmd)) {
        case ID_BUTTON_F1 : 
            console::log(L"ID_BUTTON_F1\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::F1, 0);
            break;
        case ID_BUTTON_F2:
            console::log(L"ID_BUTTON_F2\n");
            break;
        case ID_BUTTON_F3:
            console::log(L"ID_BUTTON_F3\n");
            break;
        case ID_BUTTON_ESC:
            console::log(L"ID_BUTTON_ESC\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::ESC, 0);
            break;
        case ID_BUTTON_UP:
            console::log(L"ID_BUTTON_UP\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::Up, 0);
            break;
        case ID_BUTTON_OK:
            console::log(L"ID_BUTTON_OK\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::ENT, 0);
            break;
        case ID_BUTTON_LEFT:
            console::log(L"ID_BUTTON_LEFT\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::Left, 0);
            break;
        case ID_BUTTON_DOWN:
            console::log(L"ID_BUTTON_DOWN\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::Down, 0);
            break;
        case ID_BUTTON_RIGHT:
            console::log(L"ID_BUTTON_RIGHT\n");
            Msg::send_message((u32)EventSrc::KEYBOARD, (u32)KeyCodes::Right, 0);
            break;
    }
}

// ќбработчик сообщений дл€ окна "ќ программе".
INT_PTR CALLBACK MainPage::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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