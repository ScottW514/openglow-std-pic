/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: common.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _COMMON_H
#define _COMMON_H

#define _XTAL_FREQ  8000000

#define _VERSION 0x0103 // MSB=Major, LSB=Minor
#define _VENDOR  0x4F47 // 'OG'

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "adc.h"
#include "i2c.h"
#include "iref.h"
#include "leds.h"

#endif  // _COMMON_H
