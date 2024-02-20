/* ____  _____             ____    ____    _                                 ______    _________   ____  _    *
* |_   \|_   _|           |_   \  /   _|  (_)                              .' ____ \  |  _   _  | |_   _|     *
*   |   \ | |    __   _     |   \/   |    __    .---.   _ .--.    .--.     | (___ \_| |_/ | | \_|   | |       *
*   | |\ \| |   [  | | |    | |\  /| |   [  |  / /'`\] [ `/'`\] / .'`\ \    _.____`.      | |       | |   _   *
*  _| |_\   |_   | \_/ |,  _| |_\/_| |_   | |  | \__.   | |     | \__. |   | \____) |    _| |_     _| |__/ |  *
* |_____|\____|  '.__.'_/ |_____||_____| [___] '.___.' [___]     '.__.'     \______.'   |_____|   |________|  *
*                                                                                                             *
* @file     IEC60730_CONTROL_PARAM.h                                                                          *
* @version  V3.00                                                                                             *
* $Revision: 1 $                                                                                             *
* $Date: 21/03/10 3:19p $                                                                                     *
* @brief    IEC60730 User Control Parameters                                                                  *
* @note                                                                                                       *
* Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.                                       *
***************************************************************************************************************/
#ifndef IEC60730_CONTROL_PARAM_H
#define IEC60730_CONTROL_PARAM_H

typedef void (*CLASSB_ERROR_HANDLING)(uint8_t);
typedef void (*CLASSB_WATCHDOG_RESET)(void);
extern uint8_t CLASSB_STARTUP_TESTS(void);
extern void CLASSB_CHECK_RUNTIME_TESTS_EXECUTION(void);
extern void CLASSB_RUNTIME_TESTS(void);
extern void CLASSB_TESTLIB_INIT(CLASSB_ERROR_HANDLING, CLASSB_WATCHDOG_RESET);
extern void CLASSB_LSCLOCK_INT(void);
extern void CLASSB_HSCLOCK_INT(void);
extern uint32_t WriteGlobal(uint32_t *Addr, uint32_t value);
extern uint32_t ReadGlobal(uint32_t *Addr, uint32_t *value);
/* ROM test parameters */

#define ROM_START               0
#define RAM_START               0


#define APROM_SIZE (16*1024)
#define ROM_LENGTH               (APROM_SIZE)
#define ROM_END                  (APROM_SIZE-4)
#define APROM_CHECKSUM_ADDRESS (APROM_SIZE-4)


/* 
Clock Ratio = (int)(HSCLOCK_FREQ/LSCLOCK_FREQ), MeanError = Clock RatioxClock_Devation, Valid Clock Ration =  Clock Ratio+/-MeanError */
#define HSCLOCK_FREQ        100
#define LSCLOCK_FREQ        9
#define CLOCK_DEVATION      20

/* for Stack test */
#define STACK_TEST_BLOCK_SIZE     0x8u
#define STACK_TEST_OFFSET       0x20u
#define STACK_TEST_PATTERN      0x5a

/* RAM test parameters */
#define idata_size 256
#define xdata_size 1024

#define XRAM_MARCHC_RUN_FALSE    0x23
#define XRAM_MARCHC_RUNAA_FALSE  0x24
#define XRAM_MARCHC_RUN55_FALSE  0x25
#define XRAM_MARCHX_FALSE  0x26
#define XRAM_MARCHC_FALSE  0x27
#define IRAM_MARCHX_POST_FALSE    0x21
#define IRAM_MARCHC_POST_FALSE    0x22
/* Debug Message */
#define rt_printf   printf

/*Safe State: 0 for IDLE STATE, 1 for RESET STATE*/
#define SAFE_STATE              0

/* ADC VREF Voltage */
#define VREF_VALUE  3.3
/* Band-Gap Voltage 1.2V threshold 10%*/
#define BAND_GAP_H  1800    /*4095*1.32/VREF_VALUE*/
#define BAND_GAP_L  1500    /*4095*1.08/VREF_VALUE*/
/* ADC Mux Test Channel */
#define MUX_CHANNEL     0

/* each item test cycle */
#define CPUREG_TEST_CYCLE           3       // 3*test_cycle
#define PC_TEST_CYCLE               5       // 5*test_cycle
#define STACK_TEST_CYCLE            10
#define RAM_TEST_CYCLE              5
#define ROM_TEST_CYCLE              1
#define INT_TEST_CYCLE              30
#define REST_WDT_CYCLE              (HSCLOCK_FREQ/LSCLOCK_FREQ + 1)
#define ADC_TEST_CYCLE              4
#define MUX_TEST_CYCLE              4

/* RAM & ROM tested length each time */
#define RAM_RUNTIME_TEST_LENGTH     0x20    // based on Artisan SRAM achitecture
#define ROM_RUNTIME_TEST_LENGTH     0x20

/* RAM runtime test methodology */
#define RAM_RUNTIME_MARCHC_WOM
#ifndef RAM_RUNTIME_MARCHC_WOM
#define RAM_RUNTIME_MARCHX_WOM

#define PASS                    0X0
#endif
#endif
