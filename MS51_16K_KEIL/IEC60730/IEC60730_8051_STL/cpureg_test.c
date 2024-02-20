/******************************************************************************
 * @file     cpureg_test.c
 * @version  V0.10
 * $Revision: 1 $
 * $Date: 21/03/10 3:16p $
 * @brief    IEC60730 CPU Test, for PC, ACC, DPTR, R0 - R7
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/


/*********************************************************************
**  Global Variable Declaration
*********************************************************************/
#include "NuMicro.h"
volatile uint8_t data ret_flag = 0; //for asm use
#define IRAM_SIZE      0xFF
#define CPU_OK                  0x01
#define CPU_FAILURE                  0x0
#define xdata_size 1024
#define CPU_TEST_PUSH_RAM (xdata_size-16)


//BACK acc, R0, r1, r2, r3, r4, r5, r7 and write 0x55, 0xaa, test after restoe it.
void IEC60730_CPU_Reg_Test_RunTime(void)
{
    BIT_TMP = EA; //backup EA register
    EA = 0;//disable interrupt
#if defined __C51__   //keil c51 cpu test flow
#pragma asm
    push ACC  //Backup acc
    mov A, R0
    mov DPTR, #CPU_TEST_PUSH_RAM
    movx @DPTR, A

    mov A, R1
    inc dptr
    movx @DPTR, A

    mov A, R2
    inc dptr
    movx @DPTR, A

    mov A, R3
    inc dptr
    movx @DPTR, A

    mov A, R3
    inc dptr
    movx @DPTR, A

    mov A, R4
    inc dptr
    movx @DPTR, A

    mov A, R5
    inc dptr
    movx @DPTR, A

    mov A, R6
    inc dptr
    movx @DPTR, A

    mov A, R7
    inc dptr
    movx @DPTR, A

    /* Accumulator check */
    mov A, #5Ah
    cjne A, #5Ah, LABEL_CPU_run_FAILURE   //For SW test breakpoint

    mov A, #0A5h
    cjne A, #0A5h, LABEL_CPU_run_FAILURE  //For SW test breakpoint

    mov R0, #0x5A
    cjne R0, #0x5A, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov R1, #0xa5
    cjne R1, #0xA5, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov R2, #0X5a
    cjne R2, #0x5a, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov r3, #0xa5
    cjne R3, #0xa5, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov R4, #0x5A
    cjne R4, #0x5A, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov R5, #0xa5
    cjne R5, #0xA5, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov R6, #0X5a
    cjne R6, #0x5a, LABEL_CPU_run_FAILURE //For SW test breakpoint
    mov r7, #0xa5
    cjne R7, #0xa5, LABEL_CPU_run_FAILURE //For SW test breakpoint

    mov DPTR, #CPU_TEST_PUSH_RAM
    movx A, @DPTR
    mov R0, A

    inc dptr
    movx A, @DPTR
    mov R1, A

    inc dptr
    movx A, @DPTR
    mov R2, A

    inc dptr
    movx A, @DPTR
    mov R3, A

    inc dptr
    movx A, @DPTR
    mov R4, A

    inc dptr
    movx A, @DPTR
    mov R5, A

    inc dptr
    movx A, @DPTR
    mov R6, A

    inc dptr
    movx A, @DPTR
    mov R7, A
    mov ret_flag, #CPU_OK
    jmp LABEL_end_of_CPU_run

LABEL_CPU_run_FAILURE:
    mov ret_flag, #CPU_FAILURE

LABEL_end_of_CPU_run :
    pop ACC
#pragma endasm
#endif

#if defined __ICC8051__  //iar cpu test flow
    __asm(
        "push ACC\n"  //Backup acc
        "mov A, R0\n"
        "mov DPTR, #(1024-16)\n" //xram 1024-16
        "movx @DPTR, A\n"

        "mov A, R1\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R2\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R3\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R3\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R4\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R5\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R6\n"
        "inc dptr\n"
        "movx @DPTR, A\n"

        "mov A, R7\n"
        "inc dptr\n"
        "movx @DPTR, A\n"
        /* Accumulator check */
        "mov A, #5Ah\n"
        "cjne A, #5Ah, LABEL_CPU_run_FAILURE\n"  //For SW test breakpoint
        "mov A, #0A5h\n"
        "cjne A, #0A5h, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint



        "mov R0, #0x5A\n"
        "cjne R0, #0x5A, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov R1, #0xa5\n"
        "cjne R1, #0xA5, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov R2, #0X5a\n"
        "cjne R2, #0x5a, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov r3, #0xa5\n"
        "cjne R3, #0xa5, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov R4, #0x5A\n"
        "cjne R4, #0x5A, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov R5, #0xa5\n"
        "cjne R5, #0xA5, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov R6, #0X5a\n"
        "cjne R6, #0x5a, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint
        "mov r7, #0xa5\n"
        "cjne R7, #0xa5, LABEL_CPU_run_FAILURE\n" //For SW test breakpoint

        "mov DPTR, #(1024-16)\n"
        "movx A, @DPTR\n"
        "mov R0, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R1, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R2, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R3, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R4, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R5, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R6, A\n"

        "inc dptr\n"
        "movx A, @DPTR\n"
        "mov R7, A\n"
        "mov ret_flag, #0x01\n"//0x0 is CPU_OK
        "sjmp LABEL_end_of_CPU_run\n"

        "LABEL_CPU_run_FAILURE:\n"
        "mov ret_flag, #0x00\n"//CPU_FAILURE

        "LABEL_end_of_CPU_run:\n"
        "pop ACC\n"
    );
#endif
    EA = BIT_TMP;  //reconver ea
}
