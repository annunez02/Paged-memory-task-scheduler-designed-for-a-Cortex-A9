/*
    
    Definiciones necesarias: formato de salida, arquitectura y

    Todo lo que esta en amarillo se llama directiva, data para el linker. 

*/

OUTPUT_FORMAT("elf32-littlearm")  /* Le digo que es little endian, de 32 bits, arm y el punto de entrada se llama _reset_vector*/
OUTPUT_ARCH(arm)
ENTRY(_reset_vector)

/*

    Definiciones de simbolos necesarios. Cada simbolo esta asociado a una direccion de memoria

*/

_ISR_TABLE_INIT     = 0x00000000; /* Simbolo */
_PUBLIC_RAM_INIT    = 0x70010000; /* Simbolo */
_PUBLIC_STACK_INIT  = 0x70020000; /* Indico donde arranca la pila del sistema*/



IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;
SYS_STACK_SIZE = 1024;

TASK_IDLE_STACK_SIZE = 256;
TASK_1_STACK_SIZE = 256;
TASK_2_STACK_SIZE = 256;



/* 
    Definiciones de simbolos necesarios
*/
/*
_PUBLIC_STACK_INIT = 0x4030B800;
_PUBLIC_RAM_INIT = 0x402f0400;
_public_ram_INIT = 0x80000000;
*/

C_STACK_SIZE   = 4K;

/* ------------------ PHYSICAL ------------------ */
/* Vector de reset y código de inicialización */
__RESET_PHYSICAL            = 0x70010000;
/* Public stack */
__PUBLIC_STACK_PHYSICAL     = 0x70020000;
/* ISR Table */
__ISR_TABLE_PHYSICAL        = 0x00000000;

/* Kernel */
__KERNEL_TXT_PHYSICAL       = 0x70030000;
__KERNEL_BSS_PHYSICAL       = 0x70022000;
__KERNEL_DATA_PHYSICAL      = 0x70032000;
__KERNEL_RODATA_PHYSICAL    = 0x70023000;

__KERNEL_PILA_PHY      = 0x70020000;

