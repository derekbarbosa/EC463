/*
 * \file   main2.c
 *
 * \brief  Second sample application for FR2433 using MSPBoot
 *      This example places application in the appropiate area
 *      of memory (check linker file), shows how to use 
 *      interrupts and how to use the shared communication module
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
#include "TI_MSPBoot_Mgr_CI.h"
#include "TI_MSPBoot_Mgr_Vectors.h"

// 
// Global variables
//
static uint8_t RxByte;     /*! Byte received from UART */
static uint8_t new_data;   /*! Flag to indicate new data reception */

//
// Function prototypes
//

static void App_Comm_Rx(uint8_t data);


/******************************************************************************
 *
 * @brief   Main function
 *  This example application performs the following functions:
 *  - Toggle LED2 (P1.1) at startup (to indicate App2 execution)
 *  - Toggles LED2 when button S2 (P2.7) is pressed (demonstrates vector
 *      redirection)
 *  - Uses the shared UART API from MSPBoot detecting some application commands
 *      (demonstrates MSPBoot PI sharing)
 *  - Jumps to Bootloader when the corresponding UART command is detected
 *
 * @return  none
 *****************************************************************************/

int main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
//Simple change start
    // init LED1 on P1.0
    P1DIR = BIT0;
    P1OUT &= ~BIT0;
    // Toggle LED2 in P1.1
    P1DIR = BIT1;
    P1OUT = BIT1;
    //unlock GPIOs
    PM5CTL0 &= ~LOCKLPM5;
    __delay_cycles(500000);
    P1OUT &= ~BIT1;
    __delay_cycles(500000);
    P1OUT |= BIT1;
    __delay_cycles(500000);
    P1OUT &= ~BIT1;

    // Start P2.7 (S2 button) as interrupt with pull-up
    P2OUT |= BIT7;
    P2REN |= BIT7;
    P2IES |= BIT7;
    P2IE |= BIT7;
    P2IFG &= ~BIT7;
//Simple change end
    /* If the MSPBoot supports it, initialize the shared comm interface
        Note that this function will fail if the comm is not shared and the init
        vector is invalid 
        This example only uses the RX and TX callbacks
        The error callback is not implemented
    */
    TI_MSPBoot_Comm_Init(App_Comm_Rx, NULL, NULL);


    new_data = 0;

    while (1)
    {
        __bis_SR_register(LPM3_bits + GIE);
        __disable_interrupt();

        if (new_data ==1)
        {
            switch (RxByte)
            {
                // Process byte received from Shared Comm
                case 0xAA:
                    // Force Boot mode
                    TI_MSPBoot_JumpToBoot();
                break;
                case 0x01:
                    // Toggle LED1 (P1.0)
                    P1OUT ^= BIT0;//Simple change
                break;
                case 0x02:
                    // Toggle LED2 (P1.1)
                    P1OUT ^= BIT1;//Simple change
                break;
                default:
                    // Toggle both LEDs
                    P1OUT ^= BIT0;//Simple change
                    P1OUT ^= BIT1;//Simple change
                break;
            }

            new_data = 0; // Clear flag
        }
    }

}

/******************************************************************************
 *
 * @brief   P1 Interrupt service routine
 *  This routine simply toggles an LED but it shows how to declare interrupts
 *   in Application space
 *   Note that this function prototype should be accessible by TI_MSPBoot_Mgr_Vectors.c
 *
 * @return  none
 *****************************************************************************/
//Simple change start
#pragma vector = PORT2_VECTOR
__interrupt void P2_Isr(void)
{
    P2IFG = 0;
    P1OUT ^= BIT1;
}
//Simple change end

/******************************************************************************
 *
 * @brief   RXCallback for Shared Comm interface
 *  This function demonstrates how to receive data from the shared Communication
 *  interface. Function is called by MSPBoot when a byte is received from the host
 *
 *   Note that this function prototype should be accessible by TI_MSPBoot_Mgr_PI.c
 *   and is called by TI_MSPBoot_Comm_Init
 *
 * @return  none
 *****************************************************************************/
static void App_Comm_Rx(uint8_t data)
{
    RxByte = data;
    new_data = 1;
}


