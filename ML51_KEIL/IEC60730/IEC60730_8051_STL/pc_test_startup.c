/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     pc_test_startup.c                                                                                 *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 Program Counter Test                                                                     *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "IEC60730_SAFETY_TEST_LIB.h"

#if defined __ICC8051__
    #pragma location="PC_1000"
#endif
uint32_t pc_test_return1(void)
{
    return PC_RETURNVALUE;
}//For SW test breakpoint

//return myself address
#if defined __ICC8051__
    #pragma location="PC_2000"
#endif
uint32_t pc_test_return2(void)
{
    return ((uint32_t) &pc_test_return2);
}//For SW test breakpoint

uint8_t IEC60730_PC_Test()
{
    uint32_t u32Addr = (uint32_t)&pc_test_return2;
    uint8_t u8PCTestResult = TEST_PASS;

    if (pc_test_return1() != PC_RETURNVALUE)
        u8PCTestResult = TEST_FAIL;

    if (pc_test_return2() != u32Addr)
        u8PCTestResult = TEST_FAIL;

    return u8PCTestResult;
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
