/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: adc.h

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45


 PIC Temperature Indicator Module:
  F = ((9/5)*((.659-((3.3/2)*(1-(TEMP_ADC/1023))))/.00132)) + 32
  C = (.659-((3.3/2)*(1-(TEMP_ADC/1023))))/.00132

 PIC ADC Result to Voltage:
  Vin = (3.3/1023) * ADC_RESULT
*/

#ifndef _ADC_H
#define _ADC_H

#include "common.h"

#define HV_SENS1    0x12
#define HV_SENS2    0x13
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
