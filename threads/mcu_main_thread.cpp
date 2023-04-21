#include "mcu_main_thread.h"
#include "os_resources.h"
#include <iostream>
#include <conio.h>
#include "app.h"
#include "msg.h"

static HANDLE hMCUMainThread = NULL;
static DWORD  dwMCUMainThreadId = 0;

DWORD WINAPI mcu_main_thread(LPVOID lpParam) {
    OSResources::init();
    (App::init())
        ? (App::run())
        : (App::error());
    return 0;
}

void create_mcu_main_thread(void) {
    DWORD dwThrdParam = 1;
    hMCUMainThread = CreateThread(
        NULL,         // атрибуты безопасности по умолчанию
        0,            // размер стека используется по умолчанию
        mcu_main_thread,   // функция потока
        &dwThrdParam, // аргумент функции потока
        0,            // флажки создания используются по умолчанию
        &dwMCUMainThreadId  // возвращает идентификатор потока
    );
}

void close_mcu_main_thread(void) {
    if (hMCUMainThread != NULL) {
        CloseHandle(hMCUMainThread);
    }
}