/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     ram_march_test.c                                                                                  *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 MarchC method for testing RAM                                                            *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include <string.h>
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"

//for iram test
#define pu8Idata ((unsigned char volatile idata *) 0)
static  xdata uint16_t u16xaddr;
static uint8_t xdata au8XRAMBackup[256];

//for xram test
#define pu8Xdata ((unsigned char volatile xdata *) 0)
static  uint16_t data u16XRAMAddr;
static  uint16_t data u16AddrssTemp;
static  uint8_t data u8LocalCnt;
static  uint8_t data au8IRAMBackup[8];
//record test xram start addreess
static uint16_t volatile data g_u16XRAMStartAddress;

void IEC60730_Ram_Test_RunTime_Init(void)
{
    g_u16XRAMStartAddress = xdata_size - 8; //for inital flash start address
}


//internal ram march c test
uint8_t IEC60730_IRAM_MarchC_Test(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;

    //backup idata context
    for (u16xaddr = 0X0; u16xaddr < idata_size; u16xaddr++)
    {

        au8XRAMBackup[u16xaddr] = pu8Idata[u16xaddr];
    }

    //write 0x0 from address 0x20 to idata size end
    for (u16xaddr = 0x20; u16xaddr < idata_size; u16xaddr++)
    {
        pu8Idata[u16xaddr] = 0;
    }

    //compare ram cotex is 0x00 and write 0xff for next test
    for (u16xaddr = 0x20; u16xaddr < idata_size; u16xaddr++)
    {
        if (pu8Idata[u16xaddr] != 0)
            return IRAM_MARCHC_POST_FALSE;
        else
            pu8Idata[u16xaddr] = 0xff;
    }

    //compare ram context is 0xff and write 0x00 for next test
    for (u16xaddr = 0x20; u16xaddr < idata_size; u16xaddr++)
    {
        if (pu8Idata[u16xaddr] != 0xff)
            return IRAM_MARCHC_POST_FALSE;

        pu8Idata[u16xaddr] = 0x0;
    }

    //revise compare ram cotex is 0x00 and write 0xff for next test
    for (u16xaddr = (idata_size - 1); u16xaddr != 0x20; u16xaddr--)
    {
        if (pu8Idata[u16xaddr] != 0x0)
            return IRAM_MARCHC_POST_FALSE;

        pu8Idata[u16xaddr] = 0xff;
    }

    //revise compare ram cotext is 0x00 and write 0xff for next test
    for (u16xaddr = (idata_size - 1); u16xaddr != 0x20; u16xaddr--)
    {
        if (pu8Idata[u16xaddr] != 0xff)
            return IRAM_MARCHC_POST_FALSE;

        pu8Idata[u16xaddr] = 0x0;
    }

    //reconvert idata context
    for (u16xaddr = 0X0; u16xaddr < idata_size; u16xaddr++)
    {
        pu8Idata[u16xaddr] = au8XRAMBackup[u16xaddr];

        if (pu8Idata[u16xaddr] != au8XRAMBackup[u16xaddr])
            return IRAM_MARCHC_POST_FALSE;
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}

//internal ram march x test
uint8_t IEC60730_IRAM_MarchX_Test(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;

    //backup idata context
    for (u16xaddr = 0X0; u16xaddr < idata_size; u16xaddr++)
    {
        au8XRAMBackup[u16xaddr] = pu8Idata[u16xaddr];
    }

    //write 0x0 from address 0x20 to idata size end
    for (u16xaddr = 0X20; u16xaddr < idata_size; u16xaddr++)
    {
        pu8Idata[u16xaddr] = 0;

    }

    //compare ram context is 0x00 and write 0xff for next test
    for (u16xaddr = 0x20; u16xaddr < idata_size; u16xaddr++)
    {
        if (pu8Idata[u16xaddr] != 0)
            return IRAM_MARCHX_POST_FALSE;

        pu8Idata[u16xaddr] = 0xff;
    }

    //revise compare ram context is 0xff and write 0x00 for next test
    for (u16xaddr = idata_size - 1; u16xaddr != 0x20; u16xaddr--)
    {
        if (pu8Idata[u16xaddr] != 0xff)
            return IRAM_MARCHX_POST_FALSE;

        pu8Idata[u16xaddr] = 0x00;
    }

    //reconvert idata context and compare context
    for (u16xaddr = 0X0; u16xaddr < idata_size; u16xaddr++)
    {
        pu8Idata[u16xaddr] = au8XRAMBackup[u16xaddr];

        if (pu8Idata[u16xaddr] != au8XRAMBackup[u16xaddr])
            return IRAM_MARCHX_POST_FALSE;
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}

uint8_t IEC60730_XRAM_MarchX_Test(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;

    // start for address 0, add 8 byte for next test
    for (u16XRAMAddr = 0; u16XRAMAddr < xdata_size; u16XRAMAddr = u16XRAMAddr + 8)
    {
        u8LocalCnt = 0;

        //backup 8 byte xram data for next test
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            au8IRAMBackup[u8LocalCnt] = pu8Xdata[u16AddrssTemp];

            if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
                return XRAM_MARCHX_FALSE;

            u8LocalCnt++;
        }

        //write xram 0x00, 8 byte count from u16XRAMAddr
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            pu8Xdata[u16AddrssTemp] = 0;
        }

        //comapre xram 0x00 (8 byte count from u16XRAMAddr) and write 0xff for next test
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            if (pu8Xdata[u16AddrssTemp] != 0)
                return XRAM_MARCHX_FALSE;

            pu8Xdata[u16AddrssTemp] = 0xff;
        }

        //revise comapre xram 0xff  (8 byte count from u16XRAMAddr) and write 0x00 for next test
        for (u16AddrssTemp = ((u16XRAMAddr + 8) - 1); u16AddrssTemp != (u16XRAMAddr - 1); u16AddrssTemp--)
        {
            if (pu8Xdata[u16AddrssTemp] != 0xff)
                return XRAM_MARCHX_FALSE;

            pu8Xdata[u16AddrssTemp] = 0x00;
        }

        u8LocalCnt = 0;

        //reconvert xram context and compare context
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            pu8Xdata[u16AddrssTemp] = au8IRAMBackup[u8LocalCnt] ;

            if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
                return XRAM_MARCHX_FALSE;

            u8LocalCnt++;
        }
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}

