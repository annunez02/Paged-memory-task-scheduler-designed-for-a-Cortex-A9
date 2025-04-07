
#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"


void board_init(void);

__attribute__((section(".text"))) void board_init(void)
{
    __mmu_init();
    // __scheduler_init();
    //__gic_init();
    //__timer_init();
    // inicializo el contexto de tareas
}
