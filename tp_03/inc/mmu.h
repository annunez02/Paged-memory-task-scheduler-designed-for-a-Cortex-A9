#ifndef __MMU_LIB_H
#define __MMU_LIB_H

#include <stddef.h>
#include <stdint.h>
#include "macro.h"
#include "mmu_tools_.h"
#include "gic.h"
#include "timer.h"
#include "memmap_symbols.h"

#define LONGITUD_TABLAS_PRIMER_NIVEL    0x1000 //4096 bytes, 1024 entradas largo tablas 1
#define LONGITUD_TABLAS_SEGUNDO_NIVEL    0x100 //256 entradas, largo tablas 2

// ----------- MASCARAS -------------

#define TL1_mask         0xFFF00000
#define TL2_mask         0x000FF000
#define TL2_control_mask 0x00000FFF

// ----------- KERNEL -------------

#define TABLA_SEGUNDO_NIVEL_A_K   (TTBRO_idle + LONGITUD_TABLAS_PRIMER_NIVEL)
#define TABLA_SEGUNDO_NIVEL_B_K   (TABLA_SEGUNDO_NIVEL_A_K + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_C_K   (TABLA_SEGUNDO_NIVEL_B_K + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_D_K   (TABLA_SEGUNDO_NIVEL_C_K + LONGITUD_TABLAS_SEGUNDO_NIVEL)

#define LONGITUD_TABLAS_K         (TTBRO_idle - (TABLA_SEGUNDO_NIVEL_D_K + LONGITUD_TABLAS_SEGUNDO_NIVEL))

// ----------- TAREA 1 -------------

#define TABLA_SEGUNDO_NIVEL_A_T1   (TTBRO_tarea1 + LONGITUD_TABLAS_PRIMER_NIVEL)
#define TABLA_SEGUNDO_NIVEL_B_T1   (TABLA_SEGUNDO_NIVEL_A_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_C_T1   (TABLA_SEGUNDO_NIVEL_B_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_D_T1   (TABLA_SEGUNDO_NIVEL_C_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_E_T1   (TABLA_SEGUNDO_NIVEL_D_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_F_T1   (TABLA_SEGUNDO_NIVEL_E_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL)

#define LONGITUD_TABLAS_T1         (TTBRO_tarea1 - (TABLA_SEGUNDO_NIVEL_F_T1 + LONGITUD_TABLAS_SEGUNDO_NIVEL))

// ----------- TAREA 2 -------------

#define TABLA_SEGUNDO_NIVEL_A_T2   (TTBRO_tarea2 + LONGITUD_TABLAS_PRIMER_NIVEL)
#define TABLA_SEGUNDO_NIVEL_B_T2   (TABLA_SEGUNDO_NIVEL_A_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_C_T2   (TABLA_SEGUNDO_NIVEL_B_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_D_T2   (TABLA_SEGUNDO_NIVEL_C_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_E_T2   (TABLA_SEGUNDO_NIVEL_D_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL)
#define TABLA_SEGUNDO_NIVEL_F_T2   (TABLA_SEGUNDO_NIVEL_E_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL)

#define LONGITUD_TABLAS_T2         (TTBRO_tarea2 - (TABLA_SEGUNDO_NIVEL_F_T2 + LONGITUD_TABLAS_SEGUNDO_NIVEL))

// ----------- TIMER -----------
#define DIR_TIMER01_VMA    (uint32_t *)TIMER01_ADDR
#define DIR_TIMER01_PHY    (uint32_t *)TIMER01_ADDR

// ----------- GIC ------------

#define DIR_GICC0_VMA    (uint32_t *)GICC0_ADDR
#define DIR_GICD0_VMA    (uint32_t *)GICD0_ADDR
#define DIR_GICC0_PHY    (uint32_t *)GICC0_ADDR
#define DIR_GICD0_PHY    (uint32_t *)GICD0_ADDR

//#define def_PUBLIC_STACK_INIT          (int *)&_PUBLIC_STACK_INIT

void __mmu_init();
void __level1_page_init(uint32_t *, uint32_t, uint32_t *);
void __level2_page_init(uint32_t *, uint32_t, uint32_t *);

#endif // 
