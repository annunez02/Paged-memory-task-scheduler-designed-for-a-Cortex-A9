#include "../inc/scheduler.h"

/*
- De Rx a Memoria
    asm("STR RX, %0":"=m"(var));

- De Memoria a Rx 
    asm("LDR RX, %0":"=m"(var));

*/

__attribute__((section(".kernel_data"))) int ticks = 0, current_task = 0, task_switch = 0;

__attribute__((section(".kernel_data"))) struct TCB tcb_tareas[4];

__attribute__((section(".kernel_data"))) int ticks_task[4] = {5, 8, 12, 5};

__attribute__((section(".kernel_data"))) int* task_mem_irq[4] = {&__task_idle_irq_stack_top__, &__task_1_irq_stack_top__, &__task_2_irq_stack_top__, &__task_3_irq_stack_top__};

__attribute__((section(".kernel_data"))) int* task_mem_svc[4] = {&__task_idle_svc_stack_top__, &__task_1_svc_stack_top__, &__task_2_svc_stack_top__, &__task_3_svc_stack_top__};

__attribute__((section(".kernel_data"))) void (*funciones[4])(void) = {__tarea_idle, __tarea_1, __tarea_2, __tarea_3};

__attribute__((section(".text"))) void __scheduler_init()
{
    int i = 0;
    for (i; i < MAX_TASK; i++)
    {
        int r = 1;

        *(task_mem_irq[i] - r) = (uint32_t) funciones[i]; // LR
        r++;

        for (r; r < 15; r++) // Guardo R12 - R0 en la pila de IRQ 
        {
            *(task_mem_irq[i] - r) = 0; // xq es full descending
        }

        asm("cpsie i");                                         // cps i(nterrupt) e(nable) I(RQ)  tengo que hacer esto porque antes no estaban las interrupciones habilitadas, entonces cada vez que entre a la tarea, va a tener las interrupciones deshabilitadas
        asm("MRS %0, CPSR" : "=r" (*(task_mem_irq[i] - r)));    // guardo el CPSR de la tarea
        asm("cpsid i");                                         // cps interrupt disable IRQ
        
        *(task_mem_irq[i] - r - 1) = (task_mem_irq[i] - r + 1); // Apunto SP_IRQ a R0

        tcb_tareas[i].ticks = ticks_task[i];
        tcb_tareas[i].ID = i; 
        tcb_tareas[i].PC = (uint32_t) funciones[i];
        tcb_tareas[i].SP_SVC = task_mem_svc[i];
        tcb_tareas[i].SP_IRQ = (task_mem_irq[i] - r - 1); //Guardo el SP en la posicion despues del CPSR

    }
    
}

__attribute__((section(".text"))) void scheduler_c()
{
    ticks++;
    
    if (ticks > tcb_tareas[current_task].ticks)
    {
        asm("STR SP, %0" : "=m" (tcb_tareas[current_task].SP_IRQ));  // guardo el sp de la tarea actual
        asm("CPS #0x13");
        asm("STR SP, %0" : "=m" (tcb_tareas[current_task].SP_SVC));  // guardo el sp de la tarea actual
        asm("CPS #0x12");

        task_switch = 1;
        ticks = 0;
        current_task = tcb_tareas[(current_task + 1) % MAX_TASK].ID;   // el % me devuelve el resto de la division
    }
    else
    {
        task_switch = 0;
    }
    
}