/*
 * \file   TI_MSPBoot_CI_PHYDL_USCI_UART.c
 *
 * \brief  Driver for UART Physical-DataLink layers using USCI
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
//Need to change
//Simple change: Realize functions same with the example code. You can search "Simple change" to find where need to be changed.
//You can make more changes to add more functions based on your applicaiton
//
// Include files
//
#include "msp430.h"
#include "TI_MSPBoot_Common.h"
#include "TI_MSPBoot_CI.h"
#include "TI_MSPBoot_AppMgr.h"

//
//  Configuration checks
//
#ifndef MSPBoot_CI_UART
#   error "This file uses the UART interface"
#endif
// Baudrate configuration, check User's guide for table with values of 
// UCBRx, UCBRSx, UCBRFx and UCOS16
#if (MCLK==1000000)
#   if (CONFIG_CI_PHYDL_UART_BAUDRATE == 9600)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    6
#       define UCBRSx_VAL   0x20
#       define UCBRFx_VAL   8
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 57600)
#       define UCOS16_VAL   0
#       define UCBRx_VAL    17
#       define UCBRSx_VAL   0x4A
#       define UCBRFx_VAL   0
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 115200)
#       warning "Check error of UART using 115200 @ 1Mhz in User's Guide"
#       define UCOS16_VAL   0
#       define UCBRx_VAL    8
#       define UCBRSx_VAL   0xD6
#       define UCBRFx_VAL   0
#   else
#       error "Baudrate is not supported"
#   endif
#elif (MCLK==4000000)
#   if (CONFIG_CI_PHYDL_UART_BAUDRATE == 9600)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    26
#       define UCBRSx_VAL   0xB6
#       define UCBRFx_VAL   0
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 57600)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    4
#       define UCBRSx_VAL   0x55
#       define UCBRFx_VAL   5
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 115200)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    2
#       define UCBRSx_VAL   0xBB
#       define UCBRFx_VAL   2
#   else
#       error "Baudrate is not supported"
#   endif
#elif (MCLK==8000000)
#   if (CONFIG_CI_PHYDL_UART_BAUDRATE == 9600)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    52
#       define UCBRSx_VAL   0x49
#       define UCBRFx_VAL   1
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 57600)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    8
#       define UCBRSx_VAL   0xF7
#       define UCBRFx_VAL   10
#   elif (CONFIG_CI_PHYDL_UART_BAUDRATE == 115200)
#       define UCOS16_VAL   1
#       define UCBRx_VAL    4
#       define UCBRSx_VAL   0x55
#       define UCBRFx_VAL   5
#   else
#       error "Baudrate is not supported"
#   endif
#else
#error "Frequency is not supported"
#endif

//
//  Type Definitions
//
/*! State machine used by this communication interface 
 *   USCI doesn't require too much control, so we only check for an idle state
 *   and when receiving a packet 
 */
typedef enum {
    USCI_STATE_IDLE=0,          /*! Initialized state waiting for start */
    USCI_STATE_RECEIVING,       /*! Receiving packet */
}USCI_State_Machine_e;


//
//  Global variables
//
//    Note that these variables are assigned to a specific location in RAM
//    since they can also be used during application.
//    If not used by application, the location doesn't matter.
//
/*! Pointer to the Communication Interface callback structure 
 *   The NWK layer will define its callback structure and pass the pointer to
 *   this layer. An application can also declare its own structure and pass it
 *   to this layer in order to use the same interface.
 *   Note that the declaration for IAR and CCS is different.
 */
#ifdef __IAR_SYSTEMS_ICC__
#pragma location="RAM_CICALLBACK"
__no_init t_CI_Callback  * CI_Callback_ptr;
#elif defined (__TI_COMPILER_VERSION__)
extern t_CI_Callback  * CI_Callback_ptr;
#endif

/*! State machine used by this interface. 
 *   Note that the declaration for IAR and CCS is different.
 */
#ifdef __IAR_SYSTEMS_ICC__
#pragma location="RAM_CISM"
__no_init USCI_State_Machine_e CI_State_Machine;
#elif defined (__TI_COMPILER_VERSION__)
extern USCI_State_Machine_e CI_State_Machine;
#endif


//
//  Local function prototypes
//

