#include "sleep.h"

#ifdef _WIN32
    #include <windows.h>
    void sleepMS(uint32_t milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    void sleepMS(uint32_t milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif