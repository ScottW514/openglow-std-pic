/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

  File Name: main.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#include "common.h"

/*
 Device Configuration
*/
// CONFIG1
#pragma config FOSC = INTOSC  // Inernal Oscillator
#pragma config WDTE = OFF     // WDT disabled
#pragma config PWRTE = OFF    // PWRT disabled
#pragma config MCLRE = ON     // MCLR/VPP pin function is MCLR
#pragma config CP = OFF       // Code protection is disabled
#pragma config BOREN = ON     // Brown-out Reset enabled
#pragma config CLKOUTEN = OFF // CLKOUT disabled
#pragma config IESO = ON      // Int/Ext Switchover Mode is enabled
#pragma config FCMEN = ON     // Fail-Safe Clock Monitor is enabled

// CONFIG2
#pragma config WRT = OFF      // Write protection off
#pragma config PPS1WAY = ON   // PPSLOCK bit cannot be cleared once it is set
#pragma config ZCDDIS = ON    // Zero-cross detect circuit disabled
#pragma config PLLEN = ON     // 4x PLL is always enabled
#pragma config STVREN = ON    // Stack Overflow or Underflow will cause a Reset
#pragma config BORV = LO      // Brown-out Reset Voltage, low trip point
#pragma config LPBOR = OFF    // Low-Power BOR is disabled
#pragma config LVP = ON       // Low-voltage programming enabled

/*
 Local Functions
*/
void interrupt InterruptHandler(void);

/*
 Main Program
*/
void main(void) {

    // Initialize Registers
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    TRISA = 0xFD;
    TRISB = 0xFC;
    TRISC = 0xF8;
    TRISE = 0x08;
    ANSELA = 0x3F;
    ANSELB = 0x3F;
    ANSELC = 0xE4;
    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x00;
    OPTION_REGbits.nWPUEN = 1;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    // Pin Init
    RC2PPSbits.RC2PPS = 0x0C;       //RC2->CCP1
    RC1PPSbits.RC1PPS = 0x0D;       //RC1->CCP2
    RC4PPSbits.RC4PPS = 0x11;       //RC4->MSSP-SDA
    SSPDATPPSbits.SSPDATPPS = 0x14; //RC4->MSSP-SDA
    RC3PPSbits.RC3PPS = 0x10;       //RC3->MSSP-SCL
    SSPCLKPPSbits.SSPCLKPPS = 0x13; //RC3->MSSP-SCL
    RB0PPSbits.RB0PPS = 0x0E;       //RB0->PWM3
    RC0PPSbits.RC0PPS = 0x0F;       //RC0->PWM4

    // Osc Init
    OSCCON = 0x70;    // SCS FOSC / SPLLEN disabled / IRCF 8MHz_HF
    OSCTUNE = 0x00;
    BORCON = 0x00;
    // Stabilize PLL
    while(PLLR == 0) {
        // Twiddle our thumbs
    }

    // Watchdog Timer
    WDTCON = 0x16; // WDTPS 1:65536 / SWDTEN OFF

    // Init Peripherals
    I2C_Init();
    LED_Init();
    IREF_Init();
    ADC_Init();

    // Enable Interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    // Main Loop
    while (1) {
        // Twiddle our thumbs and wait for interrupts
    }
}

/*
 Interrupt Handler
*/
void interrupt InterruptHandler(void) {
    if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
        {
            I2C_InterruptHandler();
        }
    }
}
