#include "com_master_driver.h"

HANDLE ComMasterDriver::hCom = NULL;
HANDLE ComMasterDriver::hComThread = NULL;
DWORD  ComMasterDriver::dwComThreadId = 0;
TDriverComReadEndHandler ComMasterDriver::onReadEdnd = nullptr;
u8* ComMasterDriver::outbuf = NULL;
u16 ComMasterDriver::OutBufLen = 0;
u16 ComMasterDriver::DelayAfterWrite = 0;
u8 ComMasterDriver::reply[256];

void ComMasterDriver::send(TComMasterTask task) {
    onReadEdnd = task.callback;
    outbuf = task.pbuff;
    OutBufLen = task.len;
    DelayAfterWrite = task.DelayAfterWrite;
    ::ResumeThread(hComThread);
}

DWORD WINAPI ComMasterDriver::com_thread(LPVOID lpParam) {
    DWORD ButesToRead;
    DWORD Count;
    DWORD fSuccess;
    while (true) {
        fSuccess = WriteFile(hCom, outbuf, OutBufLen, &Count, NULL);
        Sleep(DelayAfterWrite);// p.SleepAfterWrite);
        ButesToRead = 256;
        fSuccess = ReadFile(hCom, &reply, ButesToRead, &Count, NULL);
        s16 result = (fSuccess > 0) ? Count : -1;
        if (onReadEdnd) onReadEdnd(result, reply);
        ::SuspendThread(hComThread);
    }
    return 0;
}


void ComMasterDriver::open() {
    
    DCB dcb;
    COMMTIMEOUTS CommTimeouts;
    DWORD fSuccess = 0;
    LPCTSTR pcCommPort = TEXT("COM3");

	hCom = CreateFile(pcCommPort,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING,
        0);
    if (hCom != INVALID_HANDLE_VALUE) {
        fSuccess = GetCommTimeouts(hCom, &CommTimeouts);

        SecureZeroMemory(&dcb, sizeof(DCB));
        fSuccess = GetCommState(hCom, &dcb);

        dcb.DCBlength = sizeof(DCB);
        dcb.BaudRate = CBR_115200;
        dcb.Parity = NOPARITY;
        dcb.ByteSize = 8;
        dcb.StopBits = ONESTOPBIT;
        fSuccess = SetCommState(hCom, &dcb);

        CommTimeouts.ReadIntervalTimeout = 20;//chartimeout;
        CommTimeouts.ReadTotalTimeoutMultiplier  = 0;
        CommTimeouts.ReadTotalTimeoutConstant    = 500;
        CommTimeouts.WriteTotalTimeoutMultiplier = 0;
        CommTimeouts.WriteTotalTimeoutConstant   = 0;
        fSuccess = SetCommTimeouts(hCom, &CommTimeouts);
    }
    create_com_thread();
}

void ComMasterDriver::close() {
    PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    if (WaitForSingleObject(hComThread, 500) == WAIT_TIMEOUT)
       TerminateThread(hComThread, 0);
    CloseHandle(hCom);
}

void ComMasterDriver::create_com_thread(void) {
    DWORD dwThrdParam = 1;
    hComThread = CreateThread(
        NULL,         // атрибуты безопасности по умолчанию
        0,            // размер стека используется по умолчанию
        com_thread,   // функция потока
        &dwThrdParam, // аргумент функции потока
        CREATE_SUSPENDED,            // флажки создания используются по умолчанию
        &dwComThreadId  // возвращает идентификатор потока
    );
}