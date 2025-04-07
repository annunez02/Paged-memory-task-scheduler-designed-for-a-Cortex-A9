#ifndef __MMU_LIB_H
#define __MMU_LIB_H

#include <stddef.h>
#include <stdint.h>
#include "macro.h"
#include "mmu_tools_.h"
#include "gic.h"

extern uint32_t _PUBLIC_RAM_INIT, _ISR_TABLE_INIT, _PUBLIC_STACK_INIT, __TTBR0_PRUEBA;
#define LONGITUD_TABLAS_PRIMER_NIVEL    0x1000 //4096 bytes, 1024 entradas largo tablas 1
#define LONGITUD_TABLAS_SEGUNDO_NIVEL    0x100 //256 entradas, largo tablas 2

#define TABLA_PRIMER_NIVEL          (int *)0x70080000
#define TABLA_SEGUNDO_NIVEL_A       (int *)0x70090000
#define TABLA_SEGUNDO_NIVEL_B       (int *)0x70090400 // 0x70090000 + 0x100*4 
#define TABLA_SEGUNDO_NIVEL_C       (int *)0x70090800 //gic
#define TABLA_SEGUNDO_NIVEL_D       (int *)0x7009C000 //vector de interrupciones
#define DIR_FISICA_RAM              (int *)&_PUBLIC_RAM_INIT
#define DIR_FISICA_2                (int *)0x70015000
//#define DIR_FISICA_STACK            (int *)0x70020000
#define DIR_FISICA_STACK            (int *)&_PUBLIC_STACK_INIT
#define DIR_FISICA_INTERRUPCIONES   (int *)&_ISR_TABLE_INIT


#define DIR_NO_PAGINADA         (int *)0x90000000
#define LONGITUD_TABLAS         ((int) TABLA_SEGUNDO_NIVEL_D + LONGITUD_TABLAS_SEGUNDO_NIVEL - (int)TABLA_PRIMER_NIVEL)


//#define def_PUBLIC_STACK_INIT          (int *)&_PUBLIC_STACK_INIT

void __mmu_init();
void __level1_page_init(uint32_t, uint32_t *);
void __level2_page_init(uint32_t *, uint32_t, uint32_t *);

#endif // __GIC_LIB_H
