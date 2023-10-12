#include "timer.hpp"

namespace MyTimer {
std::unordered_map<std::string, Time_count> MyTimer::Timer::COUNT = std::unordered_map<std::string, Time_count>();

Timer::Timer(const std::string &_name) : name(_name) { testTime_t1 = std::chrono::steady_clock::now(); }

Timer::~Timer() {
    if (is_manualy == false){
        testTime_t2 = std::chrono::steady_clock::now();
        double duration_ns = std::chrono::duration_cast<std::chrono::duration<double> >(testTime_t2 - testTime_t1).count();
        if (COUNT.count(name) != 0) {
            COUNT[name].update(duration_ns);
        } else {
            COUNT[name] = Time_count(duration_ns);
        }
    }
}

void Timer::tick(){
    testTime_t1 = std::chrono::steady_clock::now(); 
}
void Timer::tock(){
    is_manualy = true;
    testTime_t2 = std::chrono::steady_clock::now();
    double duration_ns = std::chrono::duration_cast<std::chrono::duration<double> >(testTime_t2 - testTime_t1).count();
    if (COUNT.count(name) != 0) {
        COUNT[name].update(duration_ns);
    } else {
        COUNT[name] = Time_count(duration_ns);
    }
}

}  // namespace MyTimer