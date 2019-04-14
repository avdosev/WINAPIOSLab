#include "timer.h"
#include <synchapi.h>

Timer::Timer()
{

}

void Timer::start() {
    this->run = true;
    _timer_thread.start([this](){
        while (this->run) {
            Sleep(this->_time);
            if (!this->run)
                break;
            this->_callback();
        }
    });
}

void Timer::stop() {
    this->run = false;
}

void Timer::set_callback(std::function<void()> callback) {
    _callback = callback;
}

void Timer::set_time_miliseconds(unsigned time) {
    _time = time;
}
