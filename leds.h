/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

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
