/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     IEC60730_SAFETY_TEST_LIB.c                                                                        *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 SAFETY TEST LIB API implementation                                                       *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/

#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"
extern uint8_t IEC60730_PC_Test(void);
extern uint8_t IEC60730_Stack_Test_RunTime(void);
extern uint8_t IEC60730_CPU_Reg_Test(void);
extern void IEC60730_CPU_Reg_Test_RunTime(void);
extern uint8_t IEC60730_FullRamMarchC_WOM(void);
extern uint8_t IEC60730_RAM_MarchC_Test_RunTime(void);
extern uint8_t IEC60730_Flash_Test(void);
extern uint8_t IEC60730_Flash_Test_RunTime(void);
extern uint8_t IEC60730_Clock_Test(void);
extern uint8_t IEC60730_Interrupt_Test_RunTime(void);
extern uint8_t IEC60730_Clock_Test(void);
extern uint8_t IEC60730_Interrupt_Test_RunTime(void);
extern uint8_t IEC60730_ADC_Test_RunTime(void);
extern uint8_t IEC60730_MUX_Test_RunTime(void);
extern CLASSB_ERROR_HANDLING g_APP_pfnErrorHandling;
extern CLASSB_WATCHDOG_RESET g_APP_pfnWatchDogReset;

#if defined __ICC8051__
    extern void MemCopy(uint8_t *dest, uint16_t code *u16_addr, uint8_t size);
    extern char printf_buffer[64];
    char const Test_Mode_Error[] = "Test Mode Error\n";
    char const Test_Fail_Code[] = "Test Fail Code:";
#endif

uint8_t CLASSB_ProgramCounter_Test()
{
    uint8_t u8Result;
    u8Result = IEC60730_PC_Test();

    return u8Result;
}
uint8_t CLASSB_WatchDog_Reset(void)
{
//    uint32_t u32value;

    if (g_APP_pfnWatchDogReset)
        g_APP_pfnWatchDogReset();

    return 1;
}
uint8_t CLASSB_Stack_Test()
{
    uint8_t u8Result;
    u8Result = IEC60730_Stack_Test_RunTime();

    return u8Result;
}
extern volatile uint8_t data ret_flag;
uint8_t CLASSB_Registers_Test(uint8_t u8TestMode)
{
    uint8_t u8Result;

    if (u8TestMode == STARTUP)
    {
        IEC60730_CPU_Reg_Test_RunTime();
			  u8Result=ret_flag;
    }
    else if (u8TestMode == RUNTIME)
    {

        IEC60730_CPU_Reg_Test_RunTime();
			u8Result=ret_flag;
    }
    else
    {
#if defined __C51__
    rt_printf((char const *)"Test Mode Error\n");
#endif
#if defined __ICC8051__
    printf((char const *)"Test Mode Error\n");
#endif
    }

    return u8Result;
}
uint8_t CLASSB_Interrupt_Clock_Test()
{
    uint8_t u8Result;

    u8Result = IEC60730_Interrupt_Test_RunTime();

    return u8Result;
}
uint8_t CLASSB_Flash_Test(uint8_t u8TestMode)
{
    uint8_t u8Result = TEST_PASS;

    if (u8TestMode == STARTUP)
		{
        u8Result = IEC60730_Flash_Test();
		}
    else if (u8TestMode == RUNTIME)
    {
        u8Result = IEC60730_Flash_Test_RunTime();
    }
    else
    {
#if defined __C51__
        rt_printf((char const *)"Test Mode Error\n");
#endif
#if defined __ICC8051__
        printf((char const *)"Test Mode Error\n");
#endif
    }

    return u8Result;
}
uint8_t CLASSB_RAM_Test(uint8_t u8TestMode)
{
    uint8_t u8Result = TEST_PASS;

    u8Result = IEC60730_RAM_MarchC_Test_RunTime();
    return u8Result;
}
uint8_t CLASSB_ADC_Test(uint8_t u8TestMode)
{
    uint8_t u8Result;

    if (u8TestMode == RUNTIME)
    {
        u8Result = IEC60730_ADC_Test_RunTime();
    }
    else
    {
#if defined __C51__
        rt_printf((char const *)"Test Mode Error\n");
#endif
#if defined __ICC8051__
        printf((char const *)"Test Mode Error\n");
#endif
    }

    return u8Result;
}
uint8_t CLASSB_MUX_Test(uint8_t u8TestMode)
{
    uint8_t u8Result;

    if (u8TestMode == RUNTIME)
    {
        u8Result = IEC60730_MUX_Test_RunTime();
    }
    else
    {
#if defined __C51__
        rt_printf((char const *)"Test Mode Error\n");
#endif
#if defined __ICC8051__
        printf((char const *)"Test Mode Error\n");
#endif
    }

    return u8Result;
}
void CLASSB_SYSTEM_RESET()
{
    /* System Reset Implementations*/


}
uint8_t CLASSB_SAFE_STATE(uint8_t u8TestResult)
{
//    uint32_t u32result, u32value;
#if defined __C51__
    rt_printf((char const *)"Test Fail Code: 0x%bx\n", u8TestResult);
#endif

#if defined __ICC8051__
    printf((char const *)"Test Fail Code: 0x%hx\n", u8TestResult);
#endif

    if (SAFE_STATE)
        CLASSB_RESET_STATE;
    else
        CLASSB_IDLE_STATE;

    if (g_APP_pfnErrorHandling)
        g_APP_pfnErrorHandling(u8TestResult);


    return 0;
}
/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
