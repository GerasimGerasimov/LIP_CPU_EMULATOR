#include "consolelog.h"

HWND console::hwnd = nullptr;

void console::log(std::wstring text) {
    if (hwnd == nullptr) return;
    int strLen = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
    SendMessage(hwnd, EM_SETSEL, (WPARAM)strLen, (LPARAM)strLen);    
    SendMessage(hwnd, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)text.c_str());
}

void console::log(std::string text) {
    std::wstring wstr(text.begin(), text.end());
    console::log(wstr);
}

void console::clear(void) {
    SetWindowText(hwnd, 0);
}
