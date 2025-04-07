#ifndef __MACRO_LIB_H
#define __MACRO_LIB_H


#define reserved_bits(x,y,z) uint8_t reserved##x[ z - y + 1 ];

#endif