
#if defined __ICC8051__
 #define bit                                 __no_init bool __bit
 #define xdata                                __xdata
 #define data                                __data
 #define idata                                __idata
 #define pdata                                __pdata
 #define bdata                                __bdata
 #define ixdata                                __ixdata
 #define code                                __code

#define _nop_()  asm("nop") 

/* Convert To IAR: push pop SFRS */
#define _push_(SFRS)   asm(" PUSH 0x91")
#define _pop_(SFRS)    asm(" POP 0x91")

#pragma diag_suppress=Pe301 
#pragma diag_suppress=Pe061
#endif
#if defined __C51__
#include "ML51.h"
#endif
#if defined __ICC8051__
#include "ML51_IAR.h"
#endif