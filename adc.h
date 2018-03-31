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
  File Name: adc.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#ifndef _ADC_H
#define _ADC_H

#include "common.h"

#define HV_SENS     0x12
#define LID_SENS1   0x08
#define LID_SENS2   0x09
#define LID_SENS3   0x0B
#define LID_SENS4   0x0D
#define PWR_SENS    0x00
#define TEC_SENS    0x04
#define WTR_SENS1   0x02
#define WTR_SENS2   0x03

#define DAC1_ADC    0x1E
#define DAC2_ADC    0x1C
#define FVR_ADC     0x1F
#define TEMP_ADC    0x1D

#ifdef __cplusplus
    extern "C" {
#endif

/*
 Initialize ADCs 
*/
void ADC_Init(void);

/*
 Initiate ADC Capture Cycle
*/
uint16_t ADC_ProcessCapture(uint8_t);

#ifdef __cplusplus
    }
#endif

#endif  // _ADC_H
