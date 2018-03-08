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
    I2C_W_COMPLETED,
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

#ifdef __cplusplus
    }
#endif

#endif  // _I2C_H
