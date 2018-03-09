# Firmware for OpenGlow STD PIC16F1713 MCU.
I2C BUS0, Slave Address 0x08  
  
To test, use ```i2c-tools```.  
Example to read PIC's internal temp sensor:
```console
root@openglow_std:/# i2cset -y 0 0x08 0x1d 0x01
root@openglow_std:/# i2cget -y 0 0x08 0x3d
0xa1  <-- MSB
root@openglow_std:/# i2cget -y 0 0x08 0x5d
0x40  <-- LSB
```
## Firmware Version:  
```
READ:  
    MAJOR #:    0xFD  
    MINOR #:    0xFE  
    PATCH #:    0xFF  
```
   
## LED Outputs:  
Write MSB first, then LSB.  
Device updates brightness level after LSB write.
```
WRITE:  0x0000 - 0x03FF  
            MSB     LSB  
    RED:    0xF0    0xF1  
    GRN:    0xF2    0xF3  
    BLU:    0xF4    0xF5  
    LID:    0xF6    0xF7  
```

## Stepper IREF Outputs:  
```
WRITE:  
    X-AXIS: 0xE0    (0x00 - 0xFF)  
    Y-AXIS: 0xE1    (0x00 - 0x1F)  
```  
## Analog to Digital Converters:  
```
WRITE:  Any value to trigger reading.  Wait > 250uS.  
READ:   ADC_ID + 0x20 for MSB, ADC_ID + 0x40 for LSB  
    HV_SENS:    0x12  
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
