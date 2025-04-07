#include "../inc/task.h"

__attribute__((section(".tareas_data"))) int g_inc = 0, g_dec = 0;

__attribute__((section(".tarea_idle_text"))) void __tarea_idle()
{
    while (1)
    {
        asm("WFI");
    }
    
}