/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define INT0    0
#define INT1    1

#define Level   0
#define Edge    1

void ExternPinInterrupt_Enable( unsigned char u8EXNum, unsigned char u8EXTTRG, unsigned char u8EXINT);
