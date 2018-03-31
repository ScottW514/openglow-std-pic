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
