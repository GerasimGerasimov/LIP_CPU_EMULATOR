#include "key_board_thread.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include "msg.h"
#include "graphics.h"
#include "mutexes.h"

void key_out_log(int key) {
    HANDLE console = TGrahics::get_console();
    mu.lock();
    SetConsoleTextAttribute(console, 15);// FOREGROUND_INTENSITY);
    COORD start = { 20, 0 };
    ::SetConsoleCursorPosition(console, start);
    std::cout << "key:" << key << "\n";
    send_message(KEYBOARD, key, 0);
    mu.unlock();
}

void key_board_control() {
    int key = 0;

    do {
        key = _getch_nolock();
        //key_out_log(key);
    } while (key != 8);
    std::cout << "Leave the Thread!\n";
}