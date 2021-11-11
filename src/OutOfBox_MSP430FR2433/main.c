/* --COPYRIGHT--,BSD
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
//******************************************************************************
//
//  main.c
//
//  Out of box demo for the MSP-EXP430FR2433
//
//  This demo uses the MSP432FR2433's internal Temperature Sensor and demonstrates
//  how to setup a periodic temperature data logger, by utilizing a ring-buffer
//  inside the MSP430F2433 device's FRAM memory. In addition, the demo also implements
//  a real time temperature sensor
//
//
//  E. Chen
//  Texas Instruments Inc.
//  October 2017
//******************************************************************************

#include "FRAMLogMode.h"
#include "LiveTempMode.h"
#include <MSP430_GUI/GUI_JSON.h>
#include <GUIComm.h>
#include <QmathLib.h>
#include <callbacks_JSON.h>


// ADC data
adc_data_t adc_data;

// NVS ring handle
nvs_ring_handle nvsHandle;

// FRAM storage for ADC samples using NVS ring storage
#if defined(__TI_COMPILER_VERSION__)
#pragma PERSISTENT(nvsStorage)
#elif defined(__IAR_SYSTEMS_ICC__)
__persistent
#endif
uint8_t nvsStorage[NVS_RING_STORAGE_SIZE(sizeof(adc_data_t), NVS_RING_SIZE)] = {0};

bool buttonS1Pressed;
bool buttonS2Pressed;
bool rtcWakeup;

// Application mode, selected between FRAM_LOG_MODE and LIVE_TEMP_MODE
char mode;

//! \brief RX Command structure.
//!         The corresponding callback will be called when the command is
//!         received from GUI.
//! Note: shorter command names take less time to process
const tGUI_RxCmd GUI_RXCommands[CALLBACKS_SIZE] =
{
     {"tempThreshold",    GUICallback_threshold},
};

// Function Definitions
void initRtc(void);
void initAdc(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Initialize clock, GPIOs
    HAL_System_Init();
    HAL_IO_InitButtons();

    // Initialize GUI layer
    GUI_Init();
    GUI_InitRxCmd( &GUI_RXCommands[0],CALLBACKS_SIZE );

    // Initialize RTC and ADC
    initRtc();
    initAdc();

    // Check integrity of NVS container and initialize if required;
    nvsHandle = nvs_ring_init(nvsStorage, sizeof(adc_data_t), NVS_RING_SIZE);

    /* Toggle P1.0 LED to indicated device start up. */
    P1OUT ^= BIT1;
    __delay_cycles(16000000);
    P1OUT ^= BIT1;

    P2IFG &= ~(BIT3 | BIT7);

    mode = 0;
    buttonS1Pressed = false;
    buttonS2Pressed = false;
    rtcWakeup = false;

    /* Enable global interrupts. */
    __enable_interrupt();

    /*
     * Enter into LPM3.5 with restore on reset disabled. The RTC interrupt will
     * toggle P2.0 each time the device wakes up.
     */
    while (1) {
        switch (mode)
        {
            case 0:
                framLog();
                break;
            case 1:
                thresholdChanged = true;
                liveTemp();
                break;
            default:
                break;
        }
    }
}

void initRtc(void)
{
    //Initialize RTC, interrupts roughly every 5 seconds
    RTCMOD = 50;
    RTCCTL = RTCSS__VLOCLK | RTCSR |RTCPS__1024;
    RTCCTL |= RTCIE;
}