uint8_t IEC60730_XRAM_MarchC_Test(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;

    for (u16XRAMAddr = 0x0; u16XRAMAddr < xdata_size; u16XRAMAddr = (u16XRAMAddr + 8))
    {

        u8LocalCnt = 0;

        //backup 8 byte xram data and check this context
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            au8IRAMBackup[u8LocalCnt] = pu8Xdata[u16AddrssTemp];

            if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
                while (1);

            u8LocalCnt++;
        }

        //write xram 0x00, 8 byte count from u16XRAMAddr
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {
            pu8Xdata[u16AddrssTemp] = 0x00;
        }

        //comapre xram 0x00 (8 byte count from u16XRAMAddr) and write 0xff for next test
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {

            if (pu8Xdata[u16AddrssTemp] != 0x00)
                while (1);

            pu8Xdata[u16AddrssTemp] = 0xff;
        }

        //comapre xram 0xff (8 byte count from u16XRAMAddr) and write 0x00 for next test
        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8); u16AddrssTemp++)
        {

            if (pu8Xdata[u16AddrssTemp] != 0xff)
                while (1);

            pu8Xdata[u16AddrssTemp] = 0x00;
        }

        //revise comapre xram 0x00 (8 byte count from u16XRAMAddr) and write 0xff for next test
        for (u16AddrssTemp = (u16XRAMAddr + 8) - 1; u16AddrssTemp != (u16XRAMAddr - 1); u16AddrssTemp--)
        {

            if (pu8Xdata[u16AddrssTemp] != 0x00)
                while (1);

            pu8Xdata[u16AddrssTemp] = 0xff;
        }

        //revise comapre xram 0xff (8 byte count from u16XRAMAddr) and write 0x00 for next test
        for (u16AddrssTemp = (u16XRAMAddr + 8) - 1; u16AddrssTemp != (u16XRAMAddr - 1); u16AddrssTemp--)
        {

            if (pu8Xdata[u16AddrssTemp] != 0xff)
                while (1);

            pu8Xdata[u16AddrssTemp] = 0x00;
        }

        //reconvert xram context and compare context
        u8LocalCnt = 0;

        for (u16AddrssTemp = u16XRAMAddr; u16AddrssTemp < (u16XRAMAddr + 8) ; u16AddrssTemp++)
        {
            pu8Xdata[u16AddrssTemp] = au8IRAMBackup[u8LocalCnt] ;

            if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
                while (1);

            u8LocalCnt++;
        }

    }

    EA = BIT_TMP;//restore ea
    return PASS;
}


