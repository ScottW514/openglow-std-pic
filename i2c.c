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
  File Name: i2c.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45
*/

#include "i2c.h"

#define I2C_SLAVE_ADDRESS 0x08 

typedef enum {
    I2C_DATA,
    I2C_DATA_ADDRESS,
} I2C_DATA_TYPE;

/*
 Global Variables
*/
volatile uint8_t I2C_wData = 0x55;

/*
    Initialize I2C 
*/
void I2C_Init(void) {
    // initialize the hardware
    SSP1STAT = 0x00;
    SSP1CON1 = 0x26;
    SSP1CON2 = 0x01;
    SSP1CON3 = 0x00;
    SSP1ADD = I2C_SLAVE_ADDRESS << 1;
	
    // clear interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;

}

/*
   Handles I2C interrupts
 */
void I2C_InterruptHandler(void) {
    uint8_t I2C_buffer = 0x55;
    PIR1bits.SSP1IF = 0; // clear interrupt flag
    I2C_buffer = SSP1BUF;  // grab data from buffer
    if(SSP1STATbits.R_nW == 1) {
        if((SSP1STATbits.D_nA == 1) && (SSP1CON2bits.ACKSTAT == 1)) {
            // Read Complete
            I2C_Process(I2C_R_COMPLETED);
        } else {
            // Read Request
            I2C_Process(I2C_R_REQ);
        }
    } else if(SSP1STATbits.D_nA == 0) {
        // Write Request
        I2C_Process(I2C_W_REQ);
    } else {
        // Write completed
        I2C_wData = I2C_buffer;
        I2C_Process(I2C_W_COMPLETED);
    }
    SSP1CON1bits.CKP    = 1; // SCL release
} // end I2C_InterruptHandler()

/*
 Process Incoming I2C data
*/
void I2C_Process(I2C_DRIVER_STATUS i2c_bus_state) {
    static uint8_t address = 0;
    static uint8_t writeType = I2C_DATA;

    switch (i2c_bus_state)
    {
        case I2C_W_REQ:
            // Write request, wait for address
            writeType  = I2C_DATA_ADDRESS;
            break;
        case I2C_W_COMPLETED:
            switch(writeType)
            {
                case I2C_DATA_ADDRESS:
                    address = I2C_wData;
                    break;
                case I2C_DATA:
                    if ((address >= 0xF0) & (address <= 0xF7)) {
                        LED_ProcessWrite(address, I2C_wData);
                    } else if ((address >= 0xE0) & (address <= 0xE1)) {
                        IREF_ProcessWrite(address, I2C_wData);
                    } else if ((address >= 0x00) & (address <= 0x1F)) {
                        ADC_ProcessCapture(address);
                    }
                    break;
            }
            writeType = I2C_DATA;
            break;
        case I2C_R_REQ:
            if (address == 0xFD) {
                SSP1BUF = _VERSION_MAJOR;
            } else if (address == 0xFE) {
                SSP1BUF = _VERSION_MINOR;
            } else if (address == 0xFF) {
                SSP1BUF = _VERSION_PATCH;
            } else if ((address >= 0x20) & (address <= 0x5F)) {
                SSP1BUF = ADC_ProcessRead(address);
            } else {
                SSP1BUF = 0x00;
            }
            break;
        case I2C_R_COMPLETED:
        default:;
    }
}
