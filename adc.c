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
    Initialize IREF
*/
void ADC_Init(void) {
    // Initialize ADC 
    ADCON0 = 0x01; // GO_nDONE stop / ADON enabled/CHS AN0
    ADCON1 = 0x50; // ADFM left / ADNREF VSS /ADPREF VDD / ADCS FOSC/16
    ADCON2 = 0x00; // TRIGSEL no_auto_trigger
    // Clear Address Select
    ADRESL = 0x00;
    ADRESH = 0x00;
}

/*
 Initiate ADC Capture Cycle
*/
void ADC_ProcessCapture(uint8_t address) {
    if (ADC_isADC(address)) {
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
        // Done with conversion - store it
        uint16_t temp = (uint16_t)((ADRESH << 8) + ADRESL);
        SENS_VAL[address] = temp;
        NOP();
    }
}

/*
 Return ADC readings
*/
uint8_t ADC_ProcessRead(uint8_t address) {
    if (address >= 0x40) {
        address = (uint8_t)(address - 0x40);
        if (ADC_isADC(address)) {
            // Read LSB
            return (uint8_t)(SENS_VAL[address] & 0x00FF);
        }
    } else {
        address = (uint8_t)(address - 0x20);
        if (ADC_isADC(address)) {
            // Read MSB
            return (uint8_t)((SENS_VAL[address] & 0xFF00) >> 8);
        }
    }
    return 0x00;
}

/*
 Is this an ADC
*/
bool ADC_isADC(uint8_t address) {
    switch (address) {
        case HV_SENS:
            break;
        case LID_SENS1:
            break;
        case LID_SENS2:
            break;
        case LID_SENS3:
            break;
        case LID_SENS4:
            break;
        case PWR_SENS:
            break;
        case TEC_SENS:
            break;
        case WTR_SENS1:
            break;
        case WTR_SENS2:
            break;
        case DAC1_ADC:
            break;
        case DAC2_ADC:
            break;
        case FVR_ADC:
            break;
        case TEMP_ADC:
            break;
        default:
            return false;
    }
    return true;
}
