/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

unsigned char uart4rvbuffer;
BIT uart4rvflag;

/**
 * @brief       SC2 / UART4 Interrupt vector demo 
 * @param       None
 * @return      None
 * @details     UART4 store received data.
 */
#if 0
#pragma vector=0xBB
__interrupt void SC2_UART4_ISR(void){
    PUSH_SFRS;
        uart4rvflag = 1;
        SFRS = 2;
        uart4rvbuffer = SC2DR;
    POP_SFRS;
}
#endif


/**
 * @brief       UART3 transfer data without interrupt 
 * @param       u32SysClock , define Fsys value(value)
 * @param       u32Baudrate, Define baudrate (value)
 * @return      none
 * @details     none
 * @example:    UART3_Open(24000000,115200)
 */ 
void UART4_Open(unsigned long u32SysClock, unsigned long u32Baudrate)
{
    set_SC2CR0_SCEN;         /* Enable SC module */
    set_SC2CR1_UARTEN;       /* set as UART mode */
    set_SC2CR1_CLKKEEP;      
    clr_SC2CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC2CR0_AUTOCEN;
    SC2ETURD0 = LOBYTE(u32SysClock/8/u32Baudrate-1);  /* define baud rate low byte */
    SC2ETURD1 &= 0xF0;                                /* define baud rate high byte */
    SC2ETURD1 |= (HIBYTE(u32SysClock/8/u32Baudrate-1))&0x0F; 
    set_SC2CR1_PBOFF;     //parity bit disable
    SC2CR1&=0xCF;        //datalegth 8bit
    set_SC2CR0_NSB;      //stop bit = 1bit
  }

/**
 * @brief       UART3 receive data without interrupt 
 * @param       baudrate value
 * @return      received data
 * @details     none
 * @example:    temp = UART3_Receive_Data()
 */ 
unsigned char UART4_Receive_Data()
{
    unsigned char c;

    clr_SC2CR0_RXOFF;
    while((SC2TSR&&SET_BIT1)==SET_BIT1);
    c = SC1DR;
    return (c);
}

/**
 * @brief       UART3 transfer data without interrupt 
 * @param       baudrate value
 * @return      none
 * @details     none
 * @example:    UART3_Send_Data(0x55)
 */ 
void UART4_Send_Data(unsigned char c)
{
    clr_SC2CR0_TXOFF;
    SC2DR = c;
    while(!(SC2TSR&SET_BIT3));
    clr_SC2CR0_TXOFF;
}


/**
 * @brief       UART interrupt enable setting 
 * @param       u8UARTPort: UART0/UART1/UART2/UART3 baudrate value
 * @param       u8UARTINTStatus: Disable/Enable
 * @return      none
 * @details     none
 * @note        max baud rate = 1.5MHz when Fsys = 24MHz
 * @example:    UART3_Interrupt(UART3_TXD,Enable)
 */
//void UART4_Interrupt(unsigned char u8UART4INTSel,unsigned char u8UART4INTStatus)
//{
//        switch (u8UART4INTSel)
//        {
//          case UART3_TXD:
//            switch(u8UART4INTStatus)
//            {
//              case Disable: DISABLE_SC2_TRASMIT_BUFFER_EMPTY_INTERRUPT;   break;
//              case Enable: ENABLE_SC2_TRASMIT_BUFFER_EMPTY_INTERRUPT;    break;
//            }break;
//          case UART3_RXD:
//            switch(u8UART4INTStatus)
//            {
//              case Disable:  DISABLE_SC2_RECEIVE_DATA_REACH_INTERRUPT;   break;
//              case Enable:   ENABLE_SC2_RECEIVE_DATA_REACH_INTERRUPT;   break;
//            }break;
//        }
//}


