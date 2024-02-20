/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     main.c                                                                                            *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:19p $                                                                                     *
* @brief    Main function with STL control loop example                                                       *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include "stdio.h"

#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
extern uint8_t system_init(void);

#if defined __ICC8051__
    char printf_buffer[64];
    char const system_init_OK[] = "system init OK - [OK]\n";
    char const system_init_FAIL[] = "system init FAIL - [FAIL]\n";
    char const start_up_test_OK[] = "start up test - [OK]\n";
    char const start_up_test_FAIL[] = "start up test - [FAIL]\n";
#endif

void ClassB_UserErrorHandling(uint8_t error_code)
{
    /* printf((char const*)"Error Handling\n");*/
}

void ClassB_WatchDogReset(void)
{
    /* reset wdt counter and time out flag */

}


#if defined __ICC8051__
void MemCopy(uint8_t *dest, uint16_t code *u16_addr, uint8_t size)
{
    uint8_t u8Rdata;

    while (size)
    {
        u8Rdata = *u16_addr & 0xff;
        *dest = u8Rdata;
        *dest++;
        size = size - 1;
        if (size==0)
          break;
        u8Rdata = *u16_addr >> 8 & 0xff;
        *dest = u8Rdata;
        *dest++;
        *u16_addr++;
        size = size - 1;
		if (size==0)
          break;
    }
}
#endif

void main(void)
{
    if (system_init() == PASS)
    {
#if defined __ICC8051__			
     MemCopy(printf_buffer, (uint16_t code *)system_init_OK, sizeof(system_init_OK));
     printf_UART((char *)&printf_buffer);
#endif

#if defined __C51__
        rt_printf((char const *)"system init - [OK]\n");
#endif
    }
    else
    {
#if defined __ICC8051__
        MemCopy(printf_buffer, (uint16_t code *)system_init_FAIL, sizeof(system_init_FAIL));
        printf_UART((char *)&printf_buffer);
#endif
#if defined __C51__
        rt_printf((char const *)"system init - [FAIL]\n");
#endif
    }

    /* ClassB Test Lib Init */
    CLASSB_TESTLIB_INIT(ClassB_UserErrorHandling, ClassB_WatchDogReset);


    if (CLASSB_STARTUP_TESTS() != 1)
    {
#if defined __C51__
        rt_printf((char const *)"start up test - [FAIL]\n");
#endif
#if defined __ICC8051__
        MemCopy(printf_buffer, (uint16_t code *)start_up_test_FAIL, sizeof(start_up_test_FAIL));
        printf_UART((char *)&printf_buffer);
#endif
    }
    else
    {
#if defined __C51__
        rt_printf((char const *)"start up test - [OK]\n");
#endif
#if defined __ICC8051__
        MemCopy(printf_buffer, (uint16_t code *)start_up_test_OK, sizeof(start_up_test_OK));
        printf_UART((char *)&printf_buffer);
#endif
    }

    while (1)
    {
        /* Run Time Execution Check */
        CLASSB_CHECK_RUNTIME_TESTS_EXECUTION();
        /* Run Time Test mainloop */
        CLASSB_RUNTIME_TESTS();
    }

    /* To check if system has been reset by WDT time-out reset or not */
    while (1);
}



