/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: leds.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/
#include "leds.h"

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
    PWM4DCH = (uint8_t)((BTN_R_INIT_VALUE & 0x3FC) >> 2);
    PWM4DCL = (uint8_t)((BTN_R_INIT_VALUE & 0x003) << 6);
    CCPTMRSbits.P4TSEL = 0x0; // Select TMR2

    // Setup PWM for BTN GRN LED
	CCP2CON = 0x0C; // CCP2M PWM / DC2B 3
    CCP2CON = (uint8_t)((CCP2CON & 0xCF) | (uint8_t)((BTN_G_INIT_VALUE & 0x003) << 4));
	CCPR2L =  (uint8_t)((BTN_G_INIT_VALUE & 0x3FC) >> 2);
	CCPR2H =  0x00;
	CCPTMRSbits.C2TSEL = 0x0; // Select TMR2

    // Setup PWM for BTN BLU LED
	CCP1CON = 0x0C; // CCP1M PWM / DC1B 3
    CCP1CON = (uint8_t)((CCP1CON & 0xCF) | (uint8_t)((BTN_B_INIT_VALUE & 0x003) << 4));
	CCPR1L =  (uint8_t)((BTN_B_INIT_VALUE & 0x3FC) >> 2);
	CCPTMRSbits.C1TSEL = 0x0; // Select TMR2

    // Setup PWM for LID LEDs
    PWM3CON = 0x80; // PWM3POL active_hi / PWM3OUT disabled / PWM3EN enabled
    PWM3DCH = (uint8_t)((LID_INIT_VALUE & 0x3FC) >> 2);
    PWM3DCL = (uint8_t)((LID_INIT_VALUE & 0x003) << 6);
    CCPTMRSbits.P3TSEL = 0x0; // Select TMR2
}

/*
 SET LED Duty Cycle
*/
void LED_Set_DutyCycle(uint8_t led, uint16_t dutycycle) {
    if (dutycycle > 0x3FF) {
        dutycycle = 0x3FF;
    }
    switch (led)
    {
        case LED_LID:
            PWM3DCH = (uint8_t)((dutycycle & 0x3FC) >> 2); // 8 High Bits
            PWM3DCL = (uint8_t)((dutycycle & 0x003) << 6); // 2 Low Bits
            break;
        case LED_BTN_R:
            PWM4DCH = (uint8_t)((dutycycle & 0x3FC) >> 2); // 8 High Bits
            PWM4DCL = (uint8_t)((dutycycle & 0x003) << 6); // 2 Low Bits
            break;
        case LED_BTN_G:
            CCPR2L =  (uint8_t)((dutycycle & 0x3FC) >> 2);                               // 8 High Bits
            CCP2CON = (uint8_t)((CCP2CON & 0xCF) | (uint8_t)((dutycycle & 0x003) << 4)); // 2 LSBs
            break;
        case LED_BTN_B:
            CCPR1L =  (uint8_t)((dutycycle & 0x3FC) >> 2);                               // 8 High Bits
            CCP1CON = (uint8_t)((CCP1CON & 0xCF) | (uint8_t)((dutycycle & 0x003) << 4)); // 2 LSBs
            break;
        default:;
    }
}

/*
 GET LED Duty Cycle
*/
uint16_t LED_Get_DutyCycle(uint8_t led) {
    static uint16_t value = 0;
    switch (led)
    {
        case LED_LID:
            value = (((uint16_t)PWM3DCH) << 2) + (uint16_t)(PWM3DCL >> 6);
            break;
        case LED_BTN_R:
            value = (((uint16_t)PWM4DCH) << 2) + (uint16_t)(PWM4DCL >> 6);
            break;
        case LED_BTN_G:
            value = (((uint16_t)CCPR2L) << 2) + (uint16_t)((CCP2CON & 0x30) >> 4);
            break;
        case LED_BTN_B:
            value = (((uint16_t)CCPR1L) << 2) + (uint16_t)((CCP1CON & 0x30) >> 4);
            break;
        default:
            value = 0xDEAD;
            break;
    }
    return value;
}
