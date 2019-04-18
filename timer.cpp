#include "timer.h"
#include <synchapi.h>
#include <QDebug>

Timer::Timer()
{

}

void Timer::start() {
    this->run = std::make_shared<bool>(true);
    // строки ниже необходимы для захвата перменных, тк захватить поля класса стандарт с++ не позволяет
    // либо использовать синтаксически засахаренную версию того же самого но в версии с++14
    auto _callback = this->_callback;
    auto _time = this->_time;
    auto run = this->run;
    _timer_thread.start([_callback,_time, run](){
        while (*run) {
            Sleep(_time);
            if (!*run)
                break;
            _callback();
            qDebug() << "timer tick";
        }
    });
}

void Timer::stop() {
    if (run != nullptr)
        *this->run = false;
}

void Timer::set_callback(std::function<void()> callback) {
    _callback = callback;
}

void Timer::set_time_miliseconds(unsigned time) {
    _time = time;
}
