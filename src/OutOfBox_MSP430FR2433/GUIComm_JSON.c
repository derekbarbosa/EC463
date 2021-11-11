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
//         GUI Communication Layer
//
// API to communicate with GUI using JSON protocol
// Texas Instruments, Inc.**

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include <HAL.h>
#include <MSP430_GUI/GUI_JSON.h>
#include <GUIComm.h>
#include <QmathLib.h>

static void itoa(int32_t value, char* result);

static const char cmdTemplate[] = "{\"\":}\n";
static char cATXString[20];

//These values are used to concatenate the command and data to the command template
// when using the GUIComm_send functions
#define CMD_INDEX 1
#define DATA_INDEX 3
#define CMD_TEMPLATE_LENGTH 6
#define BASE 10


//! \brief Converts a number into a string
//!
//! \return none
void itoa(int32_t value, char* result)
{
    char* ptr = result, *ptr1 = result, tmp_char;
    uint32_t tmp_value;

    tmp_value = labs(value);
    do {
    *ptr++ = "0123456789" [tmp_value%BASE];
    tmp_value /= BASE;
    } while (tmp_value);

    // Apply negative sign
    if (value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
    }
}

int GUIComm_sendUInt(char *cmd,  uint8_t cmdLength, uint32_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendInt(char *cmd, uint8_t cmdLength, uint32_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendUInt8(char *cmd, uint8_t cmdLength, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {

            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendInt8(char *cmd, uint8_t cmdLength, int8_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendInt16(char *cmd, uint8_t cmdLength, int16_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendArrayStart(char *cmd, uint8_t cmdLength, bool multiData)
{
    uint8_t i;

    for (i = 0; i <= DATA_INDEX; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if ((i == DATA_INDEX) && (multiData == true))
        {
            HAL_GUI_TransmitCharBlocking('[');
        }
    }

    return 0;
}

int GUIComm_sendArrayNewCmd(char *cmd, uint8_t cmdLength, bool multiData)
{
    if (multiData == true)
    {
        HAL_GUI_TransmitCharBlocking(']');
    }
    HAL_GUI_TransmitCharBlocking(',');
    HAL_GUI_TransmitCharBlocking('\"');
    GUI_TransmitStringBlocking(cmd);
    HAL_GUI_TransmitCharBlocking('\"');
    HAL_GUI_TransmitCharBlocking(':');
    if (multiData == true)
    {
        HAL_GUI_TransmitCharBlocking('[');
    }

    return 0;
}

int GUIComm_sendArrayEnd(bool multiData)
{
    uint8_t i;

    if (multiData == true)
    {
        HAL_GUI_TransmitCharBlocking(']');
    }
    for (i = DATA_INDEX+1; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
    }

    return 0;
}

int GUIComm_sendQ8DataAsFloat(int16_t val, bool first)
{
    if (first != true)
    {
        HAL_GUI_TransmitCharBlocking(',');
    }
    _Q8toa(cATXString, "%2.2f", val);
    GUI_TransmitStringBlocking(cATXString);
    return 0;
}

int GUIComm_sendUInt16(char *cmd, uint8_t cmdLength, uint16_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendUInt32(char *cmd, uint8_t cmdLength, uint32_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendInt32(char *cmd, uint8_t cmdLength, int32_t val)
{
    uint8_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            itoa(val, cATXString);
            GUI_TransmitStringBlocking(cATXString);
        }
    }

    return 0;
}

int GUIComm_sendBool(char *cmd, uint8_t cmdLength, bool val)
{
    uint16_t i;

    for (i = 0; i < CMD_TEMPLATE_LENGTH; i++)
    {
        HAL_GUI_TransmitCharBlocking(cmdTemplate[i]);
        if (i == CMD_INDEX)
        {
            GUI_TransmitStringBlocking(cmd);
        }
        else if (i == DATA_INDEX)
        {
            if (val == true)
            {
                GUI_TransmitStringBlocking("true");
            }
            else
            {
                GUI_TransmitStringBlocking("false");
            }
        }
    }

    return 0;
}

