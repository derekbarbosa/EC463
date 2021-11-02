/*
 * \file   main.c
 *
 * \brief  Main routine for the bootloader for FR2433
 *
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
//               MSP430FR2433    CC1101              MSP430F2433      CC1101
//                   Host                               Target
//          ----------------    -------           -----------------   -------
//          |     P2.6/SIMO |-->|     |           |     P2.6/SIMO |-->|     |
//          |     P2.5/SOMI |<--|     |           |     P2.5/SOMI |<--|     |
//          |      P2.4/CLK |-->|     |           |      P2.4/CLK |-->|     |
//   LED <--|P1.0   P2.2/SS |<--|     |    LED <--|P1.0   P2.2/SS |<--|     |
//   LED <--|P2.1       GND |<--|     |    LED <--|P2.1       GND |<--|     |
//          -----------------   -------           -----------------   -------
//
//Need to change
//Simple change: Realize functions same with the example code. You can search "Simple change" to find where need to be changed.
//You can make more changes to add more functions based on your applicaiton

//  Include files
//
#include "msp430.h"
#include "TI_MSPBoot_Common.h"
#include "TI_MSPBoot_CI.h"
#include "TI_MSPBoot_MI.h"
#include "TI_MSPBoot_AppMgr.h"

//
//  Local function prototypes
//

void Software_Trim();                       // Software Trim to get the best DCOFTRIM value
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz

static void clock_init(void);
static void HW_init(void);

/******************************************************************************
 *
 * @brief   Main function
 *  - Initializes the MCU
 *  - Selects whether to run application or bootloader
 *  - If bootloader:
 *      - Initializes the peripheral interface
 *      - Waits for a command
 *      - Sends the corresponding response
 *  - If application:
 *      - Jump to application
 *
 * @return  none
 *****************************************************************************/
int main_boot( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    
    // Initialize MCU
    HW_init();
    clock_init();

    // Validate the application and jump if needed
    if (TI_MSPBoot_AppMgr_ValidateApp() == TRUE_t)
        TI_MSPBoot_APPMGR_JUMPTOAPP();

    TI_MSPBoot_CI_Init();      // Initialize the Communication Interface
//Simple change start
    P1DIR |= BIT0;     // Used for debugging purposes to show entry to MSPBoot
    P2DIR |= BIT1;
    P1OUT |= BIT0;
    P2OUT |= BIT1;
//Simple change end
    while(1)
    {
        // Poll PHY and Data Link interface for new packets
        TI_MSPBoot_CI_PHYDL_Poll();

        // If a new packet is detected, process it
        if (TI_MSPBoot_CI_Process() == RET_JUMP_TO_APP)
        {
            // If Packet indicates a jump to App
            TI_MSPBoot_AppMgr_JumpToApp();
        }
#ifdef NDEBUG
        // Feed the dog every ~1000ms
        WATCHDOG_FEED();
#endif
    }


}


/******************************************************************************
 *
 * @brief   Initializes the MSP430 Clock
 *
 * @return  none
 *****************************************************************************/
//inline static void clock_init(void)
static void clock_init(void)
{
    CSCTL1 = DCOFTRIMEN | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_3;                         // Set DCO = 8Mhz
    CSCTL2 = FLLD_0 + 243;                   // DCODIV = 8MHz
    __delay_cycles(3);
    __bic_SR_register(SCG0);                 // enable FLL
    Software_Trim();                         // Software Trim to get the best DCOFTRIM value
    CSCTL4 = SELA__REFOCLK + SELMS__DCOCLKDIV;                // set ACLK = VLO
                                                          // MCLK=SMCLK=DC
    
#if (MCLK==1000000)
    CSCTL5 = DIVS__8 + DIVM__8;                 // Divide DCO/8
#elif (MCLK==4000000)
    CSCTL5 = DIVS__2 + DIVM__2;                 // Divide DCO/2
    #elif (MCLK==8000000)
    CSCTL5 = DIVS__1 + DIVM__1;                          // Divide DCO/1
#else
#error "Please define a valid MCLK or add configuration"
#endif

}


/******************************************************************************
 *
 * @brief   Initializes the basic MCU HW
 *
 * @return  none
 *****************************************************************************/
static void HW_init(void)
{
//Simple change start
    // Just initialize S2 button to force BSL mode
    P2OUT |= BIT7;
    P2REN |= BIT7;

    P1DIR |= BIT3 ;            // set MCLK SMCLK and LED pin as output
    P1SEL1|= BIT3 ;                  // set MCLK and  SMCLK pin as second function
//Simple change end
    PM5CTL0 &= ~LOCKLPM5;
}




void Software_Trim()
{
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do
    {
        CSCTL0 = 0x100;                         // DCO Tap = 256
        do
        {
            CSCTL7 &= ~DCOFFG;                  // Clear DCO fault flag
        }while (CSCTL7 & DCOFFG);               // Test DCO fault flag

        __delay_cycles((unsigned int)3000 * MCLK_FREQ_MHZ);// Wait FLL lock status (FLLUNLOCK) to be stable
                                                           // Suggest to wait 24 cycles of divided FLL reference clock
        while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;                   // Read CSCTL0
        csCtl1Read = CSCTL1;                   // Read CSCTL1

        oldDcoTap = newDcoTap;                 // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;       // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070)>>4;// Get DCOFTRIM value

        if(newDcoTap < 256)                    // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;     // Delta value between DCPTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & (~(DCOFTRIM0+DCOFTRIM1+DCOFTRIM2))) | (dcoFreqTrim<<4);
            }
        }
        else                                   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;     // Delta value between DCPTAP and 256
            if(oldDcoTap < 256)                // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & (~(DCOFTRIM0+DCOFTRIM1+DCOFTRIM2))) | (dcoFreqTrim<<4);
            }
        }

        if(newDcoDelta < bestDcoDelta)         // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }

    }while(endLoop == 0);                      // Poll until endLoop == 1

    CSCTL0 = csCtl0Copy;                       // Reload locked DCOTAP
    CSCTL1 = csCtl1Copy;                       // Reload locked DCOFTRIM
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
}





