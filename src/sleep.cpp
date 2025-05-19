#include "sleep.h"
#include <chrono>
#include <thread>

extern "C" void sleepMS(uint64_t milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

extern "C" void sleepNS(uint64_t nanoseconds) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
}