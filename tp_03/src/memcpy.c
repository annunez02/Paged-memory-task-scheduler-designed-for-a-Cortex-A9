#include "../inc/memcpy.h"


//      LMA       PHY    size
__attribute__((section(".text"))) void memcopy(uint32_t * DIR_LMA, uint32_t * DIR_PHY, uint32_t size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        *(DIR_PHY + i) = *(DIR_LMA + i); 
    }
    
}

__attribute__((section(".text"))) void memdeploy(void)
{
    /*          Kernel          */

    memcopy(DIR_KERNEL_TXT_LMA, DIR_KERNEL_TXT_PHY, kernel_size);
    memcopy(DIR_KERNEL_BSS_LMA, DIR_KERNEL_BSS_PHY, kernel_bss_size);
    memcopy(DIR_KERNEL_DATA_LMA, DIR_KERNEL_DATA_PHY, kernel_data_size);
    memcopy(DIR_KERNEL_RODATA_LMA, DIR_KERNEL_RODATA_PHY, kernel_rodata_size);

    memcopy(DIR_IDLE_TXT_LMA, DIR_IDLE_TXT_PHY, txt_idle_size);


    /*         Tarea 1          */

    memcopy(DIR_TAREA_1_TXT_LMA, DIR_TAREA_1_TXT_PHY, txt_tarea_1_size);
    memcopy(DIR_TAREA_1_BSS_LMA, DIR_TAREA_1_BSS_PHY, bss_tarea_1_size);
    memcopy(DIR_TAREA_1_DATA_LMA, DIR_TAREA_1_DATA_PHY, data_tarea_1_size);
    memcopy(DIR_TAREA_1_RODATA_LMA, DIR_TAREA_1_RODATA_PHY, rodata_tarea_1_size);

    /*          Tarea 2          */

    memcopy(DIR_TAREA_2_TXT_LMA, DIR_TAREA_2_TXT_PHY, txt_tarea_2_size);
    memcopy(DIR_TAREA_2_BSS_LMA, DIR_TAREA_2_BSS_PHY, bss_tarea_2_size);
    memcopy(DIR_TAREA_2_DATA_LMA, DIR_TAREA_2_DATA_PHY, data_tarea_2_size);
    memcopy(DIR_TAREA_2_RODATA_LMA, DIR_TAREA_2_RODATA_PHY, rodata_tarea_2_size);

}
