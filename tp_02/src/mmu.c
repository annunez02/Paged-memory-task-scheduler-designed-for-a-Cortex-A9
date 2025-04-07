
#include "../inc/mmu.h"



__attribute__((section(".text"))) void __level1_page_init(uint32_t slotT1, uint32_t * addrT2)
{
  *(TABLA_PRIMER_NIVEL + slotT1) = (int) addrT2 + 1;  // el contenido de tablaprimernivel + 0x000 (que no lo hago x4 porque trabajo con punteros) es tabla segundo nivel(dir) + 1 (atributos)
}

__attribute__((section(".text"))) void __level2_page_init(uint32_t * addrT2, uint32_t slotT2, uint32_t * dir_fisica)
{
 *(addrT2 + slotT2) = (int) dir_fisica + 0x30 + 2;
}


__attribute__((section(".text"))) void __mmu_init()
{
    int i = 0;

    *(DIR_FISICA_2) = 0x123456;

    //ciclo de borrado
    for (i = 0; i < LONGITUD_TABLAS; i++)
    {
        *(TABLA_PRIMER_NIVEL + i) = 0;      // por aritmetica de punteros, voy de a 4
    }
    
    // a la tabla de primer nivel, le guardo la informacion + atributos de las tablas de segundo nivel en el 0x700 y 0x800
    
    //*(TABLA_PRIMER_NIVEL + 0x000) = (int) TABLA_SEGUNDO_NIVEL_D + 1;  // el contenido de tablaprimernivel + 0x000 (que no lo hago x4 porque trabajo con punteros) es tabla segundo nivel(dir) + 1 (atributos)
    __level1_page_init(0x000, TABLA_SEGUNDO_NIVEL_D);

    //*(TABLA_PRIMER_NIVEL + 0x700) = (int) TABLA_SEGUNDO_NIVEL_A + 1;  // el contenido de tablaprimernivel + 0x700 (que no lo hago x4 porque trabajo con punteros) es tabla segundo nivel(dir) + 1 (atributos)
    __level1_page_init(0x700, TABLA_SEGUNDO_NIVEL_A);
    
      // Bits 31-10: BADDR (dirección base tabla nivel 2)
      // 9: No usado
      // 8-5: dominio
      // 4: cero,
      // 3: NS (no seguro),
      // 2: PXN (no ejecución)
      // 1: cero,
      // 0: uno.

    
    //hago lo mismo para la tabla 2
    
    //*(TABLA_PRIMER_NIVEL + 0x800) = (int) TABLA_SEGUNDO_NIVEL_B + 1;  // el contenido de tablaprimernivel + 0x700 (que no lo hago x4 porque trabajo con punteros) es tabla segundo nivel(dir) + 1 (atributos)
    __level1_page_init(0x800, TABLA_SEGUNDO_NIVEL_B);
    /*  Agrego GIC
      #define GICC0_ADDR 0x1E000000
      #define GICD0_ADDR 0x1E001000
    */ 

    //*(TABLA_PRIMER_NIVEL + 0x1E0) = (int) TABLA_SEGUNDO_NIVEL_C + 1;    
    __level1_page_init(0x1E0, TABLA_SEGUNDO_NIVEL_C);     
    
    // a las tablas de segundo nivel, le guardo la informacion + atributos de la pagina, este es el momento en el que asocio la direccion fisica con la virtual

    //*(TABLA_SEGUNDO_NIVEL_A + 0x10) = (int) DIR_FISICA_RAM + 0x30 + 2;
    __level2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x10, DIR_FISICA_RAM);

      // AP 011 significa acceso lectura/escritura.
      // Bits 31-12: BADDR (dir. base)
      // 11: nG (no global),
      // 10: S (memoria compartida)
      // 9: AP2 (bits de permisos)
      // 8-6: TEX (atributos de la región de memoria)
      // 5-4: AP1, AP0 (bits de permisos)
      // 3: C (atributos de la región de memoria)
      // 2: B (atributos de la región de memoria)
      // 1: uno
      // 0: XN (la página no se puede ejecutar).

    
    // Agrego la paginacion del stack, que en el memmap asignamos a 0x70020000

    //*(TABLA_SEGUNDO_NIVEL_A + 0x20) = (int) DIR_FISICA_STACK + 0x30 + 2;
    __level2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x20, DIR_FISICA_STACK);

    //*(TABLA_SEGUNDO_NIVEL_B + 0x00) = (int) DIR_FISICA_2 + 0x30 + 2;
    __level2_page_init(TABLA_SEGUNDO_NIVEL_B, 0x00, DIR_FISICA_2);


    /*  Agrego GIC
      #define GICC0_ADDR 0x1E000000
      #define GICD0_ADDR 0x1E001000
    */ 
    //  *(TABLA_SEGUNDO_NIVEL_C + 0x00) = GICC0_ADDR + 0x30 + 2; // como no estan definindos como int*, no hace falta castearlo
    //  *(TABLA_SEGUNDO_NIVEL_C + 0x01) = GICD0_ADDR + 0x30 + 2;
    __level2_page_init(TABLA_SEGUNDO_NIVEL_C, 0x00, GICC0_ADDR);
    __level2_page_init(TABLA_SEGUNDO_NIVEL_C, 0x01, GICC0_ADDR);



    /*
    Agrego vector de interrupciones
    #define TABLA_SEGUNDO_NIVEL_D   (int *)0x7009C000
    */

    //  *(TABLA_SEGUNDO_NIVEL_D + 0x00) = (int) DIR_FISICA_INTERRUPCIONES + 0x30 + 2;
    __level2_page_init(TABLA_SEGUNDO_NIVEL_D, 0x00, DIR_FISICA_INTERRUPCIONES);

   
   
    //TTRB0 debe apuntar a la tabla de primer nivel

    MMU_Set_TTBR0((TTBR0) ((uint32_t)((TABLA_PRIMER_NIVEL))));

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


