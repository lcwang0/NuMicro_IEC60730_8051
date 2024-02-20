/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     stack_test_runtime.c                                                                              *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 Program Counter-Stack Test                                                               *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"

#define stack ((unsigned char volatile idata *) 0)

void IEC60730_Stack_Test_RunTime_Init(void)
{
    /* stack pattern is destoried by RAM test at startup stage */
    uint8_t u8Count = 0;

    /* Fill test stack block with predefined pattern */
    for (u8Count = 0; u8Count < (STACK_TEST_BLOCK_SIZE / sizeof(unsigned char)); u8Count++)
    {
        stack[SP + STACK_TEST_BLOCK_SIZE + STACK_TEST_OFFSET + u8Count] = STACK_TEST_PATTERN;
    }
}
uint8_t IEC60730_Stack_Test_RunTime()
{
    uint8_t  u8Count;
    /* Pointer to the last word in the stack */
    //  *stack = SP + STACK_TEST_BLOCK_SIZE + STACK_TEST_OFFSET;
    BIT_TMP = EA; //backup ea, and disable all interrupt
    EA = 0;

    /* Check test stack block for pattern and return error if no pattern found */
    for (u8Count = 0u; u8Count < (STACK_TEST_BLOCK_SIZE / sizeof(unsigned char)); u8Count++)
    {   //check the context compare with STACK_TEST_PATTERN
        if (stack[SP + STACK_TEST_BLOCK_SIZE + STACK_TEST_OFFSET + u8Count] != STACK_TEST_PATTERN)  //For SW test breakpoint
        {
            EA = BIT_TMP; //restore ea
            return TEST_FAIL;
        }
    }

    EA = BIT_TMP; //restore ea
    return TEST_PASS;

}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
