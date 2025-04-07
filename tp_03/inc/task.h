#include "mmu.h"

__attribute__((section(".tarea_idle_text"))) void __tarea_idle();

__attribute__((section(".tarea_1_text"))) void __tarea_1();

__attribute__((section(".tarea_2_text"))) void __tarea_2();

#define Long_RA_T1  16384
#define WORD        0x55AA55AA