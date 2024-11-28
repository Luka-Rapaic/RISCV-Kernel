#include "../h/tcb.hpp"
#include "../h/riscv.hpp"

TCB *TCB::running = nullptr;

uint64 TCB::timeSliceCounter = 0;
uint64 TCB::idCounter = 0;

TCB *TCB::createThread(Body body, void* arg)
{
    TCB* newTCB = new TCB(body, arg);

    if (body != nullptr) { Scheduler::put(newTCB); }

    return newTCB;
}

void TCB::yield()
{
    __asm__ __volatile__ ("li a0, 0x13");
    __asm__ volatile ("ecall");
}

void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished() && !old->isBlocked()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    running->body(running->arg);
    running->setFinished(true);
    TCB::yield();
}

TCB::~TCB() {
    delete[] stack;
}
