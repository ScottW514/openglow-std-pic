/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: iref.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _IREF_H
#define _IREF_H

#include "common.h"

#ifdef __cplusplus
    extern "C" {
#endif

#define X_IREF 0x1
#define Y_IREF 0x2


/*
 Initialize IREF
*/
void IREF_Init(void);

/*
 Process IREF Events
*/
void IREF_SetOutput(uint8_t, uint16_t);

#ifdef __cplusplus
    }
#endif

#endif  // _IREF_H
