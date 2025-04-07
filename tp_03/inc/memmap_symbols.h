#ifndef __MEMMAP_SYMBOLS_LIB_H
#define __MEMMAP_SYMBOLS_LIB_H

#include <stddef.h>
#include <stdint.h>


extern uint32_t _ISR_TABLE_INIT;    
extern uint32_t _PUBLIC_RAM_INIT;
extern uint32_t _PUBLIC_STACK_INIT; 
extern uint32_t __TTBR0_PRUEBA;     

extern uint32_t IRQ_STACK_SIZE; 
extern uint32_t FIQ_STACK_SIZE; 
extern uint32_t SVC_STACK_SIZE; 
extern uint32_t ABT_STACK_SIZE; 
extern uint32_t UND_STACK_SIZE; 
extern uint32_t SYS_STACK_SIZE; 

extern uint32_t TASK_IDLE_STACK_SIZE; 
extern uint32_t TASK_1_STACK_SIZE; 
extern uint32_t TASK_2_STACK_SIZE; 




extern uint32_t C_STACK_SIZE;   

/* ------------------ PHYSICAL ------------------ */

/* Vector de reset y código de inicialización */
extern uint32_t __RESET_PHYSICAL;       
/* Public stack */
extern uint32_t __PUBLIC_STACK_PHYSICAL;
/* ISR Table */
extern uint32_t __ISR_TABLE_PHYSICAL;   

/* Kernel */
extern uint32_t __KERNEL_TXT_PHYSICAL;  
extern uint32_t __KERNEL_BSS_PHYSICAL;  
extern uint32_t __KERNEL_DATA_PHYSICAL; 
extern uint32_t __KERNEL_RODATA_PHYSICAL;

extern uint32_t __KERNEL_PILA_PHY;     

extern uint32_t __KERNEL_PILA_IRQ_PHY;  
extern uint32_t __KERNEL_PILA_SYS_PHY;  
extern uint32_t __KERNEL_PILA_SVC_PHY;  
extern uint32_t __KERNEL_PILA_UND_PHY;  
extern uint32_t __KERNEL_PILA_ABT_PHY;  


/* Tablas de paginación*/
extern uint32_t __SYSTABLES_PHYSICAL;   
extern uint32_t __SYSTABLES_TAREA_1_PHY;
extern uint32_t __SYSTABLES_TAREA_2_PHY;


/* Tareas */
extern uint32_t __IDLE_TXT_PHY;  

extern uint32_t __TAREA_1_TXT_PHY;      
extern uint32_t __TAREA_1_BSS_PHY;      
extern uint32_t __TAREA_1_DATA_PHY;    
extern uint32_t __TAREA_1_RODATA_PHY;   

extern uint32_t __TAREA_2_TXT_PHY;      
extern uint32_t __TAREA_2_BSS_PHY;      
extern uint32_t __TAREA_2_DATA_PHY;     
extern uint32_t __TAREA_2_RODATA_PHY;   

extern uint32_t __TAREA_1_PILA_PHY;     
extern uint32_t __TAREA_2_PILA_PHY;     

extern uint32_t __TAREA_1_PILA_IRQ_PHY; 
extern uint32_t __TAREA_1_PILA_SYS_PHY; 
extern uint32_t __TAREA_1_PILA_SVC_PHY; 
extern uint32_t __TAREA_1_PILA_UND_PHY; 
extern uint32_t __TAREA_1_PILA_ABT_PHY; 

extern uint32_t __TAREA_2_PILA_IRQ_PHY; 
extern uint32_t __TAREA_2_PILA_SYS_PHY; 
extern uint32_t __TAREA_2_PILA_SVC_PHY; 
extern uint32_t __TAREA_2_PILA_UND_PHY; 
extern uint32_t __TAREA_2_PILA_ABT_PHY; 
 
extern uint32_t __TAREA_1_READING_AREA_PHY;
extern uint32_t __TAREA_2_READING_AREA_PHY;

/* ------------------ LMA ------------------ */

extern uint32_t __KERNEL_TXT_LMA;
extern uint32_t __kernel_size__;

