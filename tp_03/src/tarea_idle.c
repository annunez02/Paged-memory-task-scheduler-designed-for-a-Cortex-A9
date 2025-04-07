#include "../inc/task.h"

__attribute__((section(".idle_text"))) void __tarea_idle()
{
    while (1)
    {
        asm("WFI");
    }
    
}