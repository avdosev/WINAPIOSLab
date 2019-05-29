#include "thread.h"

#include <windows.h>

Thread::Thread()
{
    thread = NULL;
}

Thread::~Thread()  {

}

void Thread::sleep(unsigned mls) {
    Sleep(mls);
}

unsigned WINAPI Thread::runThread(LPVOID args) {
//    auto thrd = reinterpret_cast<const Thread*>(args);
//    thrd->run();
//    emit thrd->finished;
    auto func_ptr = reinterpret_cast<std::function<void()>*>(args);
    std::function<void()> func = *func_ptr;
    delete func_ptr;
    func();
    _endthreadex(0);
}

void Thread::start(std::function<void()> func)  {
    void* FuncArg = new std::function<void()>(func);
    thread = (HANDLE)_beginthreadex(0, NULL, &runThread, FuncArg, 0, NULL);
    if (thread == NULL) {
        delete (std::function<void()>*)FuncArg; // если поток не работает то мы должны корректно удалить этот участок иначе произойдет утечка памяти
        throw std::runtime_error("ошибка стартование ядра");
    }
}

void Thread::quit() {
    CloseHandle(thread);
}

bool Thread::running() const  {
    return WaitForSingleObject(thread, 10) == WAIT_TIMEOUT;
}

//void Thread::make_signal_started() const {
//    emit started();
//}
//void Thread::make_signal_finished() const {

//}

