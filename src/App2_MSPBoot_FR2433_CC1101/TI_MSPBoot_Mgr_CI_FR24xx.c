/*
 * \file   TI_MSPBoot_Mgr_CI_FR24xx.c
 *
 * \brief  Manager of the shared communication interface
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

#include "msp430.h"
#include <stdint.h>
#include "TI_MSPBoot_Mgr_CI.h"

//
//  External variables from linker file
//
/*! Address of table with Vectors/functions shared by boot:
USI:
    [0] = TI_MSPBoot_CI_Init
    [1] = TI_MSPBoot_CI_Poll
    [2] = TI_MSPBoot_CI_PHYDL_TXByte
 */
extern uint32_t _BOOT_APPVECTOR[3];

//
//  Global variables
//
t_CI_Callback CI_App_Callbacks;


/******************************************************************************
 *
 * @brief   Initializes the Shared Comm Interface
 *  Sends the corresponding Callback routines and initializes interrupts (default
 *  PI interface uses polling)
 *
 * @param RxCallback        Pointer to RX Callback
 * @param TxCallback        Pointer to TX Callback
 * @param ErrorCallback     Pointer to Error Callback
 *
 * @note The TI_MSPBoot_CI_Init function has the following prototype:
 *  void TI_MSPBoot_CI_PHYDL_Init(t_CI_Callback * CI_Callback);
 *  Sending a callback =NULL means that the callback won't be implemented/used
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_Comm_Init(  void (*RxCallback)(uint8_t),
                            void (*TxCallback)(uint8_t *),
                            void (*ErrorCallback)(uint8_t))
{
    // Fill the structure
    CI_App_Callbacks.RxCallback = RxCallback;
    CI_App_Callbacks.TxCallback = TxCallback;
    CI_App_Callbacks.ErrorCallback = ErrorCallback;
    // Call MSPBoot PI Init routine (TI_MSPBoot_CI_Init)
    ((void (*)()) (uint32_t) _BOOT_APPVECTOR[0]) (&CI_App_Callbacks);
}

/******************************************************************************
 *
 * @brief   Calls the poll routine from shared communication interface
 *
 * @note The TI_MSPBoot_CI_Init function has the following prototype:
 *  void TI_MSPBoot_CI_PHYDL_Poll(void);
 *  but the function will call the corresponding callbacks
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_Comm_Poll( void )
{
    // Call MSPBoot PI poll routine (TI_MSPBoot_CI_Poll). This will eventually
    // call the corresponding callback
    ((void (*)()) (uint32_t) _BOOT_APPVECTOR[1]) ();
}

/******************************************************************************
 *
 * @brief   Sends a byte to the Communication interface
 *
 * @note This function is not supported in CC110x CI.
 *      The TI_MSPBoot_CI_PHYDL_TXByte function has the following prototype:
 *  void TI_MSPBoot_CI_PHYDL_TXByte(uint8_t byte);
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_Comm_TxByte( uint8_t byte )
{
    // Call MSPBoot PI TXByte (TI_MSPBoot_CI_PHYDL_TXByte).
    ((void (*)())  (uint32_t) _BOOT_APPVECTOR[2]) (byte);
}

