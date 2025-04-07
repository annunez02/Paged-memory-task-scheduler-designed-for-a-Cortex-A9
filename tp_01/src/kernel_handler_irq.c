#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include <stddef.h>
#include <stdint.h>

typedef struct context_t
{
    uint32_t SP, SPSR, GPR[13], LR;
}context_t;

__attribute__((section(".text"))) uint32_t kernel_handler_irq(context_t* context);

__attribute__((section(".text"))) uint32_t kernel_handler_irq(context_t* context)
{
    _gicc_t* const GICC0 = (_gicc_t*)GICC0_ADDR;
    _timer_t* const TIMER01 = (_timer_t*)TIMER01_ADDR;
   
    uint32_t id = 0x00000000;

    id = GICC0->IAR & 0x000001FF;

    switch (id) //analizo quien me interrumpio
    {
    case GIC_SOURCE_TIMER01:

        if (TIMER01->Timer1RIS & 0x01) // me fijo si esta en 1 el timer 0
        {   
            scheduler_c();
            TIMER01->Timer1IntClr = 0x01; //limpio las interrupciones
        }
        else if (TIMER01->Timer2RIS & 0x01) // me fijo si esta en 1 el timer 1
        {
            TIMER01->Timer2IntClr = 0x01; //limpio las interrupciones
        }
        
        break;
    
    default:
        break;
    }


    /*
        .equ IRQ_MODE, 0x12
        .equ SVC_MODE, 0x13
    */

    if (task_switch == 1)
    {
        asm("CPS #0x13");
        asm("LDR SP, %0" : "=m" (tcb_tareas[current_task].SP_SVC)); // Tengo que guardar el valor del stack pointer SVC que apunta a la tarea siguiente
        asm("CPS #0x12");
    }

    GICC0->EOIR = id; //End of interrupt

    return tcb_tareas[current_task].SP_IRQ; //Devuelvo el SP
}
