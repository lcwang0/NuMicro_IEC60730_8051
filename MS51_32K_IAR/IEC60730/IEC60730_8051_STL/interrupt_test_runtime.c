/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     interrupt_test_runtime.c                                                                          *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 Interrupt Test                                                                           *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"
static uint32_t s_u32LSFreq;
static uint32_t s_u32HSFreq;
void IEC60730_LSCLOCK_INIT(void)
{
    s_u32LSFreq = 0;
}
void IEC60730_HSCLOCK_INIT(void)
{
    s_u32HSFreq = 0;
}
void IEC60730_LSCLOCK_INT(void)
{
    s_u32LSFreq++;
}
void IEC60730_HSCLOCK_INT(void)
{
    s_u32HSFreq++;

    /* Overflow handling */
    if (s_u32HSFreq == 0)
    {
        IEC60730_LSCLOCK_INIT();
        IEC60730_HSCLOCK_INIT();
    }
}

void IEC60730_Interrupt_Test_RunTime_Init(void)
{
    IEC60730_LSCLOCK_INIT();
    IEC60730_HSCLOCK_INIT();
}
uint8_t IEC60730_Interrupt_Test_RunTime(void)
{
    uint32_t u32Ratio, u32RatioH, u32RatioL, u32MeanError;
    uint8_t u8TestResult;

    if ((s_u32HSFreq < HSCLOCK_FREQ) || (s_u32LSFreq < LSCLOCK_FREQ))
        return TEST_PASS;

    u32Ratio = (uint32_t)(s_u32HSFreq / s_u32LSFreq);
    u32MeanError = (uint32_t)((HSCLOCK_FREQ / LSCLOCK_FREQ) * (uint8_t)CLOCK_DEVATION / 100);
    u32RatioH = u32Ratio + u32MeanError;

    if (u32Ratio >= u32MeanError)
        u32RatioL = u32Ratio - u32MeanError;
    else
        u32RatioL = 0;

    if ((u32Ratio > u32RatioH) || (u32Ratio < u32RatioL))//For SW test breakpoint
        u8TestResult = TEST_FAIL;
    else
        u8TestResult = TEST_PASS;

    return u8TestResult;
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
