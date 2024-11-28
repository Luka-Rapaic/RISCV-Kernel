#ifndef LUKA_RAPAIC_OS_PROJEKAT_SEMAPHORE2_HPP
#define LUKA_RAPAIC_OS_PROJEKAT_SEMAPHORE2_HPP

#include "../lib/hw.h"
#include "tcb.hpp"

class SysSem {
public:
    static SysSem* openSemaphore(uint64 init);
    static int closeSemaphore(SysSem* sysSem);
    static int waitSemaphore(SysSem* sysSem);
    static int trywaitSemaphore(SysSem* sysSem);
    static int signalSemaphore(SysSem* sysSem);

private:
    SysSem(uint64 init);

    List <TCB> waitingList;
    int balance;

    uint64 id;
    static uint64 idCounter;
};

#endif //LUKA_RAPAIC_OS_PROJEKAT_SEMAPHORE2_HPP