//
//  Function declarations
//
/******************************************************************************
*
 * @brief   Initializes the USCI UART interface
 *  - Sets corresponding GPIOs for UART functionality
 *  - Resets and then configures the UART module
 *  - Initializes the UART state machine
 *  - Initializes the UART callbacks
 *  The NWK layer will define its callback structure and pass the pointer to
 *   this function. An application can also declare its own structure and call
 *   this function in order to use the same interface.
 *
 *  @param  CI_Callback     Pointer to Communication interface callbacks
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_Init(t_CI_Callback * CI_Callback)
{
  //Simple change start
    UCA0CTLW0 = UCSWRST | UCSSEL_2;          // USCI held in reset and use SMCLK

    P1SEL1 &= ~(BIT4 | BIT5);                 // Enable P1[4:5] for USCI_A0 UART mode
    P1SEL0 |= (BIT4 | BIT5);                //

   // UCA0BR0 = (UCBRx_VAL & 0xFF);           // Set Low baudrate byte
   // UCA0BR1 = (UCBRx_VAL >> 8);             // Set high baudrate byte
   // UCA0MCTLW = UCOS16_VAL |                 // Set modulation values
   //           (UCBRSx_VAL << 8) |
   //           (UCBRFx_VAL << 4) ;
    UCA0BR0 = 52;                             // 8000000/16/9600
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x4900 | UCOS16 | UCBRF_1;

    UCA0CTLW0 &= ~UCSWRST;                   // Clear SW reset, resume operation
//Simple change end
    // Initialize all callbacks
    CI_Callback_ptr = CI_Callback;
    // Init state machine
    CI_State_Machine = USCI_STATE_IDLE;
}

/******************************************************************************
 *
 * @brief   Disables the USCI module
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_disable(void)
{
    UCA0CTLW0 |= UCSWRST; //Simple change
}

/******************************************************************************
 *
 * @brief   Enables the USCI module
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_reenable(void)
{
    UCA0CTLW0 &= ~UCSWRST; //Simple change
}

/******************************************************************************
*
 * @brief   Polls for USCI flags
 *  - Checks the RX, TX flags
 *  - Calls the corresponding Callback functions and informs 
 *    higher level layers, so they can handle data properly
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_Poll(void)
{
    uint8_t temp;
    uint8_t flag_ifg2;
    
    // Read flags at the beginning of function 
    // New detected flags will be handled in the next poll
    flag_ifg2 = UCA0IFG;         //Simple change

    if (flag_ifg2 & UCRXIFG)     // Check the RX flag
    {
        temp = UCA0RXBUF;        // Get received byte//Simple change
        if (CI_Callback_ptr->RxCallback != NULL)
        {
            // Call RX Callback (if valid) and send byte to upper layer
            CI_Callback_ptr->RxCallback(temp);
        }
    }
    else if (flag_ifg2 & UCTXIFG)     // Check for TX flag
    {
        // Send ACK after byte reception
        if (CI_Callback_ptr->TxCallback != NULL)
        {
            // Call TXCallback (if valid) and get byte to send from upper layer
            CI_Callback_ptr->TxCallback(&temp);     
            UCA0TXBUF = temp;        // Send byte//Simple change
        }
    }
    // If necessary and if enough space is available, UCA0STAT can be checked
    // for errors and ErrorCallback can be called

}   // TI_MSPBoot_CI_PHYDL_Poll


/******************************************************************************
*
 * @brief   Sends a byte via UART. Function added for UART CI. 
 *  
 *  @param  byte     byte to send
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_TXByte(uint8_t byte)
{
    while (!(UCA0IFG & UCTXIFG));  // USCI_A0 TX buffer ready?//Simple change
    UCA0TXBUF = byte;           // TX data byte               //Simple change
}

//  Constant table
//
/*! Peripheral Interface vectors for Application:
 *  These vectors are shared with application and can be used by the App to
 *   initialize and use the Peripheral interface
 *   Note that the declaration for IAR and CCS is different.
 */
#   ifdef CONFIG_CI_PHYDL_COMM_SHARED
#       ifdef __IAR_SYSTEMS_ICC__
#           pragma location="BOOT_APP_VECTORS"
__root const uint32_t Boot2App_Vector_Table[] =
#       elif defined (__TI_COMPILER_VERSION__)
#           pragma DATA_SECTION(Boot2App_Vector_Table, ".BOOT_APP_VECTORS")
#           pragma RETAIN(Boot2App_Vector_Table)
const uint32_t Boot2App_Vector_Table[] =
#       endif
{
    (uint32_t) &TI_MSPBoot_CI_PHYDL_Init,       /*! Initialization routine */
    (uint32_t) &TI_MSPBoot_CI_PHYDL_Poll,       /*! Poll routine */
    (uint32_t) &TI_MSPBoot_CI_PHYDL_TXByte      /*! Transmit byte */
};
#endif  //CONFIG_CI_PHYDL_COMM_SHARED



