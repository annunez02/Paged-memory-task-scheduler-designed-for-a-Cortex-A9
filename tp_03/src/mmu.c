
#include "../inc/mmu.h"

/*
kernel 4 TL2
t1 6 TL2
t2 6 TL2 con otro ttbr0
*/

__attribute__((section(".kernel_text"))) void __level1_page_init(uint32_t * TTBR0, uint32_t VMA, uint32_t * TL2)
{
  uint32_t slotT1 = 0;
  slotT1 = ((VMA & TL1_mask) >> 20);

  *(TTBR0 + slotT1) = (int) TL2 + 1;  // el contenido de tablaprimernivel + 0x000 (que no lo hago x4 porque trabajo con punteros) es tabla segundo nivel(dir) + 1 (atributos)
}

__attribute__((section(".kernel_text"))) void __level2_page_init(uint32_t * addrT2, uint32_t VMA, uint32_t * dir_fisica)
{
  uint32_t slotT2 = 0;
  slotT2 = ((VMA & TL2_mask) >> 12);
 *(addrT2 + slotT2) = (int) dir_fisica + 0x30 + 2;
}


__attribute__((section(".kernel_text"))) void __mmu_init()
{
  int i = 0;

  //ciclo de borrado
  for (i = 0; i < LONGITUD_TABLAS_K; i++)
  {
      *(TTBRO_idle + i) = 0;      // por aritmetica de punteros, voy de a 4
  }

  /* En el kernel tengo 4 entradas en mi tabla de nivel 1
      - 000 (vect interrupciones)
      - 100 (timer)
      - 1E0 (GIC)
      - 700 (kernel)
  
  */
  __level1_page_init(TTBRO_idle, (uint32_t) DIR_ISR_TABLE_VMA, TABLA_SEGUNDO_NIVEL_A_K);
  __level1_page_init(TTBRO_idle, (uint32_t) DIR_TIMER01_VMA, TABLA_SEGUNDO_NIVEL_B_K);
  __level1_page_init(TTBRO_idle, (uint32_t) GICC0_ADDR, TABLA_SEGUNDO_NIVEL_C_K);
  __level1_page_init(TTBRO_idle, (uint32_t) DIR_KERNEL_TXT_VMA, TABLA_SEGUNDO_NIVEL_D_K);

  /*--- RESET VECTOR ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_A_K, (uint32_t) DIR_ISR_TABLE_VMA, DIR_ISR_TABLE_PHY);

  /*--- TIMER ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_B_K, (uint32_t) DIR_TIMER01_VMA, DIR_TIMER01_PHY);

  /*--- GIC ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_K, (uint32_t) DIR_GICC0_VMA, DIR_GICC0_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_K, (uint32_t) DIR_GICD0_VMA, DIR_GICD0_PHY);
  
  /*--- KERNEL ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_RESET_VMA, DIR_RESET_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_TXT_VMA, DIR_KERNEL_TXT_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K,((uint32_t) (DIR_KERNEL_TXT_VMA)) + 0x1000, (uint32_t *) (((uint32_t) (DIR_KERNEL_TXT_PHY)) + 0x1000));
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_DATA_VMA, DIR_KERNEL_DATA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_BSS_VMA, DIR_KERNEL_BSS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_RODATA_VMA, DIR_KERNEL_RODATA_PHY);

  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_VMA, DIR_KERNEL_PILA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_IRQ_VMA, DIR_KERNEL_PILA_IRQ_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_SYS_VMA, DIR_KERNEL_PILA_SYS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_SVC_VMA, DIR_KERNEL_PILA_SVC_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_UND_VMA, DIR_KERNEL_PILA_UND_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_KERNEL_PILA_ABT_VMA, DIR_KERNEL_PILA_ABT_PHY);
  

  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_K, (uint32_t) DIR_IDLE_TXT_VMA, DIR_IDLE_TXT_PHY);


  for (i = 0; i < LONGITUD_TABLAS_T1; i++)
  {
      *(TTBRO_tarea1 + i) = 0;      // por aritmetica de punteros, voy de a 4
  }

  /* En la tarea 1 tengo 6 entradas en mi tabla de nivel 1
      - 000 (vect interrupciones)
      - 100 (timer)
      - 1E0 (GIC)
      - 700 (kernel)
      - 70F (Tarea 1)
      - 70A (reading area)
  
  */
  __level1_page_init(TTBRO_tarea1, (uint32_t) DIR_ISR_TABLE_VMA, TABLA_SEGUNDO_NIVEL_A_T1);
  __level1_page_init(TTBRO_tarea1, (uint32_t) DIR_TIMER01_VMA, TABLA_SEGUNDO_NIVEL_B_T1);
  __level1_page_init(TTBRO_tarea1, (uint32_t) GICC0_ADDR, TABLA_SEGUNDO_NIVEL_C_T1);
  __level1_page_init(TTBRO_tarea1, (uint32_t) DIR_KERNEL_TXT_VMA, TABLA_SEGUNDO_NIVEL_D_T1);
  __level1_page_init(TTBRO_tarea1, (uint32_t) DIR_TAREA_1_TXT_VMA, TABLA_SEGUNDO_NIVEL_E_T1);
  __level1_page_init(TTBRO_tarea1, (uint32_t) DIR_TAREA_1_READING_AREA_VMA, TABLA_SEGUNDO_NIVEL_F_T1);

  /*--- RESET VECTOR ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_A_T1, (uint32_t) DIR_ISR_TABLE_VMA, DIR_ISR_TABLE_PHY);

  /*--- TIMER ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_B_T1, (uint32_t) DIR_TIMER01_VMA, DIR_TIMER01_PHY);

  /*--- GIC ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_T1, (uint32_t) DIR_GICC0_VMA, DIR_GICC0_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_T1, (uint32_t) DIR_GICD0_VMA, DIR_GICD0_PHY);
  
  /*--- KERNEL ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_RESET_VMA, DIR_RESET_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_TXT_VMA, DIR_KERNEL_TXT_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, ((uint32_t) (DIR_KERNEL_TXT_VMA)) + 0x1000, (uint32_t *) (((uint32_t) (DIR_KERNEL_TXT_PHY)) + 0x1000));
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_BSS_VMA, DIR_KERNEL_BSS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_DATA_VMA, DIR_KERNEL_DATA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_RODATA_VMA, DIR_KERNEL_RODATA_PHY);

/*
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_VMA, DIR_KERNEL_PILA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_IRQ_VMA, DIR_KERNEL_PILA_IRQ_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_SYS_VMA, DIR_KERNEL_PILA_SYS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_SVC_VMA, DIR_KERNEL_PILA_SVC_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_UND_VMA, DIR_KERNEL_PILA_UND_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T1, (uint32_t) DIR_KERNEL_PILA_ABT_VMA, DIR_KERNEL_PILA_ABT_PHY);
*/ 
  /*--- T1 ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_TXT_VMA, DIR_TAREA_1_TXT_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_BSS_VMA, DIR_TAREA_1_BSS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_DATA_VMA, DIR_TAREA_1_DATA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_RODATA_VMA, DIR_TAREA_1_RODATA_PHY);

  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_VMA, DIR_TAREA_1_PILA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_IRQ_VMA, DIR_TAREA_1_PILA_IRQ_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_SYS_VMA, DIR_TAREA_1_PILA_SYS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_SVC_VMA, DIR_TAREA_1_PILA_SVC_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_UND_VMA, DIR_TAREA_1_PILA_UND_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T1, (uint32_t) DIR_TAREA_1_PILA_ABT_VMA, DIR_TAREA_1_PILA_ABT_PHY);

  /*--- READING AREA ---*/

  for (int i = 0; i < 16; i++)
  {
    __level2_page_init(TABLA_SEGUNDO_NIVEL_F_T1, ((uint32_t) (DIR_TAREA_1_READING_AREA_VMA)) + 0x1000 * i, (uint32_t *) (((uint32_t) (DIR_TAREA_1_READING_AREA_PHY)) + 0x1000 * i));
  }
  



  for (i = 0; i < LONGITUD_TABLAS_T2; i++)
  {
      *(TTBRO_tarea2 + i) = 0;      // por aritmetica de punteros, voy de a 4
  }

  /* En la tarea 2 tengo 6 entradas en mi tabla de nivel 1
      - 000 (vect interrupciones)
      - 100 (timer)
      - 1E0 (GIC)
      - 700 (kernel)
      - 70F (Tarea 1)
      - 70A (reading area)
  
  */
  __level1_page_init(TTBRO_tarea2, (uint32_t) DIR_ISR_TABLE_VMA, TABLA_SEGUNDO_NIVEL_A_T2);
  __level1_page_init(TTBRO_tarea2, (uint32_t) DIR_TIMER01_VMA, TABLA_SEGUNDO_NIVEL_B_T2);
  __level1_page_init(TTBRO_tarea2, (uint32_t) GICC0_ADDR, TABLA_SEGUNDO_NIVEL_C_T2);
  __level1_page_init(TTBRO_tarea2, (uint32_t) DIR_KERNEL_TXT_VMA, TABLA_SEGUNDO_NIVEL_D_T2);
  __level1_page_init(TTBRO_tarea2, (uint32_t) DIR_TAREA_2_TXT_VMA, TABLA_SEGUNDO_NIVEL_E_T2);
  __level1_page_init(TTBRO_tarea2, (uint32_t) DIR_TAREA_2_READING_AREA_VMA, TABLA_SEGUNDO_NIVEL_F_T2);

  /*--- RESET VECTOR ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_A_T2, (uint32_t) DIR_ISR_TABLE_VMA, DIR_ISR_TABLE_PHY);

  /*--- TIMER ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_B_T2, (uint32_t) DIR_TIMER01_VMA, DIR_TIMER01_PHY);

  /*--- GIC ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_T2, (uint32_t) DIR_GICC0_VMA, DIR_GICC0_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_C_T2, (uint32_t) DIR_GICD0_VMA, DIR_GICD0_PHY);
  
  /*--- KERNEL ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_RESET_VMA, DIR_RESET_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_TXT_VMA, DIR_KERNEL_TXT_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, ((uint32_t) (DIR_KERNEL_TXT_VMA)) + 0x1000, (uint32_t *) (((uint32_t) (DIR_KERNEL_TXT_PHY)) + 0x1000));
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_BSS_VMA, DIR_KERNEL_BSS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_DATA_VMA, DIR_KERNEL_DATA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_RODATA_VMA, DIR_KERNEL_RODATA_PHY);

/*
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_VMA, DIR_KERNEL_PILA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_IRQ_VMA, DIR_KERNEL_PILA_IRQ_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_SYS_VMA, DIR_KERNEL_PILA_SYS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_SVC_VMA, DIR_KERNEL_PILA_SVC_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_UND_VMA, DIR_KERNEL_PILA_UND_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_D_T2, (uint32_t) DIR_KERNEL_PILA_ABT_VMA, DIR_KERNEL_PILA_ABT_PHY);
*/  
  /*--- T2 ---*/

  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_TXT_VMA, DIR_TAREA_2_TXT_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_BSS_VMA, DIR_TAREA_2_BSS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_DATA_VMA, DIR_TAREA_2_DATA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_RODATA_VMA, DIR_TAREA_2_RODATA_PHY);

  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_VMA, DIR_TAREA_2_PILA_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_IRQ_VMA, DIR_TAREA_2_PILA_IRQ_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_SYS_VMA, DIR_TAREA_2_PILA_SYS_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_SVC_VMA, DIR_TAREA_2_PILA_SVC_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_UND_VMA, DIR_TAREA_2_PILA_UND_PHY);
  __level2_page_init(TABLA_SEGUNDO_NIVEL_E_T2, (uint32_t) DIR_TAREA_2_PILA_ABT_VMA, DIR_TAREA_2_PILA_ABT_PHY);

  /*--- READING AREA ---*/

  for (int i = 0; i < 16; i++)
  {
    __level2_page_init(TABLA_SEGUNDO_NIVEL_F_T2, ((uint32_t) (DIR_TAREA_2_READING_AREA_VMA)) + 0x1000 * i, (uint32_t *) (((uint32_t) (DIR_TAREA_2_READING_AREA_PHY)) + 0x1000 * i));
  }


  //TTRB0 debe apuntar a la tabla de primer nivel

  MMU_Set_TTBR0((TTBR0) ((uint32_t)((TTBRO_idle))));

  /*
    Todos los dominios van a ser cliente.
    LDR R0, =0x55555555
    MCR p15, 0, R0, c3, c0, 0
  */

  MMU_Set_DACR((DACR) ((uint32_t) 0x55555555));

  // Habilitar MMU

  MMU_Enable((MMUENABLE) MMUENABLE_YES);

  //asm("B .");

}


