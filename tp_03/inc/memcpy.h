#ifndef __MEMCPY_LIB_H
#define __MEMCPY_LIB_H

#include <stddef.h>
#include <stdint.h>
#include "memmap_symbols.h"

//            LMA          PHY        size
void memcopy(uint32_t *, uint32_t *, uint32_t);
void memdeploy(void);

#endif 