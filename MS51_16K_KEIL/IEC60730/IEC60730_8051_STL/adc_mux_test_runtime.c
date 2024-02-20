/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     adc_mux_test_runtime.c                                                                            *
* @version  V1.00                                                                                             *
* $Date: 21/03/10 3:16p $                                                                                     *
* @brief    IEC60730 ADC/MUX Test                                                                             *
* @note                                                                                                       *
* SPDX-License-Identifier: Apache-2.0                                                                         *
* @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.                                      *
***************************************************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"
#include "IEC60730_SAFETY_TEST_LIB.h"
extern uint16_t READ_bandgap(void);
static volatile uint16_t s_u16ConversionData;
uint8_t IEC60730_ADC_Test_RunTime(void)
{
	  s_u16ConversionData =READ_bandgap();
	  if((s_u16ConversionData<BAND_GAP_H) && (s_u16ConversionData>BAND_GAP_L))        //For SW test breakpoint
    /* ADC Test Implementations */
      return TEST_PASS;
		else
			return TEST_FAIL;
}
uint8_t IEC60730_MUX_Test_RunTime(void)
{

	uint16_t u16MuxData;;
	u16MuxData =READ_ADC_CH();
    /* MUX Test Implementations */
	 if(u16MuxData != s_u16ConversionData)       //For SW test breakpoint
            return TEST_PASS;
        else
            return TEST_FAIL;

}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
