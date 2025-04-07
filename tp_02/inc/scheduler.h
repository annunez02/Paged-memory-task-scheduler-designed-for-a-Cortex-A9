#include <stddef.h>
#include <stdint.h>
#include "task.h"


struct TCB
{
    int ticks;
    int ID;
    uint32_t PC; //Le tengo que decir a que funcion ir
    int SP_SVC;
    int SP_IRQ;
};

extern int ticks, current_task, task_switch;
extern struct TCB tcb_tareas[4];
extern uint32_t __task_idle_irq_stack_top__, __task_1_irq_stack_top__, __task_2_irq_stack_top__, __task_3_irq_stack_top__;
extern uint32_t __task_idle_svc_stack_top__, __task_1_svc_stack_top__, __task_2_svc_stack_top__, __task_3_svc_stack_top__;


#define MAX_TASK 4

__attribute__((section(".text"))) void __scheduler_init();

__attribute__((section(".text"))) void scheduler_c();