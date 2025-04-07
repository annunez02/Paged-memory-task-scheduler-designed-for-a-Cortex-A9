#include "../inc/task.h"


__attribute__((section(".tarea_1_txt"))) void __tarea_1()
{
    int i = 0;
    uint32_t context_saver = 0, reading_verificator = 0;
    while (1)
    {
        for (i = 0; i < Long_RA_T1; i++)
        {
            context_saver = (uint32_t) *(DIR_TAREA_1_READING_AREA_VMA + i);
            *(DIR_TAREA_1_READING_AREA_VMA + i) = WORD;
            reading_verificator = (uint32_t) *(DIR_TAREA_1_READING_AREA_VMA + i);
            if (reading_verificator == WORD)
            {
                *(DIR_TAREA_1_READING_AREA_VMA + i) = context_saver;
            }        
        }
        i = 0;
    }
    

    //    DIR_TAREA_1_READING_AREA_VMA
}