extern uint32_t __KERNEL_BSS_LMA;
extern uint32_t __kernel_bss_size__;

extern uint32_t __KERNEL_DATA_LMA;
extern uint32_t __kernel_data_size__;

extern uint32_t __KERNEL_RODATA_LMA;
extern uint32_t __kernel_rodata_size__;

extern uint32_t __IDLE_TXT_LMA;
extern uint32_t __idle_size__;

extern uint32_t __TAREA_1_TXT_LMA;
extern uint32_t __txt_tarea_1_size__;

extern uint32_t __TAREA_1_BSS_LMA;
extern uint32_t __bss_tarea_1_size__;

extern uint32_t __TAREA_1_DATA_LMA;
extern uint32_t __data_tarea_1_size__;

extern uint32_t __TAREA_1_RODATA_LMA;
extern uint32_t __rodata_tarea_1_size__;

extern uint32_t __TAREA_2_TXT_LMA;
extern uint32_t __txt_tarea_2_size__;

extern uint32_t __TAREA_2_BSS_LMA;
extern uint32_t __bss_tarea_2_size__;

extern uint32_t __TAREA_2_DATA_LMA;
extern uint32_t __data_tarea_2_size__;

extern uint32_t __TAREA_2_RODATA_LMA;
extern uint32_t __rodata_tarea_2_size__;


/* ------------------ VMA ------------------ */

/* Vector de reset y código de inicialización */
extern uint32_t __RESET_VMA;            

/* Public stack */
extern uint32_t __PUBLIC_STACK_VMA;     

/* ISR Table */
extern uint32_t __ISR_TABLE_VMA;        

/* Kernel */

extern uint32_t __KERNEL_TXT_VMA;       
extern uint32_t __KERNEL_BSS_VMA;       
extern uint32_t __KERNEL_DATA_VMA;      
extern uint32_t __KERNEL_RODATA_VMA;    

extern uint32_t __KERNEL_PILA_VMA;      

extern uint32_t __KERNEL_PILA_IRQ_VMA;  
extern uint32_t __KERNEL_PILA_SYS_VMA;  
extern uint32_t __KERNEL_PILA_SVC_VMA;  
extern uint32_t __KERNEL_PILA_UND_VMA;  
extern uint32_t __KERNEL_PILA_ABT_VMA;  


/* Tareas */

extern uint32_t __IDLE_TXT_VMA;  

extern uint32_t __TAREA_1_TXT_VMA;      
extern uint32_t __TAREA_1_BSS_VMA;      
extern uint32_t __TAREA_1_DATA_VMA;     
extern uint32_t __TAREA_1_RODATA_VMA;   

extern uint32_t __TAREA_2_TXT_VMA;      
extern uint32_t __TAREA_2_BSS_VMA;      
extern uint32_t __TAREA_2_DATA_VMA;     
extern uint32_t __TAREA_2_RODATA_VMA;   

extern uint32_t __TAREA_1_PILA_VMA;     
extern uint32_t __TAREA_2_PILA_VMA;     

extern uint32_t __TAREA_1_PILA_IRQ_VMA; 
extern uint32_t __TAREA_1_PILA_SYS_VMA; 
extern uint32_t __TAREA_1_PILA_SVC_VMA; 
extern uint32_t __TAREA_1_PILA_UND_VMA; 
extern uint32_t __TAREA_1_PILA_ABT_VMA; 

extern uint32_t __TAREA_2_PILA_IRQ_VMA; 
extern uint32_t __TAREA_2_PILA_SYS_VMA; 
extern uint32_t __TAREA_2_PILA_SVC_VMA; 
extern uint32_t __TAREA_2_PILA_UND_VMA; 
extern uint32_t __TAREA_2_PILA_ABT_VMA; 

extern uint32_t __TAREA_1_READING_AREA_VMA;
extern uint32_t __TAREA_2_READING_AREA_VMA;


/* Tablas de paginación*/

extern uint32_t __SYSTABLES_VMA;   
extern uint32_t __SYSTABLES_TAREA_1_VMA;
extern uint32_t __SYSTABLES_TAREA_2_VMA;

