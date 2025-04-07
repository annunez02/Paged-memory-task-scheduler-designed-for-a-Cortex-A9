.code 32
.global _start      

.extern _table_start
.extern table_size
.extern _ISR_TABLE_INIT

.extern board_init

// architectual reference manual B1.3.1

.equ USR_MODE, 0x10  /*  */
.equ FIQ_MODE, 0x11
.equ IRQ_MODE, 0x12
.equ SVC_MODE, 0x13
.equ ABT_MODE, 0x17
.equ UND_MODE, 0x1B
.equ SYS_MODE, 0x1F
.equ I_BIT   , 0x80
.equ F_BIT   , 0x40

.section .startup  //Para asegurarme que esten en diferentes secciones y que no me lo guarde en funcion de cual mando primero

_start :            
    _TABLE_COPY :        //Si se resetea vuelve al mismo lugar

        LDR R0, = #_ISR_TABLE_INIT
        LDR R1, = _table_start
        LDR R2, = #table_size

    _TABLE_LOOP :

        LDR R3, [R1], #4    //lee el primer dato que tengo que mmover y lo llevo a R3, con ! apunto a la siguiente posición // guardo el contenido de lo que apunta r1 en r3 y le sumo 4 a r1 
        STR R3, [R0], #4    //guardo R3 en R0 e incremento 4 veces
        SUBS R2, #4         // Con la s modifico los flags
        CMP R2, #0
        BNE _TABLE_LOOP

    _STACK_INIT :

        /* Inicializacion del stack cuando ponemos _c accedemos al link register */
        MSR cpsr_c, #(IRQ_MODE | I_BIT | F_BIT)  /* pongo al procesador en irq y le cargo la memoria al stack pointer */
        LDR SP, = __irq_stack_top__     /* IRQ stack pointer (direccion de memoria, en el memmap (linker script))*/ /* LDR: load data 2 register */

        MSR cpsr_c, #(FIQ_MODE | I_BIT | F_BIT)
        LDR SP, = __fiq_stack_top__     /* FIQ stack pointer */

        MSR cpsr_c, #(SYS_MODE | I_BIT | F_BIT)
        LDR SP, = __sys_stack_top__     /* SYS stack pointer */

        MSR cpsr_c, #(ABT_MODE | I_BIT | F_BIT)
        LDR SP, = __abt_stack_top__     /* ABT stack pointer */

        MSR cpsr_c, #(UND_MODE | I_BIT | F_BIT)
        LDR SP, = __und_stack_top__     /* UND stack pointer */

        MSR cpsr_c, #(SVC_MODE | I_BIT | F_BIT)
        LDR SP, = __svc_stack_top__     /* SVC stack pointer */

    _BOARD_INIT :
        LDR R10 ,= board_init
        MOV LR, PC
        BX R10

    _IRQ_ENABLE :
        MRS R0, cpsr 
        BIC R0, R0, #0x80
        MSR cpsr_c, R0

        //SWI 95 /* software interrupt num 95 de 255. Puedo recuperar este numero en el handler de svc*/



    idle : 
        WFI /* va a salir  cada vez que aparece el timer */
        B idle /* duermo al procesador, su consumo cae casi a cero */

.end
