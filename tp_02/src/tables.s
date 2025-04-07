.code 32
.global _table_start
.global table_size

.extern _reset_vector
.extern _undefined  // "funcion" extern
.extern _software_int
.extern _prefetch_abort
.extern _data_abort
.extern _IRQ
.extern _FIQ

.section .table_isr

/* El compilador resuelve igual, aunque no haga los literal pools por la cercania con la definicion */

_table_start : //Llevarlo a table.s
    LDR PC, addr_reset_vector       //opcode (codigo de operacion de la instruccion)
    LDR PC, addr_undefined    
    LDR PC, addr_software_int       //copio las instrucciones
    LDR PC, addr_prefetch_abort
    LDR PC, addr_data_abort
    LDR PC, addr_reserved
    LDR PC, addr_IRQ
    LDR PC, addr_FIQ
    // LDR = load register

addr_reset_vector:      .word _reset_vector     // Definicion de literal pools
addr_undefined:         .word _undefined
addr_software_int:      .word _software_int
addr_prefetch_abort:    .word _prefetch_abort
addr_data_abort:        .word _data_abort       // Cuando no puedo acceder a la dir de memoria
addr_reserved:          .word _reset_vector     // Le digo que en el caso de caer en el reservado, me haga un reset porque me fui al pasto :p
addr_IRQ:               .word _IRQ
addr_FIQ:               .word _FIQ

.equ table_size, (. - _table_start)

.end
