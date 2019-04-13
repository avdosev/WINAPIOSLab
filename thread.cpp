#include "thread.h"

#include <windows.h>

Thread::Thread()
{

}

Thread::~Thread()  {

}

void Thread::exit(uint ExitCode)  {
    _endthreadex(ExitCode);
}

unsigned WINAPI Thread::runThread(LPVOID args) {
//    auto thrd = reinterpret_cast<const Thread*>(args);
//    thrd->run();
//    emit thrd->finished;
    auto func = reinterpret_cast<std::function<void()>*>(args);
    return 0;
}

void Thread::start()  {
    thread = (HANDLE)_beginthreadex(0, NULL, &runThread, , 0, NULL);
    if (thread == NULL)
        throw std::runtime_error("ошибка стартование ядра");
}

void Thread::quit()  {

}

bool Thread::running() const  {

}

