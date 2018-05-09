/*
  Copyright (C) 2018, Scott Wiederhold <s.e.wiederhold@gmail.com>

  SPDX-License-Identifier:	MIT

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
