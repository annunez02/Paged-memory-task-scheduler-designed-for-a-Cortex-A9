#include "../inc/scheduler.h"

/*
- De Rx a Memoria
    asm("STR RX, %0":"=m"(var));

- De Memoria a Rx 
    asm("LDR RX, %0":"=m"(var));

*/

__attribute__((section(".kernel_data"))) int ticks = 0, current_task = 0, task_switch = 0;

__attribute__((section(".kernel_data"))) struct TCB tcb_tareas[3];

__attribute__((section(".kernel_data"))) int ticks_task[3] = {5, 8, 12};

__attribute__((section(".kernel_data"))) uint32_t* task_mem_irq_phy[3] = {&__task_idle_irq_stack_top__PHY, &__task_1_irq_stack_top__PHY, &__task_2_irq_stack_top__PHY};

__attribute__((section(".kernel_data"))) uint32_t* task_mem_svc_phy[3] = {&__task_idle_svc_stack_top__PHY, &__task_1_svc_stack_top__PHY, &__task_2_svc_stack_top__PHY};

__attribute__((section(".kernel_data"))) uint32_t* task_mem_irq_vma[3] = {&__task_idle_irq_stack_top__VMA, &__task_1_irq_stack_top__VMA, &__task_2_irq_stack_top__VMA};

__attribute__((section(".kernel_data"))) uint32_t* task_mem_svc_vma[3] = {&__task_idle_svc_stack_top__VMA, &__task_1_svc_stack_top__VMA, &__task_2_svc_stack_top__VMA};

__attribute__((section(".kernel_data"))) uint32_t* task_ttbr0[3] = {TTBRO_idle, TTBRO_tarea1, TTBRO_tarea2};

__attribute__((section(".kernel_data"))) void (*funciones[3])(void) = {__tarea_idle, __tarea_1, __tarea_2};

__attribute__((section(".kernel_text"))) void __scheduler_init()
{
    int i = 0;
    for (i; i < MAX_TASK; i++)
    {
        int r = 1;

        *(task_mem_irq_phy[i] - r) = (uint32_t) funciones[i]; // LR
        r++;

        for (r; r < 15; r++) // Guardo R12 - R0 en la pila de IRQ 
        {
            *(task_mem_irq_phy[i] - r) = 0; // xq es full descending
        }

        /*
        asm("cpsie i");                                         // cps i(nterrupt) e(nable) I(RQ)  tengo que hacer esto porque antes no estaban las interrupciones habilitadas, entonces cada vez que entre a la tarea, va a tener las interrupciones deshabilitadas
        asm("MRS %0, CPSR" : "=r" (*(task_mem_irq_phy[i] - r)));    // guardo el CPSR de la tarea
        asm("cpsid i");                                         // cps interrupt disable IRQ
        */
        *(task_mem_irq_phy[i] - r) = 0x113;

        /*
                    0x113 = 00001 0001 0011
        Supervisor	            svc	 1 0011
        I, bit[7]                  0            (Exception not masked. Enabled)
        F, bit[6]                   0
        Big-endian operation    1

        https://developer.arm.com/documentation/ddi0406/cb/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-ARM-core-registers/Program-Status-Registers--PSRs-?lang=en#CIHHHBDD
https://developer.arm.com/documentation/ddi0406/cb/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-ARM-core-registers/ARM-processor-modes?lang=en#CIHGHDGI
        */

        // guardo el R0 de la VMA en el SP de la fisica para que cuando prenda la mmu pueda volver
        *(task_mem_irq_phy[i] - r - 1) = (task_mem_irq_vma[i] - r + 1); // Apunto SP_IRQ a R0

        tcb_tareas[i].ticks = ticks_task[i];
        tcb_tareas[i].ID = i; 
        tcb_tareas[i].PC = (uint32_t) funciones[i];
        tcb_tareas[i].SP_SVC_PHY = task_mem_svc_phy[i];
        tcb_tareas[i].SP_SVC_VMA = task_mem_svc_vma[i];
        tcb_tareas[i].SP_IRQ_PHY = (task_mem_irq_phy[i] - r - 1); //Guardo el SP en la posicion despues del CPSR
        tcb_tareas[i].SP_IRQ_VMA = (task_mem_irq_vma[i] - r - 1); //Guardo el SP en la posicion despues del CPSR
        tcb_tareas[i].TTBR0 = (task_ttbr0[i]); 


    }
    
}

__attribute__((section(".kernel_text"))) void scheduler_c(uint32_t* SP_IRQ)
{
    ticks++;
    
    if (ticks > tcb_tareas[current_task].ticks)
    {
        tcb_tareas[current_task].SP_IRQ_VMA = SP_IRQ;
        asm("CPS #0x13");
        asm("STR SP, %0" : "=m" (tcb_tareas[current_task].SP_SVC_VMA));  // guardo el sp de la tarea actual
        asm("CPS #0x12");

        task_switch = 1;
        ticks = 0;
        current_task = tcb_tareas[(current_task + 1) % MAX_TASK].ID;   // el % me devuelve el resto de la division
        MMU_Set_TTBR0((TTBR0) ((uint32_t)((tcb_tareas[current_task].TTBR0))));
    }
    else
    {
        task_switch = 0;
    }
    
}