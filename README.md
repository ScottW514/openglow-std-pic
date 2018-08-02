## 08/01/2018 - This MCU has been removed from the OpenGlow system and is no longer used.

# Firmware for OpenGlow STD PIC16F1713 MCU.
I2C BUS0, Slave Address 0x08  

To test, use ```i2c-tools```.  
Example to read PIC's internal temp sensor:
```console
root@openglow_std:/# i2cget -y 0 0x08 0x1d w
0x0274
```
Example to set LID LED Duty Cycle:
```console
root@openglow_std:/# i2cset -y 0 0x08 0x30 0x01ff w
root@openglow_std:/# i2cget -y 0 0x08 0x30 w
0x01ff
```
## Firmware Version:  
```
READ:  
    VERSION #: 0xFE  
    VENDOR  #: 0xFF  
```

## LED Outputs:  
```
WRITE:  0x0000 - 0x03FF  
    LID    :    0x30  
    BTN_RED:    0x31
    BTN_GRN:    0x32  
    BTN_BLU:    0x33  
```

## Stepper IREF Outputs:  
```
WRITE:  
    X-AXIS: 0xE0    (0x0000 - 0x00FF)  
    Y-AXIS: 0xE1    (0x0000 - 0x001F)  
```  
## Analog to Digital Converters:  
```
READ: ADC_ID  
    HV_CURRENT: 0x12  
    HV_VOLTAGE: 0x13  
    LID_SENS1:  0x08  
    LID_SENS2:  0x09  
    LID_SENS3:  0x0B  
    LID_SENS4:  0x0D  
    PWR_SENS:   0x00  
    TEC_SENS:   0x04  
    WTR_SENS1:  0x02  
    WTR_SENS2:  0x03  

    DAC1_ADC:   0x1E  
    DAC2_ADC:   0x1C  
    FVR_ADC:    0x1F  
    TEMP_ADC:   0x1D  
```
