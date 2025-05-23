
#include "../inc/timer.h"

__attribute__((section(".text"))) void __timer_init()
    {
        _timer_t* const TIMER01 = ( _timer_t* )TIMER01_ADDR;

        TIMER01->Timer1Load     = 0x00010000; // Período = 2^18 ticks ~= 0.25 segundos
        TIMER01->Timer1Ctrl     = 0x00000002; // Seleccionamos timer de 32-bit 
        TIMER01->Timer1Ctrl    |= 0x00000040; // Seleccionamos timer periodico
        TIMER01->Timer1Ctrl    |= 0x00000020; // Habilitamos interrupción del timer
        TIMER01->Timer1Ctrl    |= 0x00000080; // Habilitamos el timer

    }