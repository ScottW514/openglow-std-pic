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

#define LED_LID     0x0
#define LED_BTN_R   0x1
#define LED_BTN_G   0x2
#define LED_BTN_B   0x3

#define BTN_R_INIT_VALUE 0x000
#define BTN_G_INIT_VALUE 0x000
#define BTN_B_INIT_VALUE 0x000
#define LID_INIT_VALUE   0x1F4

#ifdef __cplusplus
    extern "C" {
#endif

/*
 Initialize LEDs 
*/
void LED_Init(void);

/*
 Set LED Duty Cycle
*/
void LED_Set_DutyCycle(uint8_t, uint16_t);

/*
 Get LED Duty Cycle
*/
uint16_t LED_Get_DutyCycle(uint8_t);

#ifdef __cplusplus
    }
#endif

#endif  // _LEDS_H