void initAdc(void)
{
    //Initialize the ADC Module
    /*
     * Base Address for the ADC Module
     * Use internal ADC bit as sample/hold signal to start conversion
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC_init(ADC_BASE,
             ADC_SAMPLEHOLDSOURCE_SC,
             ADC_CLOCKSOURCE_ADCOSC,
             ADC_CLOCKDIVIDER_1);

    ADC_enable(ADC_BASE);

    /*
     * Base Address for the ADC Module
     * Sample/hold for 256 clock cycles
     * Do not enable Multiple Sampling
     */
    ADC_setupSamplingTimer(ADC_BASE,
                           ADC_CYCLEHOLD_1024_CYCLES,
                           ADC_MULTIPLESAMPLESDISABLE);

    //Configure the Memory Buffer
    /*
     * Base Address for the ADC Module
     * Use input A12
     * Use positive reference of AVcc
     * Use negative reference of AVss
     */
    ADC_configureMemory(ADC_BASE,
                        ADC_INPUT_TEMPSENSOR,
                        ADC_VREFPOS_INT,
                        ADC_VREFNEG_AVSS);

    ADC_clearInterrupt(ADC_BASE,
                       ADC_COMPLETED_INTERRUPT);

    //Enable the Memory Buffer Interrupt
    ADC_enableInterrupt(ADC_BASE,
                        ADC_COMPLETED_INTERRUPT);

    //Configure internal reference
    //If ref voltage no ready, WAIT
    while(PMM_REFGEN_NOTREADY ==
          PMM_getVariableReferenceVoltageStatus());

    PMM_enableTempSensor();

    //Internal Reference ON
    PMM_enableInternalReference();

//    __delay_cycles(500);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT2_VECTOR)))
#endif
void Port2_ISR(void)
{
    // Both buttons pressed
    if (!(P2IN & BIT3) && !(P2IN & BIT7))
    {
        P2IES |= BIT3 | BIT7;       // P2.3 P2.7 Hi/Lo edge
        P2IFG &= ~(BIT3 | BIT7);    // Clear P2.3 P2.7 IFG

        buttonS1Pressed = false;
        buttonS2Pressed = false;

        // Switch mode
        if (mode == FRAM_LOG_MODE)
            mode = LIVE_TEMP_MODE;
        else
            mode = FRAM_LOG_MODE;

        return;
    }
    // Left button S1
    if (P2IFG & BIT3)
    {
        P2IFG &= ~BIT3;

        // Left button S1 released
        if (P2IN & BIT3)
        {
            P2IES |= BIT3;       // P2.3 Hi/Lo edge
            buttonS1Pressed = true;

            if (mode == LIVE_TEMP_MODE && threshold > _Q8(-127))
            {
                threshold = threshold - _Q8(0.5);
                thresholdChanged = true;
            }
        }
        else
            P2IES &= ~BIT3;       // P2.3 Lo/Hi edge
    }
    // Right button S2
    if (P2IFG & BIT7)
    {
        P2IFG &= ~BIT7;

        // Right button S2 released
        if (P2IN & BIT7)
        {
            P2IES |= BIT7;       // P2.7 Hi/Lo edge
            buttonS2Pressed = true;

            if (mode == LIVE_TEMP_MODE && threshold < _Q8(127))
            {
                threshold = threshold + _Q8(0.5);
                thresholdChanged = true;
            }
        }
        else
            P2IES &= ~BIT7;       // P2.7 Lo/Hi edge
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_ISR(void)
{
    switch(__even_in_range(RTCIV, RTCIV_RTCIF)) {
        case RTCIV_NONE : break;
        case RTCIV_RTCIF:
            // Turn on LED1 P1.0
            P1OUT |= BIT0;
            rtcWakeup = true;

            break;
        default: break;
    }
}

//ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC_VECTOR)))
#endif
void ADC_ISR(void)
{
    switch(__even_in_range(ADCIV,12))
    {
        case ADCIV_NONE: break;       //No interrupt
        case ADCIV_ADCOVIFG: break;   //conversion result overflow
        case ADCIV_ADCTOVIFG: break;  //conversion time overflow
        case ADCIV_ADCHIIFG: break;   //ADC10HI
        case ADCIV_ADCLOIFG: break;   //ADC10LO
        case ADCIV_ADCINIFG: break;   //ADC10IN
        case ADCIV_ADCIFG:            //ADC10IFG0
            if (mode == FRAM_LOG_MODE)
                adc_data.value = ADC_getResults(ADC_BASE);
            else
                ADCIFG &= ~ADCIFG0;
            //Clear LPM3 bits from 0(SR)
            __bic_SR_register_on_exit(LPM3_bits);
            break;
        default: break;
    }
}

