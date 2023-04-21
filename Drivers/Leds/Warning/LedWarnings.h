//служба сообщений
#ifndef LED_WARNINGS_H
#define LED_WARNINGS_H

#include "stm32f4xx.h"
#include <Windows.h>

class LedWarnings {
	public:
		static void init(HWND hWndMain);
		static void setState(u16 state);
	private:
		static HWND hwnd;
		static HDC hdc;
		static RECT rect;
		static HBRUSH YELLOW_BRUSH;
};

#endif