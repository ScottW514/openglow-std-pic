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
  File Name: leds.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/
#include "leds.h"

/*
 Global Variables
*/
volatile uint16_t LED_BTN_RED = BTN_R_INIT_VALUE;
volatile uint16_t LED_BTN_GRN = BTN_G_INIT_VALUE;
volatile uint16_t LED_BTN_BLU = BTN_B_INIT_VALUE;
volatile uint16_t LED_LID = LID_INIT_VALUE;

/*
    Initialize LEDs
*/
void LED_Init(void) {
    // Setup Timer2 - Our source for the PWMs 
    PR2 = 0xF9;
    TMR2 = 0x00;
    PIR1bits.TMR2IF = 0;
    T2CON = 0x07; // T2CKPS 1:64 / T2OUTPS 1:1 / TMR2ON on

    // Setup PWM for BTN RED LED
    PWM4CON = 0x80; // PWM4POL active_hi / PWM4OUT disabled / PWM4EN enabled
    PWM4DCH = 0;
    PWM4DCL = 0;   
    CCPTMRSbits.P4TSEL = 0x0; // Select TMR2

    // Setup PWM for BTN GRN LED
	CCP2CON = 0x3C; // CCP2M PWM / DC2B 3 
	CCPR2L = 0;    
	CCPR2H = 0;    
	CCPTMRSbits.C2TSEL = 0x0; // Select TMR2

    // Setup PWM for BTN BLU LED
	CCP1CON = 0x3C; // CCP1M PWM / DC1B 3
	CCPR1L = 0;
	CCPR1H = 0;
	CCPTMRSbits.C1TSEL = 0x0; // Select TMR2

    // Setup PWM for LID LEDs
    PWM3CON = 0x80; // PWM3POL active_hi / PWM3OUT disabled / PWM3EN enabled
    PWM3DCH = 0;
    PWM3DCL = 0;
    CCPTMRSbits.P3TSEL = 0x0; // Select TMR2
}

/*
 Process I2C Data
*/
void LED_ProcessWrite(uint8_t address, uint8_t value) {
    uint16_t value16 = value;
    if (address & 1) {
        // Processing the LSB - We load duty cycles when done
        switch (address) {
            case LED_BTN_RED_LSB:
                LED_BTN_RED = (LED_BTN_RED & 0xFF00) + value16;
                break;
            case LED_BTN_GRN_LSB:
                LED_BTN_GRN = (LED_BTN_GRN & 0xFF00) + value16;
                break;
            case LED_BTN_BLU_LSB:
                LED_BTN_BLU = (LED_BTN_BLU & 0xFF00) + value16;
                break;
            case LED_LID_LSB:
                LED_LID = (LED_LID & 0xFF00) + value16;
                break;
        }
        LED_LoadDutyCycles();
    } else {
        // Processing the MSB
        value16 = value16 << 8;
        switch (address) {
            case LED_BTN_RED_MSB:
                LED_BTN_RED = (LED_BTN_RED & 0x00FF) + value16;
                break;
            case LED_BTN_GRN_MSB:
                LED_BTN_GRN = (LED_BTN_GRN & 0x00FF) + value16;
                break;
            case LED_BTN_BLU_MSB:
                LED_BTN_BLU = (LED_BTN_BLU & 0x00FF) + value16;
                break;
            case LED_LID_MSB:
                LED_LID = (LED_LID & 0x00FF) + value16;
                break;
        }
    }
}

/*
 Load LED Duty Cycle Values
*/
void LED_LoadDutyCycles(void) {
    // BTN RED LED
    PWM4DCH = (LED_BTN_RED & 0x3FC)>>2; // 8 MSBs
    PWM4DCL = (LED_BTN_RED & 0x3)<<6; // 2 LSBs

    // BTN GRN LED
    CCPR2L = ((LED_BTN_GRN & 0x3FC)>>2); // 8 MSBs
    CCP2CON = ((uint8_t)(CCP2CON & 0xCF) | ((LED_BTN_GRN & 0x3)<<4)); // 2 LSBs

    // BTN BLU LED
    CCPR1L = ((LED_BTN_BLU & 0x3FC)>>2); // 8 MSBs
    CCP1CON = ((uint8_t)(CCP1CON & 0xCF) | ((LED_BTN_BLU & 0x3)<<4)); // 2 LSBs

    // LID LEDs
    PWM3DCH = (LED_LID & 0x03FC)>>2; // 8 MSBs
    PWM3DCL = (LED_LID & 0x0003)<<6; // 2 LSBs
}
