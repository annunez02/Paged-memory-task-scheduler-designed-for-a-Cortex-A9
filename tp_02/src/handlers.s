.code 32

.global _undefined
.global _software_int
.global _prefetch_abort
.global _data_abort
.global _IRQ
.global _FIQ
.extern kernel_handler_irq

.section .handlers //Para asegurarme que esten en diferentes secciones y que no me lo guarde en funcion de cual mando primero


_undefined :
    B .

_software_int :
    B .

_prefetch_abort :
    B .

_data_abort :
    B .

_IRQ :
    /* El contexto lo guardo solo en IRQ porque es donde hago el cambio de tarea */
    SUB lr, lr, #4
    STMFD SP!, {R0 - R12, LR} /* store multiple full descending en la pila */ /* sp! incremento el stack pointer y me queda en una direccion que desconozco */
    MOV R7, SP /* Una vez que termine de pushear, guardo ese puntero, que tiene una direccion desconocida en R7 */
    MRS R8, SPSR /* Move register system */ /* guardo saved program status register en R8 */
    PUSH {R7, R8} /* pusheo a la pila ambos registros*/

    MOV R0, SP
    BL kernel_handler_irq
    MOV SP, R0
    /*
    1. ir a modo svc
    2. asignarle a sp(svc) el valor de la tarea a la que tengo que cambiar
    3. volver a irq
     */


    POP {R7, R8}
    MOV SP, R7
    MSR SPSR, R8
    LDMFD SP!, {R0-R12, PC}^ /* Aca en el spsr se va a guardar para el modo svc, entonces tengo que cambiar el sp antes */ /* Aca termine de cambiar la tarea */

    /* con el ^ le digo que el contenido del spsr lo guarde en cpsr */

    B .

_FIQ :
    B .


.end
