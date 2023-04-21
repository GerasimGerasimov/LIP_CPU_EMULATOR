#include "LedWarnings.h"
#include "resource.h"

HWND LedWarnings::hwnd = nullptr;
HDC LedWarnings::hdc = nullptr;
RECT LedWarnings::rect = {0,0,0,0};
HBRUSH LedWarnings::YELLOW_BRUSH = CreateSolidBrush(RGB(255, 255, 0));

static const int border = 3;
void LedWarnings::init(HWND hWndMain) {
	hwnd = GetDlgItem(hWndMain, ID_BUTTON_WRN);
	hdc = GetDC(hwnd);
	bool res = GetClientRect(hwnd, &rect);
	rect.left += border;
	rect.right -= border;
	rect.top += border;
	rect.bottom -= border;
	setState(1);

}

void LedWarnings::setState(u16 state) {
	switch (state) {
		case 0:
			FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			break;
		case 1:
			FillRect(hdc, &rect, YELLOW_BRUSH);
			break;
	};
}
