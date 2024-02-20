#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#if defined __ICC8051__
    uint8_t const code checksum [] @ APROM_CHECKSUM_ADDRESS =
#endif

#if defined __C51__
    uint8_t const code checksum[] =
#endif
{
    //all aprom checksum
    0X00, 0x00, 0x46, 0x84
};