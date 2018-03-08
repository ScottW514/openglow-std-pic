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
  File Name: common.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _COMMON_H
#define _COMMON_H

#define _XTAL_FREQ  32000000

#define _VERSION_MAJOR 0x01
#define _VERSION_MINOR 0x02
#define _VERSION_PATCH 0x03

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
#include "adc.h"
#include "i2c.h"
#include "iref.h"
#include "leds.h"

#endif  // _COMMON_H
