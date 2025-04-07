
#include "../inc/gic.h"
#include "../inc/mmu.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include "../inc/memcpy.h"


void board_init(void);

__attribute__((section(".kernel_text"))) void board_init(void)
{
    __scheduler_init();
    __gic_init();
    __mmu_init();
    __timer_init();
    // inicializo el contexto de tareas

    // inicializo interrupciones con esta linea
    asm("cpsie i");  

    __tarea_idle();
}

//extern const void 