uint8_t IEC60730_XRAM_MarchC_Test_RUN(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;
    g_u16XRAMStartAddress = g_u16XRAMStartAddress + 8;

    //the g_u16XRAMStartAddress is over xdata_size, it will set g_u16XRAMStartAddress start 0x0000
    if (g_u16XRAMStartAddress >= xdata_size)
        g_u16XRAMStartAddress = 0;


    //backup 8 byte xram data and check this context
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        au8IRAMBackup[u8LocalCnt] = pu8Xdata[u16AddrssTemp];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUN_FALSE;

        u8LocalCnt++;
    }

    //write xram 0x00, 8 byte count from u16XRAMAddr
    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = 0;
    }

    //compare xram 0x00 (8 byte count from u16XRAMAddr) and write 0xff for next test
    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0) //For SW test breakpoint
            return XRAM_MARCHC_RUN_FALSE;

        pu8Xdata[u16AddrssTemp] = 0xff;
    }

    //comapre xram 0xff (8 byte count from u16XRAMAddr) and write 0x00 for next test
    for (u16AddrssTemp = (g_u16XRAMStartAddress); u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0xff)
            return XRAM_MARCHC_RUN_FALSE;

        pu8Xdata[u16AddrssTemp] = 0x0;
    }

    //revise comapre xram 0x00 (8 byte count from u16XRAMAddr) and write 0xff for next test
    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0x0)
            return XRAM_MARCHC_RUN_FALSE;

        pu8Xdata[u16AddrssTemp] = 0xff;
    }

    //revise comapre xram 0xff (8 byte count from u16XRAMAddr) and write 0x00 for next test
    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0xff)
            return XRAM_MARCHC_RUN_FALSE;

        pu8Xdata[u16AddrssTemp] = 0x0;
    }


    //recoveer
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = au8IRAMBackup[u8LocalCnt];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUN_FALSE;

        u8LocalCnt++;
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}


uint8_t IEC60730_XRAM_MarchC_55_Test_RUN(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        au8IRAMBackup[u8LocalCnt] = pu8Xdata[u16AddrssTemp];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUN55_FALSE;

        u8LocalCnt++;
    }


    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = 0;
    }

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0)
            return XRAM_MARCHC_RUN55_FALSE;

        pu8Xdata[u16AddrssTemp] = 0X55;
    }

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0X55)
            return XRAM_MARCHC_RUN55_FALSE;

        pu8Xdata[u16AddrssTemp] = 0x0;
    }

    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0x0)
            return XRAM_MARCHC_RUN55_FALSE;

        pu8Xdata[u16AddrssTemp] = 0X55;
    }

    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0X55)
            return XRAM_MARCHC_RUN55_FALSE;
        else
            pu8Xdata[u16AddrssTemp] = 0x0;
    }


    //recoveer
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = au8IRAMBackup[u8LocalCnt];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUN55_FALSE;

        u8LocalCnt++;
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}


uint8_t IEC60730_XRAM_MarchC_AA_Test_RUN(void)
{
    BIT_TMP = EA;//backup ea
    EA = 0;
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        au8IRAMBackup[u8LocalCnt] = pu8Xdata[u16AddrssTemp];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUNAA_FALSE;

        u8LocalCnt++;
    }


    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = 0;
    }

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0)
            return XRAM_MARCHC_RUNAA_FALSE;
        else
            pu8Xdata[u16AddrssTemp] = 0XAA;
    }

    for (u16AddrssTemp = (g_u16XRAMStartAddress + 0); u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        if (pu8Xdata[u16AddrssTemp] != 0XAA)
            return XRAM_MARCHC_RUNAA_FALSE;
        else
            pu8Xdata[u16AddrssTemp] = 0x0;
    }

    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0x0)
            return XRAM_MARCHC_RUNAA_FALSE;
        else
            pu8Xdata[u16AddrssTemp] = 0XAA;
    }

    for (u16AddrssTemp = ((g_u16XRAMStartAddress + 8) - 1); u16AddrssTemp != (g_u16XRAMStartAddress - 1); u16AddrssTemp--)
    {
        if (pu8Xdata[u16AddrssTemp] != 0XAA)
            return XRAM_MARCHC_RUNAA_FALSE;
        else
            pu8Xdata[u16AddrssTemp] = 0x0;
    }


    //recoveer
    u8LocalCnt = 0;

    for (u16AddrssTemp = g_u16XRAMStartAddress; u16AddrssTemp < (g_u16XRAMStartAddress + 8); u16AddrssTemp++)
    {
        pu8Xdata[u16AddrssTemp] = au8IRAMBackup[u8LocalCnt];

        if (au8IRAMBackup[u8LocalCnt] != pu8Xdata[u16AddrssTemp])
            return XRAM_MARCHC_RUNAA_FALSE;

        u8LocalCnt++;
    }

    EA = BIT_TMP;//restore ea
    return PASS;
}

uint8_t IEC60730_RAM_MarchC_Test_RunTime(void)
{
    if (IEC60730_XRAM_MarchC_Test_RUN() != PASS)
        return TEST_FAIL;

    return TEST_PASS;
}
