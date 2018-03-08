/*
    (C) Copyright 2018, Scott Wiederhold

    This file is part of OpenGlow Standard PIC Firmware.

    OpenGlow Standard PIC Firmware is free software: you can redistribute it 
    and/or modify it under the terms of the GNU General Public License as 
    published by the Free Software Foundation, either version 3 of the License,
    or (at your option) any later version.

    OpenGlow Standard PIC Firmware is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenGlow Standard PIC Firmware. If not, see 
    <http://www.gnu.org/licenses/>.
*/
/*
  Author: Scott Wiederhold
  File Name: leds.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _LEDS_H
#define _LEDS_H

#include "common.h"

#define BTN_R_INIT_VALUE 0x0
#define BTN_G_INIT_VALUE 0x0
#define BTN_B_INIT_VALUE 0x0
#define LID_INIT_VALUE 0x1F4

#define LED_BTN_RED_MSB 0xF0
#define LED_BTN_RED_LSB 0xF1
#define LED_BTN_GRN_MSB 0xF2
#define LED_BTN_GRN_LSB 0xF3
#define LED_BTN_BLU_MSB 0xF4
#define LED_BTN_BLU_LSB 0xF5
#define LED_LID_MSB 0xF6
#define LED_LID_LSB 0xF7

#ifdef __cplusplus
    extern "C" {
#endif

/*
 LED Duty Cycle Registers
*/
volatile uint16_t LED_BTN_RED;
volatile uint16_t LED_BTN_GRN;
volatile uint16_t LED_BTN_BLU;
volatile uint16_t LED_LID;

/*
 Initialize LEDs 
*/
void LED_Init(void);

/*
 Process LED Events
*/
void LED_ProcessWrite(uint8_t, uint8_t);

/*
 Load LED Duty Cycle Values
*/
void LED_LoadDutyCycles(void);

#ifdef __cplusplus
    }
#endif

#endif  // _LEDS_H
