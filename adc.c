/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT


  File Name: adc.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45

*/
#include "adc.h"

#define ADC_DELAY 200

/*
 Global Variables
*/
volatile uint16_t SENS_VAL[0x20];

/*
    Initialize ADC
*/
void ADC_Init(void) {
    // Initialize ADC
    ADCON0 = 0x01; // GO_nDONE stop / ADON enabled/CHS AN0
    ADCON1 = 0xD0; // ADFM right / ADNREF VSS /ADPREF VDD / ADCS FOSC/16
    ADCON2 = 0x00; // TRIGSEL no_auto_trigger
    ADRESL = 0x00;
    ADRESH = 0x00;
}

/*
 Run ADC Capture Cycle
*/
uint16_t ADC_ProcessCapture(uint8_t address) {
    // Set ADC Channel and fire up module
    ADCON0bits.CHS = (uint8_t)(address & 0x1F);
    // Fire up module
    ADCON0bits.ADON = 1;
    // Pause
    __delay_us(ADC_DELAY);
    // Kick off the conversion cycle
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE){
        // We wait. Patiently.
    }
    // Done with conversion - return it
    return (uint16_t)((ADRESH << 8) + ADRESL);
}