#define TTBRO_idle      (uint32_t *)&__SYSTABLES_VMA
#define TTBRO_tarea1    (uint32_t *)&__SYSTABLES_TAREA_1_VMA
#define TTBRO_tarea2    (uint32_t *)&__SYSTABLES_TAREA_2_VMA

/* --------- PHY ---------- */

/* Generales */
#define DIR_RESET_PHY           (uint32_t *)&__RESET_PHYSICAL           
#define DIR_PUBLIC_STACK_PHY    (uint32_t *)&__PUBLIC_STACK_PHYSICAL    
#define DIR_ISR_TABLE_PHY       (uint32_t *)&__ISR_TABLE_PHYSICAL 

/* Kernel */

#define DIR_KERNEL_TXT_PHY          (uint32_t *)&__KERNEL_TXT_PHYSICAL
#define DIR_KERNEL_BSS_PHY          (uint32_t *)&__KERNEL_BSS_PHYSICAL
#define DIR_KERNEL_DATA_PHY         (uint32_t *)&__KERNEL_DATA_PHYSICAL
#define DIR_KERNEL_RODATA_PHY       (uint32_t *)&__KERNEL_RODATA_PHYSICAL

#define DIR_KERNEL_PILA_PHY         (uint32_t *)&__KERNEL_PILA_PHY      

#define DIR_KERNEL_PILA_IRQ_PHY     (uint32_t *)&__KERNEL_PILA_IRQ_PHY  
#define DIR_KERNEL_PILA_SYS_PHY     (uint32_t *)&__KERNEL_PILA_SYS_PHY  
#define DIR_KERNEL_PILA_SVC_PHY     (uint32_t *)&__KERNEL_PILA_SVC_PHY  
#define DIR_KERNEL_PILA_UND_PHY     (uint32_t *)&__KERNEL_PILA_UND_PHY  
#define DIR_KERNEL_PILA_ABT_PHY     (uint32_t *)&__KERNEL_PILA_ABT_PHY 

/* Tareas */

#define DIR_IDLE_TXT_PHY            (uint32_t *)&__IDLE_TXT_PHY

#define DIR_TAREA_1_TXT_PHY         (uint32_t *)&__TAREA_1_TXT_PHY
#define DIR_TAREA_1_BSS_PHY         (uint32_t *)&__TAREA_1_BSS_PHY
#define DIR_TAREA_1_DATA_PHY        (uint32_t *)&__TAREA_1_DATA_PHY
#define DIR_TAREA_1_RODATA_PHY      (uint32_t *)&__TAREA_1_RODATA_PHY

#define DIR_TAREA_2_TXT_PHY         (uint32_t *)&__TAREA_2_TXT_PHY
#define DIR_TAREA_2_BSS_PHY         (uint32_t *)&__TAREA_2_BSS_PHY
#define DIR_TAREA_2_DATA_PHY        (uint32_t *)&__TAREA_2_DATA_PHY
#define DIR_TAREA_2_RODATA_PHY      (uint32_t *)&__TAREA_2_RODATA_PHY

#define DIR_TAREA_1_PILA_PHY        (uint32_t *)&__TAREA_1_PILA_PHY     
#define DIR_TAREA_2_PILA_PHY        (uint32_t *)&__TAREA_2_PILA_PHY     

#define DIR_TAREA_1_PILA_IRQ_PHY     (uint32_t *)&__TAREA_1_PILA_IRQ_PHY 
#define DIR_TAREA_1_PILA_SYS_PHY     (uint32_t *)&__TAREA_1_PILA_SYS_PHY 
#define DIR_TAREA_1_PILA_SVC_PHY     (uint32_t *)&__TAREA_1_PILA_SVC_PHY 
#define DIR_TAREA_1_PILA_UND_PHY     (uint32_t *)&__TAREA_1_PILA_UND_PHY 
#define DIR_TAREA_1_PILA_ABT_PHY     (uint32_t *)&__TAREA_1_PILA_ABT_PHY 

