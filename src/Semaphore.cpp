#include "../h/Semaphore.hpp"
#include "../h/print.hpp"

uint64 SysSem::idCounter = 0;

SysSem::SysSem(uint64 init): balance(init), id(idCounter++) {}

SysSem* SysSem::openSemaphore(uint64 init) {
    SysSem* sysSem = new SysSem(init);
    return sysSem;
}
int SysSem::waitSemaphore(SysSem* sysSem) {
    sysSem->balance--;
    if (sysSem->balance < 0) {
        TCB::running->setBlocked(true);
        sysSem->waitingList.addLast(TCB::running);
        TCB::yield();
    }
    return 0;
}

int SysSem::trywaitSemaphore(SysSem* sysSem) {
    if (sysSem->balance) {
        sysSem->balance--;
        return 1;
    } else return 0;
}

int SysSem::signalSemaphore(SysSem* sysSem) {
    sysSem->balance++;
    TCB* thread = sysSem->waitingList.removeFirst();
    if(thread) {
//        printStringLR("NIT KOJA JE ODBLOKIRANA: THREAD[");
//        printIntegerLR(thread->id);
//        printStringLR("] SEMAPHORE[");
//        printIntegerLR(sysSem->id);
//        printStringLR("]\n");
        thread->setBlocked(false);
        Scheduler::put(thread);
    }
    return 0;
}

int SysSem::closeSemaphore(SysSem* sysSem) {
    while (sysSem->waitingList.peekFirst()) {
        TCB *thread = sysSem->waitingList.removeFirst();
        thread->setBlocked(false);
        Scheduler::put(thread);
    }
    return 0;
}