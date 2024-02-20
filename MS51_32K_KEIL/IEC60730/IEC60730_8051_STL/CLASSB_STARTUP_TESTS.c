/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     CLASSB_STARTUP_TEST.c                                                                             *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    CLASSB Startup Time tests                                                                         *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include "stdio.h"
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"
#if defined __ICC8051__
    extern void MemCopy(uint8_t *dest, uint16_t code *u16_addr, uint8_t size);
    extern char printf_buffer[64];
    char const CPU_Register_Test[] = "CPU Register Test (BIST)...";
    char const sPass[] = "Pass !!\n";
    char const Program_Counte_Test[] = "Program Counter Test ...";
#endif

extern uint8_t CLASSB_SAFE_STATE(uint8_t u8TestResult);
extern uint32_t volatile g_u32RAMStartAddr;
extern uint32_t volatile g_u32RAMEndAddr;
/*---------------------------------------------------------------------------------------------------------*/
/*  Startup Tests                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t CLASSB_STARTUP_TESTS(void)
{

    uint8_t u8TestResult;
    /* CPU Registers Test */
#if defined __C51__
    rt_printf((char const *)"CPU Register Test (BIST)...");
#endif
#if defined __ICC8051__
    MemCopy(printf_buffer, (uint16_t code *)CPU_Register_Test, sizeof(CPU_Register_Test));
    printf_UART((char *)&printf_buffer);
#endif
    u8TestResult = CLASSB_Registers_Test(STARTUP);

    if (u8TestResult)
    {
#if defined __C51__
    rt_printf((char const *)"Pass !!\n");
#endif
#if defined __ICC8051__
    MemCopy(printf_buffer, (uint16_t code *)sPass, sizeof(sPass));
    printf_UART((char *)&printf_buffer);
#endif

    }
    else
        CLASSB_SAFE_STATE(CPU_TEST_FAIL);

    /* Program Counter Test */
#if defined __C51__
    rt_printf((char const *)"Program Counter Test ...");
#endif
#if defined __ICC8051__
    MemCopy(printf_buffer, (uint16_t code *)Program_Counte_Test, sizeof(Program_Counte_Test));
    printf_UART((char *)&printf_buffer);
#endif
    u8TestResult = CLASSB_ProgramCounter_Test();

    if (u8TestResult)
    {
#if defined __C51__
       rt_printf((char const *)"Pass !!\n");
#endif
#if defined __ICC8051__
    MemCopy(printf_buffer, (uint16_t code *)sPass, sizeof(sPass));
    printf_UART((char *)&printf_buffer);
#endif
    }
    else
        CLASSB_SAFE_STATE(PC_TEST_FAIL);

    return u8TestResult;
}
