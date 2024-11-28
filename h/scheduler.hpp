#ifndef LUKA_RAPAIC_OS_PROJEKAT_SCHEDULER_HPP
#define LUKA_RAPAIC_OS_PROJEKAT_SCHEDULER_HPP

#include "list.hpp"

class TCB;

class Scheduler
{
private:
    static List<TCB> readyThreadQueue;

public:
    static TCB *get();

    static void put(TCB *tcb);
};

#endif //LUKA_RAPAIC_OS_PROJEKAT_SCHEDULER_HPP
