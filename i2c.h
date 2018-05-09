/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: i2c.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _I2C_H
#define _I2C_H

#include "common.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*
 I2C Driver Status
 */

typedef enum
{
    I2C_W_REQ,
    I2C_R_REQ,
    I2C_W_DATA,
    I2C_R_COMPLETED,
} I2C_DRIVER_STATUS;

/*
 Initialize I2C
*/
void I2C_Init(void);

/*
 Handles I2C interrupts
 */
void I2C_InterruptHandler(void);

/*
 Process I2C Events
 */
void I2C_Process(I2C_DRIVER_STATUS);

/*
 Data written to slave
*/
extern volatile uint8_t I2C_wData;

/*
 Returns MSB or LSB of 16 bit value
*/
uint8_t _get_significant(uint16_t, bool);

#ifdef __cplusplus
    }
#endif

#endif  // _I2C_H