#define DIR_TAREA_2_PILA_IRQ_PHY     (uint32_t *)&__TAREA_2_PILA_IRQ_PHY 
#define DIR_TAREA_2_PILA_SYS_PHY     (uint32_t *)&__TAREA_2_PILA_SYS_PHY 
#define DIR_TAREA_2_PILA_SVC_PHY     (uint32_t *)&__TAREA_2_PILA_SVC_PHY 
#define DIR_TAREA_2_PILA_UND_PHY     (uint32_t *)&__TAREA_2_PILA_UND_PHY 
#define DIR_TAREA_2_PILA_ABT_PHY     (uint32_t *)&__TAREA_2_PILA_ABT_PHY 

#define DIR_TAREA_1_READING_AREA_PHY    (uint32_t *)&__TAREA_1_READING_AREA_PHY
#define DIR_TAREA_2_READING_AREA_PHY    (uint32_t *)&__TAREA_2_READING_AREA_PHY



/* ------------ LMA ----------- */

#define DIR_KERNEL_TXT_LMA     (uint32_t *)&__KERNEL_TXT_LMA
#define DIR_KERNEL_BSS_LMA     (uint32_t *)&__KERNEL_BSS_LMA
#define DIR_KERNEL_DATA_LMA    (uint32_t *)&__KERNEL_DATA_LMA
#define DIR_KERNEL_RODATA_LMA  (uint32_t *)&__KERNEL_RODATA_LMA

#define DIR_IDLE_TXT_LMA            (uint32_t *)&__IDLE_TXT_LMA

#define DIR_TAREA_1_TXT_LMA         (uint32_t *)&__TAREA_1_TXT_LMA
#define DIR_TAREA_1_BSS_LMA         (uint32_t *)&__TAREA_1_BSS_LMA
#define DIR_TAREA_1_DATA_LMA        (uint32_t *)&__TAREA_1_DATA_LMA
#define DIR_TAREA_1_RODATA_LMA      (uint32_t *)&__TAREA_1_RODATA_LMA

#define DIR_TAREA_2_TXT_LMA         (uint32_t *)&__TAREA_2_TXT_LMA
#define DIR_TAREA_2_BSS_LMA         (uint32_t *)&__TAREA_2_BSS_LMA
#define DIR_TAREA_2_DATA_LMA        (uint32_t *)&__TAREA_2_DATA_LMA
#define DIR_TAREA_2_RODATA_LMA      (uint32_t *)&__TAREA_2_RODATA_LMA

/* SIZE */

#define kernel_size         (uint32_t)&__kernel_size__
#define kernel_bss_size     (uint32_t)&__kernel_bss_size__
#define kernel_data_size    (uint32_t)&__kernel_data_size__
#define kernel_rodata_size  (uint32_t)&__kernel_rodata_size__

#define txt_idle_size            (uint32_t)&__idle_size__

#define txt_tarea_1_size         (uint32_t)&__txt_tarea_1_size__
#define bss_tarea_1_size         (uint32_t)&__bss_tarea_1_size__
#define data_tarea_1_size        (uint32_t)&__data_tarea_1_size__
#define rodata_tarea_1_size      (uint32_t)&__rodata_tarea_1_size__

#define txt_tarea_2_size         (uint32_t)&__txt_tarea_2_size__
#define bss_tarea_2_size         (uint32_t)&__bss_tarea_2_size__
#define data_tarea_2_size        (uint32_t)&__data_tarea_2_size__
#define rodata_tarea_2_size      (uint32_t)&__rodata_tarea_2_size__


/* ------------- VMA ------------ */

/* Generales */
#define DIR_RESET_VMA           (uint32_t *)&__RESET_VMA            
#define DIR_PUBLIC_STACK_VMA    (uint32_t *)&__PUBLIC_STACK_VMA     
#define DIR_ISR_TABLE_VMA       (uint32_t *)&__ISR_TABLE_VMA    

/* Kernel */

