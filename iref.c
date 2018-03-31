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
  File Name: iref.c

  Summary: Firmware package for OpenGlow Standard

  Target Device   :  PIC16F1713
  Development IDE :  MPLAB X v4.15
  Compiler        :  XC8 1.45

*/
#include "iref.h"

/*
    Initialize IREF
*/
void IREF_Init(void) {
    // Fixed Voltage Reference
    FVRCON = 0xAA; // CDAFVR 2x / FVREN enabled / TSRNG Lo_range / ADFVR 2x / TSEN enabled

    // X-IREF DAC1 / OPA1
    DAC1CON0 = 0x88; // DAC1EN enabled / DAC1NSS VSS / DAC1PSS FVR / DAC1OE1 disabled / DAC1OE2 disabled
    DAC1CON1 = 0x00; // Set initial value to 0
    OPA1CON = 0xD2; // OPA1SP High_GBWP_mode / OPA1EN enabled / OPA1PCH DAC1_Output / OPA1UG OPA_Output

    // Y-IREF DAC2 / OPA2
    // DAC2EN enabled; DAC2NSS VSS; DAC2PSS FVR_buf2; DAC2OE1 disabled; DACOE2 disabled; 
    DAC2CON0 = 0x88; // DAC2EN enabled / DAC2NSS VSS / DAC2PSS FVR_buf2 / DAC2OE1 disabled / DACOE2 disabled
    DAC2CON1 = 0x00; // Set initial value to 0
    OPA2CON = 0xD1; // OPA2SP High_GBWP_mode / OPA2EN enabled / OPA2PCH DAC2_Output / OPA2UG OPA_Output 
}

/*
 Process I2C Data
*/
void IREF_SetOutput(uint8_t dac_unit, uint16_t value) {
    if (dac_unit == X_IREF) {
        if (value > 0x00FF) {
            value = 0x00FF;
        }
        DAC1CON1 = (uint8_t)value;
    } else if (dac_unit == Y_IREF) {
        if (value > 0x001F) {
            value = 0x001F;
        }
        DAC2CON1 = (uint8_t)value;
    }
}
