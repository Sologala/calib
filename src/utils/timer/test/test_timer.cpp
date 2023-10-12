#include <unistd.h>

#include "iostream"
#include "timer.hpp"
int main() {
    // do sth
    while (1) {
        {
            MyTimer::Timer _("sleep");
            usleep(10000);
        }

        std::cout << MyTimer::Timer::COUNT["sleep"].ns() << "ns\t" << MyTimer::Timer::COUNT["sleep"].ms() << "ms\t"
                  << MyTimer::Timer::COUNT["sleep"].s() << "s\t" << MyTimer::Timer::COUNT["sleep"].fps() << "fps\t"
                  << std::endl;
    }

    return 0;
}