/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     flash_test_runtime.c                                                                              *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 Intrnal Flash Test runtime                                                               *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"

extern uint32_t Read_checksum_flash(uint32_t  code *u32_addr);

//for read flash context. return byte
extern uint8_t Read_APROM_BYTE_CODE(uint16_t code *u16_addr);
extern uint32_t checksum_flash(void);
void IEC60730_Flash_Test_RunTime_Init(void)
{

}

uint8_t IEC60730_Flash_Test_RunTime(void)
{
    uint32_t   u32ChecksumValue;
    uint32_t  u32ChecksumInFlashValue;
    u32ChecksumValue = checksum_flash()&0xffff;
    u32ChecksumInFlashValue = Read_checksum_flash((uint32_t code *)APROM_CHECKSUM_ADDRESS);

    if (u32ChecksumValue != u32ChecksumInFlashValue) //For SW test breakpoint
       return TEST_FAIL;

    return TEST_PASS;
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
