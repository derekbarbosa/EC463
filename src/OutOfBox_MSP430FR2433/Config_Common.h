/* --COPYRIGHT--,BSD
 * Copyright (c) 2019, Texas Instruments Incorporated
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
//  Config_Common.h
//
//  Configuration definitions
// Texas Instruments, Inc.
#ifndef __CONFIG_COMMON_H__
#define __CONFIG_COMMON_H__

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(__TI_COMPILER_VERSION__)
#define __persistent
#define __no_init
#elif defined (__IAR_SYSTEMS_ICC__)
#else
#error Compiler not supported!
#endif

//! \brief CPU Active Frequency in Hz.
//!
#define CPU_FREQ_HZ                 (8000000)
//! \brief CPU Active Frequency in MHz.
//!
#define CPU_FREQ_MHZ                (CPU_FREQ_HZ/1000000)
//! \brief High Speed Bus Frequency in Hz.
//!         Used by High Speed peripherals such as UART.
//!
#define HSBUS_FREQ_HZ               (8000000)
//! \brief High Speed Bus Frequency in MHz.
//!         Used by High Speed peripherals such as UART.
//!
#define HSBUS_FREQ_MHZ              (HSBUS_FREQ_HZ/1000000)
//! \brief Low Speed Bus Frequency in Hz.
//!         Used by Low Speed peripherals such as LPM timers.
//!
#define LSBUS_FREQ_HZ               (32768)

#endif //__CONFIG_COMMON_H__
