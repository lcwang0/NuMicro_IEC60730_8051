/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     IEC60730_SAFETY_TEST_LIB.h                                                                        *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 SAFETY TEST LIB API interface definition                                                 *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#ifndef IEC60730_SAFETY_TEST_LIB_H
#define IEC60730_SAFETY_TEST_LIB_H

#define RUNTIME         0
#define STARTUP         1
#define TEST_FAIL       0
#define TEST_PASS       1
#define PC_RETURNVALUE 10
#define CPU_TEST_FAIL        0x10
#define PC_TEST_FAIL        0x14
#define STACK_TEST_FAIL        0x26
#define INTERRUPT_TEST_FAIL  0x18
#define CLOCK_TEST_FAIL      0x1C
#define FLASH_TEST_FAIL      0x20
#define RAM_TEST_FAIL        0x25
#define ADC_TEST_FAIL        0x50
#define MUX_TEST_FAIL        0x54
#define CLASSB_IDLE_STATE    while(1)
#define CLASSB_RESET_STATE   CLASSB_SYSTEM_RESET()
typedef struct
{
    uint32_t REGISTER_TEST;
    uint32_t PROGRAMCOUNTER_TEST;
    uint32_t STACK_TEST;
    uint32_t ROM_TEST;
    uint32_t RAM_TEST;
    uint32_t ADC_TEST;
    uint32_t MUX_TEST;
    uint32_t INTERRUPT_TEST;
    uint32_t WATCHDOG_RESET;
} RunTimeTestCounter_T;
typedef struct
{
    uint8_t REGISTER_TEST;
    uint8_t PROGRAMCOUNTER_TEST;
    uint8_t STACK_TEST;
    uint8_t ROM_TEST;
    uint8_t RAM_TEST;
    uint8_t ADC_TEST;
    uint8_t MUX_TEST;
    uint8_t INTERRUPT_TEST;
    uint8_t WATCHDOG_RESET;
} RunTimeTestExecution_T;
extern uint8_t CLASSB_ProgramCounter_Test(void);
extern uint8_t CLASSB_Stack_Test(void);
extern uint8_t CLASSB_Registers_Test(uint8_t TestMode);
extern uint8_t CLASSB_Interrupt_Clock_Test(void);
extern uint8_t CLASSB_Flash_Test(uint8_t TestMode);
extern uint8_t CLASSB_RAM_Test(uint8_t TestMode);
extern uint8_t CLASSB_ADC_Test(uint8_t TestMode);
extern uint8_t CLASSB_MUX_Test(uint8_t TestMode);
extern uint8_t IEC60730_PartRamMarchC_WOM(void);
extern uint8_t IEC60730_PartRamMarchX_WOM(void);
#endif
