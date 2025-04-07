#ifndef __MMU_LIB_H
#define __MMU_LIB_H

#include <stddef.h>
#include <stdint.h>
#include "macro.h"
#include "mmu_tools_.h"


#define LONGITUD_TABLAS_PRIMER_NIVEL    0x1000 //4096 bytes, 1024 entradas largo tablas 1
#define LONGITUD_TABLAS_SEGUNDO_NIVEL    0x100 //256 entradas, largo tablas 2

#define TABLA_PRIMER_NIVEL      (int *)0x70080000
#define TABLA_SEGUNDO_NIVEL_A   (int *)0x70090000
#define TABLA_SEGUNDO_NIVEL_B   (int *)0x700A0000
#define DIR_FISICA_1            (int *)0x70010000
#define DIR_FISICA_2            (int *)0x70015000
#define DIR_FISICA_STACK        (int *)0x70020000
#define DIR_NO_PAGINADA         (int *)0x90000000
#define LONGITUD_TABLAS         ((int) TABLA_SEGUNDO_NIVEL_B + LONGITUD_TABLAS_SEGUNDO_NIVEL - (int)TABLA_PRIMER_NIVEL)




void __mmu_init();

#endif // __GIC_LIB_H
