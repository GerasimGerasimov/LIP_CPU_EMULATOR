#include "display_driver.h"
#include <iostream>

HDC TDisplayDriver::dc = NULL;
HBRUSH TDisplayDriver::Br_Light = NULL;
HBRUSH TDisplayDriver::Br_Empty = NULL;

HBITMAP TDisplayDriver::b = NULL;
HDC TDisplayDriver::memDC = NULL;

void TDisplayDriver::setDC(HDC _dc) {
	dc = _dc;
    Br_Light = CreateSolidBrush(LIGHT_COLOR);
    Br_Empty = CreateSolidBrush(EPMTY_COLOR);
    b = CreateCompatibleBitmap(dc,
        VIEW_PORT_MAX_WIDTH * DISPLAY_DRRIVER_SCALE,
        VIEW_PORT_MAX_HEIGHT * DISPLAY_DRRIVER_SCALE);
    memDC = CreateCompatibleDC(dc);
    SelectObject(memDC, b);
}

u8 framebuffer[8][128]; //для передачи по SPI 

const static u8 Mask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void TDisplayDriver::prepareFrame(void) {
    u8 p = 0;
    u8* f = &framebuffer[0][0];
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 64; y++) {
            p = TGraphics::screen[x][y];
            u16 PixNum = (y << 7) + x; //номер пиксела в одномерном массиве, что переводится как Y*128 + X
            u16 ByteNum = PixNum >> 3;;//номер байта в двухмерном массиве  что переводится как PixNum/8
            u8 BitMask = Mask[PixNum - (ByteNum << 3)];//маска для бита
            u8* a = f + ByteNum;
            (p)
                ? (*a |= BitMask)
                : (*a &= ~BitMask);
            a = 0;
        }
    }
}

void TDisplayDriver::out(void) {
    //prepareFrame();
    if (dc == NULL) return;
    RECT r;
    HBRUSH br = Br_Empty;
    for (int y = 0; y < VIEW_PORT_MAX_HEIGHT; y++) {
        for (int x = 0; x < VIEW_PORT_MAX_WIDTH; x++) {
            br = (TGraphics::screen[x][y] != 0)
                ? Br_Light
                : Br_Empty;
            r.left = x * DISPLAY_DRRIVER_SCALE;
            r.top = y * DISPLAY_DRRIVER_SCALE;
            r.right = r.left + DISPLAY_DRRIVER_SCALE;
            r.bottom = r.top + DISPLAY_DRRIVER_SCALE;
            FillRect(memDC, &r, br);
        }
    };
    BitBlt(dc, 0, 0, 
        VIEW_PORT_MAX_WIDTH * DISPLAY_DRRIVER_SCALE,
        VIEW_PORT_MAX_HEIGHT * DISPLAY_DRRIVER_SCALE,
        memDC, 0, 0,
    SRCCOPY);
};