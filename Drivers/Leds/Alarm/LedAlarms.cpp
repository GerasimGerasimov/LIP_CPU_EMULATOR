#include "LedAlarms.h"
#include "resource.h"

HWND LedAlarms::hwnd = nullptr;
HDC LedAlarms::hdc = nullptr;
RECT LedAlarms::rect = {0,0,0,0};
HBRUSH LedAlarms::RED_BRUSH = CreateSolidBrush(RGB(255,0,0));

const int border = 3;
void LedAlarms::init(HWND hWndMain) {
	hwnd = GetDlgItem(hWndMain, ID_BUTTON_ALR);
	hdc = GetDC(hwnd);
	bool res = GetClientRect(hwnd, &rect);
	rect.left += border;
	rect.right -= border;
	rect.top += border;
	rect.bottom -= border;
	setState(1);

}

void LedAlarms::setState(u16 state) {
	switch (state) {
		case 0:
			FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			break;
		case 1:
			FillRect(hdc, &rect, RED_BRUSH);
			break;
	};
}
