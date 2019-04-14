#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <thread.h>

class Timer
{
    private:
        Thread _timer_thread;
        std::function<void()> _callback;
        unsigned _time = 1000;
        bool run;
    public:
        Timer();
        void set_callback(std::function<void()> callback);
        void set_time_miliseconds(unsigned time_ms);
        void start();
        void stop();
};

#endif // TIMER_H
