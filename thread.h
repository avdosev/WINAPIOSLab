#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <windef.h>
#include <functional>

class Thread : QObject
{
        Q_OBJECT
    private:
        HANDLE thread;
        static unsigned __stdcall runThread(void* args);
    public:
        Thread();
        ~Thread();
        void exit(uint ExitCode = 0);
        bool running() const;
        bool wait(unsigned long time = ULONG_MAX);

    public slots:
        void quit(); // сообщает потоку завершиться с кодом ноль
        void start(std::function<void()> func); // старт потока
    signals:
        void started(); // сигнал испускаемый после старта потока
        void finished(); // по окончании потока
    protected:
        //virtual void run() const = 0; // функция которая запускается в отдельном потоке
        // почему виртуальная? потому что я так захотел
        // возможно в будущем я изменю интерфейс под функциональный стайл
        // кстате это интересный варик
};

#endif // THREAD_H
