#include <stddef.h>
#include <stdint.h>
#include "task.h"
#include "mmu.h"


struct TCB
{
    int ticks;
    int ID;
    uint32_t PC; //Le tengo que decir a que funcion ir
    int SP_SVC_PHY;
    int SP_SVC_VMA;
    int SP_IRQ_PHY;
    int SP_IRQ_VMA;
    uint32_t TTBR0;
};

extern int ticks, current_task, task_switch;
extern struct TCB tcb_tareas[3];



extern uint32_t __task_idle_irq_stack_top__PHY, __task_1_irq_stack_top__PHY, __task_2_irq_stack_top__PHY;
extern uint32_t __task_idle_irq_stack_top__VMA, __task_1_irq_stack_top__VMA, __task_2_irq_stack_top__VMA;

extern uint32_t __task_idle_svc_stack_top__PHY, __task_1_svc_stack_top__PHY, __task_2_svc_stack_top__PHY;
extern uint32_t __task_idle_svc_stack_top__VMA, __task_1_svc_stack_top__VMA, __task_2_svc_stack_top__VMA;


#define MAX_TASK 3

__attribute__((section(".kernel_text"))) void __scheduler_init();

__attribute__((section(".kernel_text"))) void scheduler_c(uint32_t*);