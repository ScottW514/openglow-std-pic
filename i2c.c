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
volatile uint8_t I2C_wData = 0x00;

/*
    Initialize I2C 
*/
void I2C_Init(void) {
    // Initialize the hardware
    SSP1STAT = 0x00; // Clear SSP STATUS Register
    SSP1CON1 = 0x26; // SSPEN enabled, SSPM I2C Slave-7bit
    SSP1CON2 = 0x01; // SEN clock stretch enabled for send and receive
    SSP1CON3 = 0x00; // Default
    SSP1ADD = I2C_SLAVE_ADDRESS << 1;
	
    // Clear interrupt flag
    PIR1bits.SSP1IF = 0;
    // Enable the master interrupt
    PIE1bits.SSP1IE = 1;

}

/*
   Handles I2C interrupts
 */
void I2C_InterruptHandler(void) {
    uint8_t I2C_buffer = 0x00;
    PIR1bits.SSP1IF = 0; // clear interrupt flag
    I2C_buffer = SSP1BUF;  // grab data from buffer, resetting BF bit
    if(SSP1STATbits.R_nW == 1) {
    // READ Transaction
        if((SSP1STATbits.D_nA == 1) && (SSP1CON2bits.ACKSTAT == 1)) {
            // READ is Complete
            I2C_Process(I2C_R_COMPLETED);
        } else {
            // Read Request
            I2C_Process(I2C_R_REQ);
        }
    // WRITE TRANSACTIONS
    } else if (SSP1STATbits.D_nA == 0) {
        // I2C_buffer is an address
        I2C_Process(I2C_W_REQ);
    } else {
        // I2C_buffer is data
        I2C_wData = I2C_buffer;
        I2C_Process(I2C_W_DATA);
    }
    SSP1CON1bits.CKP    = 1; // SCL release
} // end I2C_InterruptHandler()

/*
 Process Incoming I2C data
*/
void I2C_Process(I2C_DRIVER_STATUS i2c_bus_state) {
    static uint8_t address = 0; // Address last received
    static uint8_t writeType = I2C_DATA;  // The data byte last received
    static bool LSB_nMSB = false; // Byte to send
    static uint16_t data = 0; // Holds gathered data

    switch (i2c_bus_state)
    {
        case I2C_W_REQ:
            // Request inbound, wait for Address
            writeType  = I2C_DATA_ADDRESS;
            break;
        case I2C_W_DATA:
            // Master sent us some data, see what kind it is
            switch(writeType)
            {
                case I2C_DATA_ADDRESS:
                    // It's an address for READ/WRITE
                    address = I2C_wData;
                    LSB_nMSB = true;
                    break;
                case I2C_DATA:
                    // It's data
                    if (LSB_nMSB) {
                        // It's the LSB of the 16 bit word we're expecting
                        data = I2C_wData;
                    } else {
                        // It's the MSB of the 16 bit word
                        data = data + ((uint16_t)I2C_wData << 8);
                        // We got our word, time to do something with it
                        if (address == 0x21) {
                            // Setting X_IREF output
                            IREF_SetOutput(X_IREF, data);
                        } else if (address == 0x22) {
                            // Setting Y_IREF output
                            IREF_SetOutput(Y_IREF, data);
                        } else if ((address >= 0x30) && (address <= 0x33)) {
                            // Setting LED output
                            LED_Set_DutyCycle(address - 0x30, data);
                        }
                    }
                    LSB_nMSB = LSB_nMSB ? false : true;
                    break;
            }
            writeType = I2C_DATA;
            break;
        case I2C_R_REQ:
            if (address == 0xFF) {
                // Return Vendor ID
                SSP1BUF = _get_significant(_VENDOR, LSB_nMSB);
            } else if (address == 0xFE) {
                // Return Firmware Version
                SSP1BUF = _get_significant(_VERSION, LSB_nMSB);
            } else if ((address >= 0x00) && (address <= 0x1F)) {
                // Return ADC Channel Reading
                if (LSB_nMSB) {
                    data = ADC_ProcessCapture(address);
                }
                SSP1BUF = _get_significant(data, LSB_nMSB);
            } else if (address == 0x21) {
                // Return DAC1 Setting
                SSP1BUF = _get_significant(DAC1CON1, LSB_nMSB);
            } else if (address == 0x22) {
                // Return DAC2 Setting
                SSP1BUF = _get_significant(DAC2CON1, LSB_nMSB);
            } else if ((address >= 0x30) && (address <= 0x33)) {
                // Return LED DutyCycle
                SSP1BUF = _get_significant(LED_Get_DutyCycle(address - 0x30), LSB_nMSB);
            } else {
                // Invalid address - return DEAD
                SSP1BUF = _get_significant(0xDEAD, LSB_nMSB);
            }
            LSB_nMSB = LSB_nMSB ? false : true;
            break;
        case I2C_R_COMPLETED:
        default:;
    }
} // end I2C_Process()


/*
 Returns MSB or LSB of 16 bit value 
*/
uint8_t _get_significant(uint16_t value, bool LSB_nMSB) {
    if (LSB_nMSB) {
        // LSB
        return (uint8_t)(value & 0x00FF);
    } else {
        // MSB
        return (uint8_t)((value & 0xFF00) >> 8);
    }
}