#ifndef LUKA_RAPAIC_OS_PROJEKAT_TCB_HPP
#define LUKA_RAPAIC_OS_PROJEKAT_TCB_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"
class SysSem;

// Thread Control Block
class TCB
{
public:
    ~TCB();

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    uint64 getTimeSlice() const { return timeSlice; }

    using Body = void (*)(void*);

    static TCB *createThread(Body body, void* arg);

    static void yield();

    static TCB *running;

    static void exit() {
        running->setFinished(true);
    }

    bool isBlocked() const { return blocked; }
    void setBlocked(bool value) { blocked = value; }

    static int getThreadId();

    uint64 id = idCounter++;
private:
    TCB(Body body, void* arg, uint64 timeSlice = 2) :
            body(body),
            arg(arg),
            stack(body != nullptr ? new uint64[STACK_SIZE] : nullptr),
            context({(uint64) &threadWrapper,
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            timeSlice(timeSlice),
            finished(false),
            blocked(false)
    {}

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    void* arg;
    uint64 *stack;
    Context context;
    uint64 timeSlice;
    bool finished;
    bool blocked;

    friend class Riscv;

    static void threadWrapper();

    static void contextSwitch(Context *oldContext, Context *runningContext);

    static void dispatch();

    static uint64 timeSliceCounter;
    static uint64 idCounter;

    static uint64 constexpr STACK_SIZE = 1024;
    static uint64 constexpr TIME_SLICE = 2;
};

#endif //LUKA_RAPAIC_OS_PROJEKAT_TCB_HPP
