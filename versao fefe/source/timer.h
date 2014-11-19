#ifndef __timer__
#define __timer__

#include <iostream>

class Timer {
    int cont, max;
public:
    Timer(int m) : cont(0), max(m) {}
    bool tick() { cont++; if (cont < max) return true; else return false; }
    void reboot() { cont = 0; }
    int time_remaining() { return max - cont; }
};

#endif
