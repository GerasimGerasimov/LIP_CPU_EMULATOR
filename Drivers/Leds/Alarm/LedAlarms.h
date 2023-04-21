//служба сообщений
#ifndef LED_ALARMS_H
#define LED_ALARMS_H

#include "stm32f4xx.h"
#include <Windows.h>

class LedAlarms {
	public:
		static void init(HWND hWndMain);
		static void setState(u16 state);
	private:
		static HWND hwnd;
		static HDC hdc;
		static RECT rect;
		static HBRUSH RED_BRUSH;
};

#endif