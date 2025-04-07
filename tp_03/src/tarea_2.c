#include "../inc/task.h"


__attribute__((section(".tarea_2_txt"))) void __tarea_2()
{
    int i = 0;
    while (1) 
    {     
        for (i = 0; i < Long_RA_T1; i++)
        {
            *(DIR_TAREA_2_READING_AREA_VMA + i) = ~ ((uint32_t) *(DIR_TAREA_2_READING_AREA_VMA + i));      
        }
        i = 0;

    }
    
}