.code 32
.extern _start

.section .reset_vector //Para asegurarme que esten en diferentes secciones y que no me lo guarde en funcion de cual mando primero
.global _reset_vector

_reset_vector :  //garantizo que siempre entro aca, en modo Supervisor

    B _start

.end