__KERNEL_PILA_IRQ_PHY  = __KERNEL_PILA_PHY;
__KERNEL_PILA_SYS_PHY  = (__KERNEL_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__KERNEL_PILA_SVC_PHY  = (__KERNEL_PILA_SYS_PHY + SYS_STACK_SIZE);
__KERNEL_PILA_UND_PHY  = (__KERNEL_PILA_SVC_PHY + SVC_STACK_SIZE);
__KERNEL_PILA_ABT_PHY  = (__KERNEL_PILA_UND_PHY + UND_STACK_SIZE);

__task_idle_irq_stack_top__PHY = (__KERNEL_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__task_idle_svc_stack_top__PHY = (__KERNEL_PILA_SVC_PHY + SVC_STACK_SIZE);


/* Tablas de paginación */
__SYSTABLES_PHYSICAL        = 0x70080000;
__SYSTABLES_TAREA_1_PHY     = 0x70480000;
__SYSTABLES_TAREA_2_PHY     = 0x70880000;


/* Tareas */
__IDLE_TXT_PHY          = 0x70034000;


__TAREA_1_TXT_PHY       = 0x80750000;
__TAREA_1_BSS_PHY       = 0x80753000;
__TAREA_1_DATA_PHY      = 0x80751000;
__TAREA_1_RODATA_PHY    = 0x80754000;

__TAREA_2_TXT_PHY       = 0x80740000;
__TAREA_2_BSS_PHY       = 0x80743000;
__TAREA_2_DATA_PHY      = 0x80741000;
__TAREA_2_RODATA_PHY    = 0x80744000;

__TAREA_1_PILA_PHY      = 0x80742000;
__TAREA_2_PILA_PHY      = 0x80752000;

__TAREA_1_PILA_IRQ_PHY  = __TAREA_1_PILA_PHY;
__TAREA_1_PILA_SYS_PHY  = (__TAREA_1_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__TAREA_1_PILA_SVC_PHY  = (__TAREA_1_PILA_SYS_PHY + SYS_STACK_SIZE);
__TAREA_1_PILA_UND_PHY  = (__TAREA_1_PILA_SVC_PHY + SVC_STACK_SIZE);
__TAREA_1_PILA_ABT_PHY  = (__TAREA_1_PILA_UND_PHY + UND_STACK_SIZE);

__task_1_irq_stack_top__PHY = (__TAREA_1_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__task_1_svc_stack_top__PHY = (__TAREA_1_PILA_SVC_PHY + SVC_STACK_SIZE);


__TAREA_2_PILA_IRQ_PHY  = __TAREA_2_PILA_PHY;
__TAREA_2_PILA_SYS_PHY  = (__TAREA_2_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__TAREA_2_PILA_SVC_PHY  = (__TAREA_2_PILA_SYS_PHY + SYS_STACK_SIZE);
__TAREA_2_PILA_UND_PHY  = (__TAREA_2_PILA_SVC_PHY + SVC_STACK_SIZE);
__TAREA_2_PILA_ABT_PHY  = (__TAREA_2_PILA_UND_PHY + UND_STACK_SIZE);

__task_2_irq_stack_top__PHY = (__TAREA_2_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__task_2_svc_stack_top__PHY = (__TAREA_2_PILA_SVC_PHY + SVC_STACK_SIZE);

__TAREA_1_READING_AREA_PHY   = 0x80010000;
__TAREA_2_READING_AREA_PHY   = 0x80000000;

/* ------------------ LMA ------------------ */




/* ------------------ VMA ------------------ */

/* Vector de reset y código de inicialización */
__RESET_VMA            = 0x70010000;
/* Public stack */
__PUBLIC_STACK_VMA     = 0x70020000;
/* ISR Table */
__ISR_TABLE_VMA        = 0x00000000;

/* Kernel */
__KERNEL_TXT_VMA       = 0x70030000;
__KERNEL_BSS_VMA       = 0x70022000;
__KERNEL_DATA_VMA      = 0x70032000;
__KERNEL_RODATA_VMA    = 0x70023000;

__KERNEL_PILA_VMA      = 0x70020000;

__KERNEL_PILA_IRQ_VMA  = __KERNEL_PILA_VMA;
__KERNEL_PILA_SYS_VMA  = (__KERNEL_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__KERNEL_PILA_SVC_VMA  = (__KERNEL_PILA_SYS_VMA + SYS_STACK_SIZE);
__KERNEL_PILA_UND_VMA  = (__KERNEL_PILA_SVC_VMA + SVC_STACK_SIZE);
__KERNEL_PILA_ABT_VMA  = (__KERNEL_PILA_UND_VMA + UND_STACK_SIZE);

__task_idle_irq_stack_top__VMA = (__KERNEL_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__task_idle_svc_stack_top__VMA = (__KERNEL_PILA_SVC_VMA + SVC_STACK_SIZE);

/* Tablas de paginación */
__SYSTABLES_VMA             = 0x70080000;
__SYSTABLES_TAREA_1_VMA     = 0x70480000;
__SYSTABLES_TAREA_2_VMA     = 0x70880000;

/* Tareas */
__IDLE_TXT_VMA          = 0x70034000;

__TAREA_1_TXT_VMA       = 0x70F50000;
__TAREA_1_BSS_VMA       = 0x70F53000;
__TAREA_1_DATA_VMA      = 0x70F51000;
__TAREA_1_RODATA_VMA    = 0x70F54000;

__TAREA_2_TXT_VMA       = 0x70F40000;
__TAREA_2_BSS_VMA       = 0x70F43000;
__TAREA_2_DATA_VMA      = 0x70F41000;
__TAREA_2_RODATA_VMA    = 0x70F44000;

__TAREA_1_PILA_VMA      = 0x70F52000;
__TAREA_2_PILA_VMA      = 0x70F42000;

__TAREA_1_PILA_IRQ_VMA  = __TAREA_1_PILA_VMA;
__TAREA_1_PILA_SYS_VMA  = (__TAREA_1_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__TAREA_1_PILA_SVC_VMA  = (__TAREA_1_PILA_SYS_VMA + SYS_STACK_SIZE);
__TAREA_1_PILA_UND_VMA  = (__TAREA_1_PILA_SVC_VMA + SVC_STACK_SIZE);
__TAREA_1_PILA_ABT_VMA  = (__TAREA_1_PILA_UND_VMA + UND_STACK_SIZE);

__task_1_irq_stack_top__VMA = (__TAREA_1_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__task_1_svc_stack_top__VMA = (__TAREA_1_PILA_SVC_VMA + SVC_STACK_SIZE);

__TAREA_2_PILA_IRQ_VMA  = __TAREA_2_PILA_VMA;
__TAREA_2_PILA_SYS_VMA  = (__TAREA_2_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__TAREA_2_PILA_SVC_VMA  = (__TAREA_2_PILA_SYS_VMA + SYS_STACK_SIZE);
__TAREA_2_PILA_UND_VMA  = (__TAREA_2_PILA_SVC_VMA + SVC_STACK_SIZE);
__TAREA_2_PILA_ABT_VMA  = (__TAREA_2_PILA_UND_VMA + UND_STACK_SIZE);

__task_2_irq_stack_top__VMA = (__TAREA_2_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__task_2_svc_stack_top__VMA = (__TAREA_2_PILA_SVC_VMA + SVC_STACK_SIZE);


__TAREA_1_READING_AREA_VMA   = 0x70A00000;
__TAREA_2_READING_AREA_VMA   = 0x70A10000;


/*

    Definicion del mapa de memoria

    Ayuda para definir las regiones de memoria, indico cual es el origden, con los simbolos definidos previamente y el tamaño (3 bit menos significativo en cero = 4k byte)
    Definimos limites para el linker

*/


MEMORY
{
    public_ram : org = _PUBLIC_RAM_INIT, len = 1M /* de 0x70010000 a 0x70010FFF no la podemos mover porque aca arranca el qemu*/
    public_stack : org = _PUBLIC_STACK_INIT, len = 1M /* de 0x70020000 a 0x70114240 */
}

/* 
    Como estoy en la pila, y es full descending, el stack pointer empieza en 0x70020FFF y va disminuyendo
*/

/*

    Definicion de las secciones

    . es el program counter del linker, un puntero, el . se autoincrementa solo -----------> . es el location counter
    NOTA: no es lo mismo . que .data, tener en cuenta los espacios

    Los de la derecha * son un comodin (wild card), puedo tener varios archivos que empiezan igual y meter todos 
    Los de la izquierda ponerlos siempre

*/

SECTIONS
{
    . = _PUBLIC_RAM_INIT; /* le digo que tome el valor de 0x70010000, le indico donde arranca el codigo */
    .text : {               /* Nombre de la seccion de salida, nombre de la seccion en el archivo elf */ 
        *(.reset_vector*)   /* Nombre de las secciones de entrada */
        *(.handlers*)
        *(.table_isr*)
        *(.startup*)
        *(.text*)           /* Me atajo por si me olvido */
    } > public_ram  /* Puede estar o no, si definimos MEMORY, lo usamos para indicar/asociar a que region de memoria quiero que vaya. Tiene que coincidir con el primero */
    /*__reset_size__ =sizeof(.text)*/

    /*
        Referenciandolo con public_ram me aseguro de no excederme del tamaño que le habia asignado y no hacer cagadas
     */ 

    .data : { *(.data*) } > public_ram  /* Variables goblales inicializadas */

    .bss : {  /* Variables goblales no inicializadas */
        . = ALIGN(4); /* Alineo el location counter a 4 bytes, lo pongo en la proxima direccion multiplo de 4 bytes */ 
        _bss_start__ = .; /* Leo donde quedo el location counter */
        *(bss*)
        __bss_end__ = .;
    } > public_ram


    /* ------------------------------ Kernel ------------------------------ */
    /* Código de kernel */    
    __KERNEL_TXT_LMA = .;
    .kernel __KERNEL_TXT_VMA : AT (__KERNEL_TXT_LMA)
    { 
        *(.kernel_text*) 
        *(.rel.kernel*)
        . = ALIGN(4); 
        } > public_ram
    __kernel_size__ = SIZEOF(.kernel);

    /* BSS de kernel */ 
    __KERNEL_BSS_LMA = __kernel_size__ + __KERNEL_TXT_LMA;
    .kernel_bss __KERNEL_BSS_VMA : AT(__KERNEL_BSS_LMA)
        {
            *(.kernel_bss*);
            . = ALIGN(4); 
        } > public_ram
    __kernel_bss_size__ = SIZEOF(.kernel_bss);

    /* Data de kernel */ 
    __KERNEL_DATA_LMA = __kernel_bss_size__ + __KERNEL_BSS_LMA;
    .kernel_data __KERNEL_DATA_VMA : AT(__KERNEL_DATA_LMA)
        {
            *(.kernel_data*);
            . = ALIGN(4);
        } > public_ram
    __kernel_data_size__ = SIZEOF(.kernel_data);

    __KERNEL_RODATA_LMA = __kernel_data_size__ + __KERNEL_DATA_LMA;
    .rodata_kernel __KERNEL_RODATA_VMA : AT(__KERNEL_RODATA_LMA)
        {
            *(.kernel_rodata*);
            . = ALIGN(4);
        } > public_ram
    __kernel_rodata_size__ = SIZEOF(.rodata_kernel);

    /* ------------------------------ Tarea idle ------------------------------ */
    
    __IDLE_TXT_LMA = __kernel_rodata_size__ + __KERNEL_RODATA_LMA;
    .txt_tarea_idle __IDLE_TXT_VMA : AT (__IDLE_TXT_LMA)
    { 
        *(.idle_text*) 
        . = ALIGN(4); 
        } > public_ram
    __idle_size__ = SIZEOF(.txt_tarea_idle);


    /* ------------------------------ Tarea 1 ------------------------------ */

    /* Código de Tarea 1 */ 
   
    __TAREA_1_TXT_LMA = __idle_size__ + __IDLE_TXT_LMA;
    .txt_tarea_1 __TAREA_1_TXT_VMA : AT(__TAREA_1_TXT_LMA)
        {
            *(.tarea_1_txt*);
            . = ALIGN(4);
        } 
    __txt_tarea_1_size__ = SIZEOF(.txt_tarea_1);    

    /* BSS de Tarea 1 */ 
   
    __TAREA_1_BSS_LMA = __txt_tarea_1_size__ + __TAREA_1_TXT_LMA;
    .bss_tarea_1 __TAREA_1_BSS_VMA : AT(__TAREA_1_BSS_LMA)
        {
            *(.tarea_1_bss*);
            . = ALIGN(4); 
        }  
    __bss_tarea_1_size__ = SIZEOF(.bss_tarea_1);

    /* Data de Tarea 1 */ 
   
    __TAREA_1_DATA_LMA = __bss_tarea_1_size__ + __TAREA_1_BSS_LMA;
    .data_tarea_1 __TAREA_1_DATA_VMA : AT(__TAREA_1_DATA_LMA)
        {
            *(.tarea_1_data*);
            . = ALIGN(4);
        }  
    __data_tarea_1_size__ = SIZEOF(.data_tarea_1);

    /* Rodata de Tarea 1 */ 
   
    __TAREA_1_RODATA_LMA = __data_tarea_1_size__ + __TAREA_1_DATA_LMA;
    .rodata_tarea_1 __TAREA_1_RODATA_VMA : AT(__TAREA_1_RODATA_LMA)
        {
            *(.tarea_1_rodata*);
            . = ALIGN(4);
        }  
    __rodata_tarea_1_size__ = SIZEOF(.rodata_tarea_1);

   
    /* ------------------------------ Tarea 2 ------------------------------ */

    /* Código de Tarea 2 */ 
   
    __TAREA_2_TXT_LMA = __rodata_tarea_1_size__ + __TAREA_1_RODATA_LMA;
    .txt_tarea_2 __TAREA_2_TXT_VMA : AT(__TAREA_2_TXT_LMA)
        {
            *(.tarea_2_txt*);
            . = ALIGN(4);
        }  
    __txt_tarea_2_size__ = SIZEOF(.txt_tarea_2);    

    /* BSS de Tarea 2 */ 
    __TAREA_2_BSS_LMA = __txt_tarea_2_size__ + __TAREA_2_TXT_LMA;
    .bss_tarea_2 __TAREA_2_BSS_VMA : AT(__TAREA_2_BSS_LMA)
        {
            *(.tarea_2_bss*);
            . = ALIGN(4);
        }  
    __bss_tarea_2_size__ = SIZEOF(.bss_tarea_2);

    /* Data de Tarea 2 */ 
    __TAREA_2_DATA_LMA = __bss_tarea_2_size__ + __TAREA_2_BSS_LMA;
    .data_tarea_2 __TAREA_2_DATA_VMA : AT(__TAREA_2_DATA_LMA)
        {
            *(.tarea_2_data*);
            . = ALIGN(4);
        }  
    __data_tarea_2_size__ = SIZEOF(.data_tarea_2);

    /* Rodata de Tarea 2 */ 
    __TAREA_2_RODATA_LMA = __data_tarea_2_size__ + __TAREA_2_DATA_LMA;
    .rodata_tarea_2 __TAREA_2_RODATA_VMA : AT(__TAREA_2_RODATA_LMA)
        {
            *(.tarea_2_rodata*);
            . = ALIGN(4);
        } 
    __rodata_tarea_2_size__ = SIZEOF(.rodata_tarea_2);



    /* ------------------------------ Stacks de Excepciones ------------------------------ */

    . = _PUBLIC_STACK_INIT;
    .stack : 
        {
         __stack_start__ = .;

         . += IRQ_STACK_SIZE; /* Muevo al location counter a IRQ_STACK_SIZE*/
         . = ALIGN(4);
         __irq_stack_top__ = .; /* La posicion mas baja en memoria, de aca voy subiendo hasta llegar a stack start */
         
         . += FIQ_STACK_SIZE;
         . = ALIGN(4);
         __fiq_stack_top__ = .;
         
         . += SVC_STACK_SIZE;
         . = ALIGN(4);
         __svc_stack_top__ = .;
         
         . += ABT_STACK_SIZE;
         . = ALIGN(4);
         __abt_stack_top__ = .;   

         . += UND_STACK_SIZE;
         . = ALIGN(4);
         __und_stack_top__ = .;   

         . += SYS_STACK_SIZE;
         . = ALIGN(4);
         __sys_stack_top__ = .; 
         
         __stack_end__ = .;  
        } > public_stack        /* Todo lo que esta en corchetes lo meto en publick stack */
}

/*

    Todo lo que está en el linker es global

    Hay que "atajar" todo, incluso las constantes, si no van a parar a cualquier posicion de memoria

    tener en cuenta que el pc apunta 2 direcciones mas abajo porque el pipeline tiene 3 etapas, mientras ejecuto la primera, decodifico la segunda y estoy fetcheando
    la tercera instruccion. El pc siempre va a estar en la posicion de fetch. Por eso tengo que sumar 8 menos que lo que haria normalmente mirando la posicion que
    estoy ejecutando.

    __KERNEL_TXT_LMA = .;
    .kernel __KERNEL_TXT_VMA : AT (__KERNEL_TXT_LMA)   aca esta . = __KERNEL_TXT_VMA
    {

    } > public_ram

    __kernel_size__ = SIZEOF(.kernel);
    
    
    __KERNEL_BSS_LMA = __kernel_size__ + LOADADDR(.kernel) 
    
    que es lo mismo q poner

    __KERNEL_BSS_LMA = __kernel_size__ + __KERNEL_TXT_LMA 



*/