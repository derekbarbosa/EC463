/* --COPYRIGHT--,BSD
 * Copyright (c) 2020, Texas Instruments Incorporated
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
//*****************************************************************************
//        GUI HAL for MSP430FR2xxx using UART
//
// Driver to send and receive data from GUI using FR2xxx UART
// Texas Instruments, Inc.
// *****************************************************************************
#include "HAL_Config_Private.h"
#include "HAL.h"

tGUICommRXCharCallback RxByteISRCallback;

void HAL_GUI_Init(tGUICommRXCharCallback RxByteCallback)
{
    // Store callback for ISR RX Byte
    RxByteISRCallback = RxByteCallback;

    // Configure UART for FR2xxx
    UCAnCTLW0 |= UCSWRST;
    UCAnCTLW0 |= UCSSEL__SMCLK;

#if ((HAL_GUICOMM_BAUDRATE == 9600) && (HSBUS_FREQ_MHZ == 1))
    // Baud Rate calculation
    // 1000000/(16*9600) = 6.51
    // Fractional portion = 0.51
    // User's Guide Table 17-4: UCBRSx = 0x20
    // UCBRFx = 8
    UCAnBR0 = 6;
    UCAnBR1 = 0x00;
    UCAnMCTLW = 0x2000 | UCOS16 | UCBRF_8;
#elif ((HAL_GUICOMM_BAUDRATE == 28800) && (HSBUS_FREQ_MHZ == 8))
    // Baud Rate calculation
    // 8E6/(16*28800) = 17.36
    // Fractional portion = 0.36
    // From eUSCI Calculator: UCBRSx = 221 (0xDD)
    // UCBRFx = 5
    UCAnBR0 = 17;
    UCAnBR1 = 0x00;
    UCAnMCTLW = (0xDD<<8) | UCOS16 | UCBRF_5;
#elif ((HAL_GUICOMM_BAUDRATE == 19200) && (HSBUS_FREQ_MHZ == 8))
    // Baud Rate calculation
    // 8E6/(16*19200) = 26.04
    // Fractional portion = 0.04
    // User's Guide Table 17-4: UCBRSx = 0xB6
    // UCBRFx = 0
    UCAnBR0 = 26;
    UCAnBR1 = 0x00;
    UCAnMCTLW = (0xB6<<8) | UCOS16 | UCBRF_0;
#elif ((HAL_GUICOMM_BAUDRATE == 115200) && (HSBUS_FREQ_MHZ == 8))
    // Baud Rate calculation
    // 8E6/(16*115200) = 4.34
    // Fractional portion = 0.34
    // User's Guide Table 22-5: UCBRSx = 0x55
    // UCBRFx = 5
    UCAnBR0 = 4;
    UCAnBR1 = 0x00;
    UCAnMCTLW = (0x55<<8) | UCOS16 | UCBRF_5;
#elif ((HAL_GUICOMM_BAUDRATE == 115200) && (HSBUS_FREQ_MHZ == 16))
    // Baud Rate calculation
    // 16E6/(16*115200) = 8.68
    // Fractional portion = 0.68
    // User's Guide Table 22-5: UCBRSx 0xF7
    // UCBRFx = 10
    UCAnBR0 = 8;
    UCAnBR1 = 0x00;
    UCAnMCTLW = (0xF7<<8) | UCOS16 | UCBRF_10;
#elif ((HAL_GUICOMM_BAUDRATE == 9600) && (HSBUS_FREQ_MHZ == 8))
    // Baud Rate calculation
    // 8E6/(16*9600) = 52.0833
    // Fractional portion = 0.33
    // User's Guide Table 17-4: UCBRSx = 0x49
    // UCBRFx = 1
    UCAnBR0 = 52;
    UCAnBR1 = 0x00;
    UCAnMCTLW = (0x49<<8) | UCOS16 | UCBRF_1;
#else
#error "Define UART baudrate registers based on desired frequency"
#endif

    UCAnCTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCAnIE |= UCRXIE;
}

void HAL_GUI_TransmitCharBlocking(char character)
{
    // Transmit Character
    while (UCAnSTATW & UCBUSY)
        ;
    while (!(UCAnIFG & UCTXIFG))
        ;
    UCAnTXBUF = character;
    while (UCAnSTATW & UCBUSY)
        ;
}

// EUSCI interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_An_VECTOR
__interrupt void USCI_An_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_An_VECTOR))) USCI_An_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(UCAnIV,USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            if (RxByteISRCallback != NULL)
            {
                 if (RxByteISRCallback(UCAnRXBUF) == true)
                 {
                     __bic_SR_register_on_exit(LPM4_bits);   // Exit LPM
                 }
            }
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}

