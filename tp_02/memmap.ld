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

_PUBLIC_RAM_INIT = 0x70010000; /* Simbolo */
_ISR_TABLE_INIT = 0x00000000; /* Simbolo */
_PUBLIC_STACK_INIT = 0x70020000; /* Indico donde arranca la pila del sistema*/
__TTBR0_PRUEBA = 0x70080000;

IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;
SYS_STACK_SIZE = 1024;

TASK_IDLE_STACK_SIZE = 256;
TASK_1_STACK_SIZE = 256;
TASK_2_STACK_SIZE = 256;
TASK_3_STACK_SIZE = 256;


/*

    Definicion del mapa de memoria

    Ayuda para definir las regiones de memoria, indico cual es el origden, con los simbolos definidos previamente y el tamaño (3 bit menos significativo en cero = 4k byte)
    Definimos limites para el linker

*/


MEMORY
{
    public_ram : org = _PUBLIC_RAM_INIT, len = 0x1000 /* de 0x70010000 a 0x70010FFF no la podemos mover porque aca arranca el qemu*/
    public_stack : org = _PUBLIC_STACK_INIT, len = 0x1000 /* de 0x70020000 a 0x70114240 */
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
        *(.tarea_idle_text*)
        *(.tarea_1_text*)
        *(.tarea_2_text*)
        *(.tarea_3_text*)
        *(.tareas_data*)
        *(.kernel_data*)
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


    . = _PUBLIC_STACK_INIT;
    .stack : 
        {
         __stack_start__ = .;
         
         . += TASK_IDLE_STACK_SIZE;
         . = ALIGN(4);
         __task_idle_irq_stack_top__ = .;

         . += TASK_1_STACK_SIZE;
         . = ALIGN(4);
         __task_1_irq_stack_top__ = .;

         . += TASK_2_STACK_SIZE;
         . = ALIGN(4);
         __task_2_irq_stack_top__ = .;

         . += TASK_3_STACK_SIZE;
         . = ALIGN(4);
         __task_3_irq_stack_top__ = .;

         . += IRQ_STACK_SIZE; /* Muevo al location counter a IRQ_STACK_SIZE*/
         . = ALIGN(4);
         __irq_stack_top__ = .; /* La posicion mas baja en memoria, de aca voy subiendo hasta llegar a stack start */
         
         . += FIQ_STACK_SIZE;
         . = ALIGN(4);
         __fiq_stack_top__ = .;
         
         . += TASK_IDLE_STACK_SIZE;
         . = ALIGN(4);
         __task_idle_svc_stack_top__ = .;

         . += TASK_1_STACK_SIZE;
         . = ALIGN(4);
         __task_1_svc_stack_top__ = .;

         . += TASK_2_STACK_SIZE;
         . = ALIGN(4);
         __task_2_svc_stack_top__ = .;

         . += TASK_3_STACK_SIZE;
         . = ALIGN(4);
         __task_3_svc_stack_top__ = .;

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
    .kernal __KERNEL_TXT_VMA : AT (__KERNEL_TXT_LMA)   aca esta . = __KERNEL_TXT_VMA
    {

    } > DDR0

    __kernel_size__ = SIZEOF(.kernel);
    
    
    __KERNEL_BSS_LMA = __kernel_size__ + LOADADDR(.kernel) 
    
    que es lo mismo q poner

    __KERNEL_BSS_LMA = __kernel_size__ + __KERNEL_TXT_LMA 


    Tarea 2 . readingArea   70A10000h 80010000h
    Tarea 1 .readingArea    70A00000h 80000000h
    Tarea 1 .text           70F50000h 80750000h
    Tarea 1 .data           70F51000h 80751000h
    Pila Tarea 1            70F52000h 80752000h
    Tarea 1 .bss            70F53000h 80753000h
    Tarea 1 .rodata         70F54000h 80754000h
    Tarea 2 .text           70F40000h 80740000h
    Tarea 2 .data           70F41000h 80741000h
    Tarea 2 .bss            70F43000h 80743000h
    Tarea 2 .rodata         70F44000h 80744000h
    Pila Tarea 2            70F42000h 80742000h
    Kernel .data (datos y
    tablas)                 70031000h 70031000h
    Kernel .text            70030000h 70030000h
    Kernel .rodata          70023000h 70023000h
    Kernel .bss             70022000h 70022000h
    Pila Kernel             70020000h 70020000h
    Secuencia inicialización
    ROM                     70010000h 70010000h
    Vector de INT           00000000h 00000000h

*/