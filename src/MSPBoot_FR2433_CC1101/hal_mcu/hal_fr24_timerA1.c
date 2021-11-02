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
/******************************************************************************
 *  Filename: hal_fr24_timerA1.c
 *
 *  Description: Timer abstration layer api
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************/
//Need to change
//Simple change: Realize functions same with the example code. You can search "Simple change" to find where need to be changed.
//You can make more changes to add more functions based on your applicaiton


#include "msp430.h"
#include "hal_timer.h"
#include "hal_spi_rf.h"

unsigned char volatile timer_event;
unsigned long volatile time_counter = 0;

/******************************************************************************
 * @fn         hal_timer_init
 *
 * @brief      Start packet timer using Timer using ACLK as reference
 *
 *
 * input parameters
 *
 * @param       unsigned int master_count - master packet timer value
 *
 * output parameters
 *
 * @return      void
 *
 */
//Simple change start
void hal_timer_init(unsigned int master_count) {

  // Start Timer 0 using the ACLK as a source (this enables the use of
  // various low power modes). Timer 0 will be used to keep RF burst time
  TA1CCR0  = master_count - 1;              // Seting for MASTER SCHEDULE
  TA1CCR1  = 0;                             // will be used for burst alignnment
  TA1CCR2  = 0;                             // will be used for expiration counter
  TA1CTL   = TASSEL_1 + MC_1 + TACLR + ID_0;// ACLK, Up to CCR0, clear TA1R, div/1

  return;
}


/******************************************************************************
 * @fn         hal_timer_adjust
 *
 * @brief      Align packet timer by modifying the main count value
 *
 *
 * input parameters
 *
 * @param       unsigned int adjust - modify the timer count value
 *
 * output parameters
 *
 * @return      void
 *
 */
void hal_timer_adjust(unsigned int adjust) {

  TA1R = adjust;

  return;
}

/******************************************************************************
 * @fn         hal_timer_get
 *
 * @brief      Get the current timer count value
 *
 *
 * input parameters
 *
 * @param       void
 *
 * output parameters
 *
 * @return      unsigned int timer count value
 *
 */
unsigned int hal_timer_get(void) {

	return(TA1R);
}


/******************************************************************************
 * @fn         hal_timer_get_time
 *
 * @brief      Calculate the time in seconds and milliseconds after last reset
 *
 *
 * input parameters
 *
 * @param       unsigned long *sec - pointer to seconds counter value
 *              unsigned long *ms  - pointer to millisecond count value
 *
 * output parameters
 *
 * @return      unsigned int timer count value
 *
 */
unsigned int hal_timer_get_time(unsigned long *sec, unsigned long *ms) {

	unsigned int ms_uint;
	unsigned long ms_long;

	/* grap the time counter values from the global value */
	*sec = time_counter;

	/* grap the time counter value (1/32768) second resolution */
	ms_uint = TA1R;

	/* convert information to milliseconds */
	ms_long = (unsigned long)ms_uint * 1000;
	ms_long = ms_long>>15;
	*ms = ms_long;

	/* return count value */
	return(ms_uint);
}

/******************************************************************************
 * @fn         hal_timer_stop
 *
 * @brief      Stop the timer
 *
 *
 * input parameters
 *
 * @param       void
 *
 * output parameters
 *
 * @return      void
 *
 */

void hal_timer_stop(void) {

  /* clear timer configuration register, stopping the timer */
  TA1CTL = 0;

  return;
}

/******************************************************************************
 * @fn         hal_timer_expire
 *
 * @brief      wait until the timer master count expires (for packet alignment)
 *
 *
 * input parameters
 *
 * @param       void
 *
 * output parameters
 *
 * @return      void
 *
 */
void hal_timer_expire(void) {
  
	while (!(TA1CCTL1 & CCIFG) && !(TA1CCTL2 & CCIFG));
	if (TA1CCTL1 & CCIFG) timer_event = TA1IV_TA1CCR1;
	else if (TA1CCTL2 & CCIFG) timer_event = TA1IV_TA1CCR2;
	TA1CCTL1 &= ~(CCIFG);
	TA1CCTL2 &= ~(CCIFG);
  
  return;
}

/******************************************************************************
 * @fn         hal_timer_wait
 *
 * @brief      wait an asigned amount of time or until a GPIO event (packet)
 *
 *
 * input parameters
 *
 * @param       unsigned int time  - maximum time to wait
 *
 * output parameters
 *
 * @return      unsigned int time - actual time waited
 *
 */
unsigned int hal_timer_wait(unsigned int time) {
  unsigned int wait_count, TAR_init;

  TAR_init = TA1R;   // store the current value of the timer register
  wait_count = TAR_init + time;

  // if the requested wait time exceeds the TACCR0 (max value) then make a loop
  while(wait_count > TA1CCR0) {

	  // configure the timeout for 1 less than the master clock
	  TA1CCR2  = TA1CCR0-1;

	  // calculate the remaining wait time remaining
	  wait_count = wait_count - (TA1CCR2 - TAR_init);

	  // do not count the initial timer values more that once, zero it out
	  timer_event = 0;
	  TAR_init = 0;

	  while (!(TA1CCTL1 & CCIFG) && !(TA1CCTL2 & CCIFG) && !(RF_GDO_PxIFG & RF_GDO_PIN));
	  if (TA1CCTL1 & CCIFG) timer_event = TA1IV_TA1CCR1;
	  else if (TA1CCTL2 & CCIFG) timer_event = TA1IV_TA1CCR2;
	  else if (RF_GDO_PxIFG & RF_GDO_PIN) timer_event = 0;
	  TA1CCTL1 &= ~(CCIFG);
	  TA1CCTL2 &= ~(CCIFG);
	  RF_GDO_PxIFG &= ~RF_GDO_PIN;


      // check to see if the timer woke us up or not
	  if (timer_event == 0)
		  // it did not, return imidiately and note time actual delay
		  return (time - (wait_count - TA1R));
  }

  // in the case of loop, this executes the remaining wait, in the case of no
  // loop this is the only wait that gets executed

  /* define maximum timeout by using timer counter 2 */
  TA1CCR2  = wait_count;

  while (!(TA1CCTL1 & CCIFG) && !(TA1CCTL2 & CCIFG) && !(RF_GDO_PxIFG & RF_GDO_PIN));
  if (TA1CCTL1 & CCIFG) timer_event = TA1IV_TA1CCR1;
  else if (TA1CCTL2 & CCIFG) timer_event = TA1IV_TA1CCR2;
  else if (RF_GDO_PxIFG & RF_GDO_PIN) timer_event = 0;
  TA1CCTL1 &= ~(CCIFG);
  TA1CCTL2 &= ~(CCIFG);
  RF_GDO_PxIFG &= ~RF_GDO_PIN;

/* return the time spend in sleep */
  if (timer_event == 0) return 0;
  else return (time - (wait_count-TA1R));

}

//Simple change end