#define DIR_KERNEL_TXT_VMA      (uint32_t *)&__KERNEL_TXT_VMA       
#define DIR_KERNEL_BSS_VMA      (uint32_t *)&__KERNEL_BSS_VMA       
#define DIR_KERNEL_DATA_VMA     (uint32_t *)&__KERNEL_DATA_VMA      
#define DIR_KERNEL_RODATA_VMA   (uint32_t *)&__KERNEL_RODATA_VMA    

#define DIR_KERNEL_PILA_VMA     (uint32_t *)&__KERNEL_PILA_VMA      

#define DIR_KERNEL_PILA_IRQ_VMA     (uint32_t *)&__KERNEL_PILA_IRQ_VMA  
#define DIR_KERNEL_PILA_SYS_VMA     (uint32_t *)&__KERNEL_PILA_SYS_VMA  
#define DIR_KERNEL_PILA_SVC_VMA     (uint32_t *)&__KERNEL_PILA_SVC_VMA  
#define DIR_KERNEL_PILA_UND_VMA     (uint32_t *)&__KERNEL_PILA_UND_VMA  
#define DIR_KERNEL_PILA_ABT_VMA     (uint32_t *)&__KERNEL_PILA_ABT_VMA  


/* Tareas */

#define DIR_IDLE_TXT_VMA        (uint32_t *)&__IDLE_TXT_VMA

#define DIR_TAREA_1_TXT_VMA     (uint32_t *)&__TAREA_1_TXT_VMA      
#define DIR_TAREA_1_BSS_VMA     (uint32_t *)&__TAREA_1_BSS_VMA      
#define DIR_TAREA_1_DATA_VMA    (uint32_t *)&__TAREA_1_DATA_VMA     
#define DIR_TAREA_1_RODATA_VMA  (uint32_t *)&__TAREA_1_RODATA_VMA   

#define DIR_TAREA_2_TXT_VMA     (uint32_t *)&__TAREA_2_TXT_VMA      
#define DIR_TAREA_2_BSS_VMA     (uint32_t *)&__TAREA_2_BSS_VMA      
#define DIR_TAREA_2_DATA_VMA    (uint32_t *)&__TAREA_2_DATA_VMA     
#define DIR_TAREA_2_RODATA_VMA  (uint32_t *)&__TAREA_2_RODATA_VMA   

#define DIR_TAREA_1_PILA_VMA    (uint32_t *)&__TAREA_1_PILA_VMA     
#define DIR_TAREA_2_PILA_VMA    (uint32_t *)&__TAREA_2_PILA_VMA     

#define DIR_TAREA_1_PILA_IRQ_VMA     (uint32_t *)&__TAREA_1_PILA_IRQ_VMA 
#define DIR_TAREA_1_PILA_SYS_VMA     (uint32_t *)&__TAREA_1_PILA_SYS_VMA 
#define DIR_TAREA_1_PILA_SVC_VMA     (uint32_t *)&__TAREA_1_PILA_SVC_VMA 
#define DIR_TAREA_1_PILA_UND_VMA     (uint32_t *)&__TAREA_1_PILA_UND_VMA 
#define DIR_TAREA_1_PILA_ABT_VMA     (uint32_t *)&__TAREA_1_PILA_ABT_VMA 

#define DIR_TAREA_2_PILA_IRQ_VMA     (uint32_t *)&__TAREA_2_PILA_IRQ_VMA 
#define DIR_TAREA_2_PILA_SYS_VMA     (uint32_t *)&__TAREA_2_PILA_SYS_VMA 
#define DIR_TAREA_2_PILA_SVC_VMA     (uint32_t *)&__TAREA_2_PILA_SVC_VMA 
#define DIR_TAREA_2_PILA_UND_VMA     (uint32_t *)&__TAREA_2_PILA_UND_VMA 
#define DIR_TAREA_2_PILA_ABT_VMA     (uint32_t *)&__TAREA_2_PILA_ABT_VMA 

#define DIR_TAREA_1_READING_AREA_VMA    (uint32_t *)&__TAREA_1_READING_AREA_VMA
#define DIR_TAREA_2_READING_AREA_VMA    (uint32_t *)&__TAREA_2_READING_AREA_VMA

#endif // 
