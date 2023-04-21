#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "framework.h"
#define MAX_LOADSTRING 100

class MainPage {
	public:
		//static void updateEmulatorView(void);
		static void fillHandlersByID(void);
		static void keyBoardControlMCU(int cmd);

		static HINSTANCE hInst;                                // текущий экземпляр
		static WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
		static WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

		static HWND hWndMain;
		static HWND hwndButton;
		static HWND hwndKeyCodeText;
		static HWND hwndDisplayEmulator;
		static HWND hwndMemoLogger;
		static HWND hwndTimer;
		static UINT IDT_TIMER1;

		static ATOM MyRegisterClass(HINSTANCE hInstance);
		static BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
		static VOID CALLBACK MyTimerProc(
			HWND hwnd,        // handle to window for timer messages 
			UINT message,     // WM_TIMER message 
			UINT idTimer,     // timer identifier 
			DWORD dwTime);     // current system time 
		static bool isHadlersFilled;
};

#endif