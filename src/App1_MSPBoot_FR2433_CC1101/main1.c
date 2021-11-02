/*
 * \file   main.c
 *
 * \brief  Sample application for FR2433 using MSPBoot
 *      This example places application in the appropriate area
 *      of memory (check linker file) and shows how to use interrupts 
*/
/* --COPYRIGHT--,BSD-3-Clause
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//Need to change
//Simple change: Realize functions same with the example code. You can search "Simple change" to find where need to be changed.
//You can make more changes to add more functions based on your applicaiton

#include "msp430.h"
#include <stdint.h>
#include "TI_MSPBoot_Mgr_Vectors.h"

/******************************************************************************
 *
 * @brief   Main function
 *  This example application performs the following functions:
 *  - Toggle LED1 (P1.0) at startup (to indicate App1 execution)
 *  - Toggles LED1 using a timer periodic interrupt (demonstrates vector redirection)
 *  - Forces Boot mode when button S2 (P2.7) is pressed (demonstrates vector
 *      redirection and Boot Mode call
 *
 * @return  none
 *****************************************************************************/

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
//Simple change start
    // Toggle LED1 in P1.0
    P1DIR |= BIT0;
    P1OUT |= BIT0;
    PM5CTL0 &= ~LOCKLPM5; //unlock GPIOs so settings take effect
    __delay_cycles(500000);
    P1OUT &= ~BIT0;
    __delay_cycles(500000);
    P1OUT |= BIT0;
    __delay_cycles(500000);
    P1OUT &= ~BIT0;

    // Start P2.7 (S2 button) as interrupt with pull-up
    P2OUT |= BIT7;
    P2REN |= BIT7;
    P2IES |= BIT7;
    P2IE |= BIT7;
    P2IFG &= ~BIT7;

    // Start Timer interrupt
    TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
    TA0CCR0 = 1000-1;
    TA0CTL = TASSEL_1 + MC_1;                  // ACLK, upmode
//Simple change end
    __bis_SR_register(LPM3_bits + GIE);
    __no_operation();


  return 0;
}

/******************************************************************************
 *
 * @brief   Timer A Interrupt service routine
 *  This routine simply toggles an LED but it shows how to declare interrupts
 *   in Application space
 *   Note that this function prototype should be accessible by 
 *   TI_MSPBoot_Mgr_Vectors.c
 *
 * @return  none
 *****************************************************************************/
//Simple change start
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= BIT0;                            // Toggle P1.0
  TA0CCTL0 &= ~CCIFG;
}

/******************************************************************************
 *
 * @brief   Port 1 Interrupt service routine
 *  Forces Boot mode when button S2 (P1.1) is pressed
 *   Note that this function prototype should be accessible by TI_MSPBoot_Mgr_Vectors.c
 *
 * @return  none
 *****************************************************************************/
#pragma vector = PORT2_VECTOR
__interrupt void Port2_Isr(void)
{
    P2IFG = 0;
    TI_MSPBoot_JumpToBoot();
}
//Simple change  end
