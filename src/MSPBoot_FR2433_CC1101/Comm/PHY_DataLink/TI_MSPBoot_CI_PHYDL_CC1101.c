/*
 * \file   TI_MSPBoot_CI_PHYDL_USCI_CC110x.c
 *
 * \brief  Driver for CC110x Physical-DataLink layers using SPI
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

//
// Include files
//
#include "msp430.h"
#include "TI_MSPBoot_Common.h"
#include "TI_MSPBoot_CI.h"
#include "TI_MSPBoot_AppMgr.h"
#include "radio_drv.h"
#include "cc1x_utils.h"
#include "hal_spi_rf.h"
#include "hal_timer.h"

#define TX_BUF_SIZE 24

uint8_t ii;
unsigned short rx_length;

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
 * @brief   Initializes the USCI CC110x interface
 *  - Sets corresponding GPIOs for CC110x functionality
 *  - Resets and then configures the CC110x module
 *  - Initializes the CC110x state machine
 *  - Initializes the CC110x callbacks
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
	/* initialize the radio subsystem */
	radio_init(3);

	/* configure the rx frequency to 902750 */
	radio_set_freq(CONFIG_CI_PHYDL_CC1101_FREQUENCY);

	// Set the packet length to a fixed packet size
	set_rf_packet_length(TX_BUF_SIZE);
  
    // Initialize all callbacks
    CI_Callback_ptr = CI_Callback;
    // Init state machine
    CI_State_Machine = USCI_STATE_IDLE;
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
	unsigned char txBuffer[TX_BUF_SIZE];

	/* configure the timer for a 1 second tick */
	hal_timer_init(32768);

	/* Initialize the RX chain, receive packet */
	radio_receive_on();

	// wait until end_of_packet is found, no timeout
	//status = radio_wait_for_idle(640);

	if(radio_wait_for_idle(1024) < 1024)
	{
		rx_length = TX_BUF_SIZE;
		radio_read(txBuffer, &rx_length);         // read content of FIFO

		if(txBuffer[0] == 0x80 && txBuffer[1] > 0 && txBuffer[1] <= 20)
		{
			if (txBuffer[1] == 1) rx_length = 5;
			else rx_length = txBuffer[1] + 8;
			for (ii = 0; ii < rx_length; ii++)
			{
				{
					if (CI_Callback_ptr->RxCallback != NULL)
					{
						// Call RX Callback (if valid) and send byte to upper layer
						CI_Callback_ptr->RxCallback(txBuffer[ii]);
					}
				}
			}
		}
		else
		{
			if (CI_Callback_ptr->RxCallback != NULL)
			{
				// Call RX Callback (if valid) and send byte to upper layer
				CI_Callback_ptr->RxCallback(txBuffer[0]);
			}
		}
	}
	else
	{
		// Check to see if we have lost the connection and we need to stop and hold
		radio_idle();                          // force idle and flush fifos
		// if max_wait == 0 that means we are waiting for first sync burst to appear
	}

}   // TI_MSPBoot_CI_PHYDL_Poll


/******************************************************************************
*
 * @brief   Sends a byte via CC110x. Function added for CC110x CI.
 *  
 *  @param  byte     byte to send
 *
 * @return  none
 *****************************************************************************/
void TI_MSPBoot_CI_PHYDL_TXByte(uint8_t byte)
{
	unsigned char txBuffer[TX_BUF_SIZE];

	rx_length = TX_BUF_SIZE;

	// put single byte into the payload, clear the rest
	txBuffer[0] = byte;
	for (ii = 1; ii < rx_length; ii++) txBuffer[ii] = 0;

	// Transmit packet. The MCU does not exit this until the TX is complete.
	radio_send(txBuffer, rx_length);
	radio_wait_for_idle(0);         // 0 = no timeout, just wait

	radio_receive_on();

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
__root const uint16_t Boot2App_Vector_Table[] =
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




