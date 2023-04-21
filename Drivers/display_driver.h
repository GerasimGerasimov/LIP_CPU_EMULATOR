#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H_H

#include <string>
#include <vector>
#include "stm32f4xx.h"
#include <windows.h>
#include "graphics.h"

#define LIGHT_COLOR  RGB(0, 150, 100)//1
#define EPMTY_COLOR  RGB(0, 0, 0)  //0

#define DISPLAY_DRRIVER_SCALE 2

struct TDisplayDriver {
	public:
		static void setDC(HDC _dc);
		static void out(void);
	private:
		static HDC dc;
		static HBRUSH Br_Light;
		static HBRUSH Br_Empty;
		static HBITMAP b;
		static HDC memDC;
		static void prepareFrame(void);
};

#endif
