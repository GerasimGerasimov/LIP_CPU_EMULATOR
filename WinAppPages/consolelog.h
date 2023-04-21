#ifndef CONSOLE_LOG_H
#define CONSOLE_LOG_H

//#include "framework.h"
#include <Windows.h>
#include <string> 

class console {
	public:
		static HWND hwnd;
		static void log(std::wstring text);
		static void log(std::string text);
		static void clear(void);
};

#endif