#include "timer_thread.h"

#include "stm32f4xx.h"
#include <iostream>
#include <windows.h>
#include "msg.h"
#include "graphics.h"
#include "mutexes.h"

void timer_out_log(u16 count) {
    mu.lock();
    HANDLE console = TGrahics::get_console();
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    COORD start = { 0, 0 };
    ::SetConsoleCursorPosition(console, start);
    std::cout << "time:" << count++ << "\n";
    mu.unlock();
}

void timer_control() {
    u16 count = 0;
    
    while (true) {
        //timer_out_log(count++);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}