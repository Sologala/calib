#ifndef TIMMER_H
#define TIMMER_H
#include <chrono>
#include <deque>
#include <string>
#include <unordered_map>
#pragma once
namespace MyTimer {
#define TIMER_COUNT_QUEEN_MAX_SIZE 20
class Time_count {
   public:
    Time_count() {}
    Time_count(const double _duration) { update(_duration); }
    ~Time_count(){};

    void update(const double _duration) {
        _queue.push_back(_duration);
        dur_sum += _duration;
        while (_queue.size() > TIMER_COUNT_QUEEN_MAX_SIZE) {
            dur_sum -= _queue.front();
            _queue.pop_front();
        }
        avg_duration = (dur_sum / _queue.size());
    }

    double s() { return avg_duration; }
    double ms() { return avg_duration * 1000; }
    double ns() { return avg_duration * 1000 * 1000; }
    double fps() { return 1. / (0.0000001 + avg_duration); }

   private:
    std::deque<double> _queue;
    double dur_sum{0};
    double avg_duration;
};

class Timer {
   public:
    Timer(const std::string &_name);
    ~Timer();

    void tick();
    void tock();

    bool is_manualy = false;
    const std::string name;
    static std::unordered_map<std::string, Time_count> COUNT;
    std::chrono::steady_clock::time_point testTime_t1, testTime_t2;
};
}  // namespace MyTimer
#endif