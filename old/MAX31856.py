# -*- coding: utf-8 -*-
# import CRC calc function
from functions import crc_calc

# predefined messages to read registers
read_cr0 = [0x7E,0x05,0x00,0x00,0x00,0x00,0x00,0xFF]
read_cr1 = [0x7E,0x05,0x00,0x01,0x00,0x00,0x00,0xFE]
read_cjhigh = [0x7E,0x05,0x00,0x03,0x00,0x00,0x00,0xFC]
read_cjlow = [0x7E,0x05,0x00,0x04,0x00,0x00,0x00,0xFB]
read_lthigh = [0x7E,0x05,0x00,0x05,0x06,0x00,0x00,0xF4]
read_ltlow = [0x7E,0x05,0x00,0x07,0x08,0x00,0x00,0xF0]
read_CJtemp = [0x7E,0x05,0x00,0x0A,0x0B,0x00,0x00,0xEA]
read_TCtemp = [0x7E,0x05,0x00,0x0C,0x0D,0x00,0x00,0xE6] 
read_cjoffset = [0x7E,0x05,0x00,0x09,0x00,0x00,0x00,0xF6]

MAX31856_CONST_THERM_LSB = 2**-7
MAX31856_CONST_THERM_BITS = 19
MAX31856_CONST_CJ_LSB = 2**-6
MAX31856_CONST_CJ_BITS = 14

# CR0 Register Values   
CR0_STOP_AUTO = 0x3F 
CR0_OPEN_OFF = 0xCF
CR0_REG = 0x00
CR0_AUTOCONVERT = 0x80
CR0_1SHOT = 0x40
CR0_OCFAULT1 = 0x20
CR0_OCFAULT0 = 0x10
CR0_CJ = 0x08
CR0_FAULT = 0x04
CR0_FAULTCLR = 0x02
CR0_50HZ = 0x01 

### Register constants, see data sheet Table 6 (in Rev. 0) for info.
# Read Addresses
REG_READ_CR0 = 0x00
REG_READ_CR1 = 0x01
REG_READ_MASK = 0x02
REG_READ_CJHF = 0x03
REG_READ_CJLF = 0x04
REG_READ_LTHFTH = 0x05
REG_READ_LTHFTL = 0x06
REG_READ_LTLFTH = 0x07
REG_READ_LTLFTL = 0x08
REG_READ_CJTO = 0x09
REG_READ_CJTH = 0x0A  # Cold-Junction Temperature Register, MSB
REG_READ_CJTL = 0x0B  # Cold-Junction Temperature Register, LSB
REG_READ_LTCBH = 0x0C # Linearized TC Temperature, Byte 2
REG_READ_LTCBM = 0x0D # Linearized TC Temperature, Byte 1
REG_READ_LTCBL = 0x0E # Linearized TC Temperature, Byte 0
REG_READ_FAULT = 0x0F # Fault status register

# Write Addresses
REG_WRITE_CR0 = 0x80
REG_WRITE_CR1 = 0x81
REG_WRITE_MASK = 0x82
REG_WRITE_CJHF = 0x83
REG_WRITE_CJLF = 0x84
REG_WRITE_LTHFTH = 0x85
REG_WRITE_LTHFTL = 0x86
REG_WRITE_LTLFTH = 0x87
REG_WRITE_LTLFTL = 0x88
REG_WRITE_CJTO = 0x89
REG_WRITE_CJTH = 0x8A  # Cold-Junction Temperature Register, MSB
REG_WRITE_CJTL = 0x8B  # Cold-Junction Temperature Register, LSB

# FAULT Reg. Values
FAULT_CJRANGE = 0x80
FAULT_TCRANGE = 0x40
FAULT_CJHIGH = 0x20
FAULT_CJLOW = 0x10
FAULT_TCHIGH = 0x08
FAULT_TCLOW = 0x04
FAULT_OVUV = 0x02
FAULT_OPEN = 0x01

# string for fault register 
STR_FAULT_CJRANGE = 'La juntura fría esta fuera del rango de operación'
STR_FAULT_TCRANGE = 'La termocupla esta fuera del rango de operación'
STR_FAULT_CJHIGH = 'La juntura fría excedió el limite superior de temperatura'
STR_FAULT_CJLOW = 'La juntura fría excedió el limite inferior de temperatura'
STR_FAULT_TCHIGH = 'La termocupla excedió el limite superior de temperatura'
STR_FAULT_TCLOW = 'La termocupla excedió el limite inferior de temperatura'
STR_FAULT_OVUV = 'Hay una sobre/baja tensión en el modulo MAX31856'
STR_FAULT_OPEN = 'Termocupla Abierta'

# Pre-config Register Options
CR0_READ_ONE = 0x40 # One shot reading, delay approx. 200ms then read temp registers
CR0_READ_CONT = 0x80 # Continuous reading, delay approx. 100ms between readings

# Thermocouple Types
B_TYPE = 0x00 # Read B Type Thermocouple
E_TYPE = 0x01 # Read E Type Thermocouple
J_TYPE = 0x02 # Read J Type Thermocouple
K_TYPE = 0x03 # Read K Type Thermocouple
N_TYPE = 0x04 # Read N Type Thermocouple
R_TYPE = 0x05 # Read R Type Thermocouple
S_TYPE = 0x06 # Read S Type Thermocouple
T_TYPE = 0x07 # Read T Type Thermocouple
GAIN8 = 0x08 
GAIN8_CONST = 1677721.6
GAIN32 = 0x0C
GAIN32_CONST = 6710886.4
PROM1 = 0x00  
PROM2 = 0x10
PROM4 = 0x20
PROM8 = 0x30
PROM16 = 0x40

# Reg Default Values
REG_DEF_CR0 = 0x00
REG_DEF_CR1 = 0x03
REG_DEF_MASK = 0xFF
REG_DEF_CJHF = 0x7F
REG_DEF_CJLF = 0xC0
REG_DEF_LTHFTH = 0x7F
REG_DEF_LTHFTL = 0xFF
REG_DEF_LTLFTH = 0x80
REG_DEF_LTLFTL = 0x00
REG_DEF_CJTO = 0x00
REG_DEF_CJTH = 0x00  # Cold-Junction Temperature Register, MSB
REG_DEF_CJTL = 0x00  # Cold-Junction Temperature Register, LSB
REG_DEF_LTCBH = 0x00 # Linearized TC Temperature, Byte 2
REG_DEF_LTCBM = 0x00 # Linearized TC Temperature, Byte 1
REG_DEF_LTCBL = 0x00 # Linearized TC Temperature, Byte 0
REG_DEF_FAULT = 0x00 # Fault status register

# Mask for registers, used by gui 
REG_CR0_VALUE = 0x85
REG_CR0_MASK_CONV_MODE = 0x80
REG_CR0_MASK_AUTOCONVERTION = 0x7F
REG_CR0_MASK_OCFAULT = 0x30
REG_CR0_MASK_CJSENSOR = 0x08
REG_CR0_MASK_FILTER = 0x01
REG_CR1_MASK_AVGMODE = 0x70
REG_CR1_MASK_TERMTYPE = 0x0F

SING_MASK = 0x08
SING_ONE_MASK = 0x80
SING_TWO_MASK = 0x800
ODD_MASK = 0x01

CONVERSION_AUTO = 0
NORMALLY_OFF = 1

HABILITADO = 0
DESHABILITADO = 1

FILTRO_60 = 0
FILTRO_50 = 1

PROM_16 = 0
PROM_8 = 1
PROM_4 = 2
PROM_2 = 3
PROM_1 = 4

TERM_B = 0
TERM_E = 1
TERM_J = 2
TERM_K = 3
TERM_N = 4
TERM_R = 5
TERM_S = 6
TERM_T = 7
GAIN_8 = 8
GAIN_32 = 9

# def cj_read(self):    
    # if self & SING_ONE_MASK:
        # if not (self & ODD_MASK): parity = True
        # else: parity = False
        # self &= 0xFE
        # self ^= 0xFF
        # self *= -1                    
        # if parity: self -=1                                           
    # else:
        # self &= 0x7F         
    # return self
    
# def lt_read(self):
    # self >>= 4
    # if self & SING_TWO_MASK:
        # if not (self & ODD_MASK): parity = True
        # else: parity = False   
        # self &= 0xFFE
        # self ^= 0xFFF
        # self *= -1
        # if parity: self -=1        
    # else:
        # self &= 0x7FF
    # return self
    
def cj_offset_read(self):
    self >>= 4
    if self & SING_MASK:
        if not (self & ODD_MASK): parity = True
        else: parity = False
        self &= 0x0E
        self ^= 0x0F
        self *= -1
        if parity: self -=1        
    else:
        self &= 0x07
    return self
    
def cj_write(self):
    if self < 0:
        self *= -1        
        if not (self % 2): parity = True
        else: parity = False           
        self &= 0x7E
        self ^= 0xFF             
        if parity: self += 1
    else:
        self &= 0x7F
    return self
    
def lt_write(self):    
    if self < 0:        
        self *= -1                
        if not (self % 2): parity = True
        else: parity = False
        self &= 0x7FE
        self ^= 0xFFF             
        if parity: self += 1
    else:
        self &= 0x7FF
    self <<=4    
    return ((self & 0xFF00) >> 8), (self & 0xFF)

def cj_offset_write(self):
    if self < 0:
        self *= -1        
        if not (self % 2): parity = True
        else: parity = False           
        self &= 0x06
        self ^= 0x0F             
        if parity: self += 1
    else:
        self &= 0x07
    return (self << 4)
    
def lt_read(byte2, byte1, byte0):
    """Converts the thermocouple byte values to a decimal value.
    This function was removed from readInternalTempC() and moved to its own method to allow for
        easier testing with standard values.
    Args:
        byte2 (hex): Most significant byte of thermocouple temperature
        byte1 (hex): Middle byte of thermocouple temperature
        byte0 (hex): Least significant byte of a thermocouple temperature
    Returns:
        temp_c (float): Temperature in degrees celsius
    """
    #            (((val_high_byte w/o +/-) shifted by 2 bytes above LSB)
    #                 + (val_mid_byte shifted by number 1 byte above LSB)
    #                                             + val_low_byte )
    #                              >> back shift by number of dead bits
    temp_bytes = (((byte2 & 0x7F) << 16) + (byte1 << 8) + byte0)
    temp_bytes = temp_bytes >> 5
    
    if byte2 & 0x80:
        temp_bytes -= 2**(MAX31856_CONST_THERM_BITS - 1)
    #        temp_bytes*value of LSB
    temp_c = temp_bytes*MAX31856_CONST_THERM_LSB
    
    return temp_c
    
def adc_read(byte2, byte1, byte0):    
    temp_bytes = (((byte2 & 0x7F) << 16) + (byte1 << 8) + byte0)
    temp_bytes = temp_bytes >> 5

    if byte2 & 0x80:
        temp_bytes -= 2**(MAX31856_CONST_THERM_BITS -1)
    
    return temp_bytes
    
def cj_read(msb, lsb):
    """Takes in the msb and lsb from a Cold Junction (CJ) temperature reading and converts it
    into a decimal value.
    This function was removed from readInternalTempC() and moved to its own method to allow for
        easier testing with standard values.
    Args:
        msb (hex): Most significant byte of CJ temperature
        lsb (hex): Least significant byte of a CJ temperature
    """
    #            (((msb w/o +/-) shifted by number of 1 byte above lsb)
    #                                  + val_low_byte)
    #                                          >> shifted back by # of dead bits
    temp_bytes = (((msb & 0x7F) << 8) + lsb) >> 2

    if msb & 0x80:
        # Negative Value.  Scale back by number of bits
        temp_bytes -= 2**(MAX31856_CONST_CJ_BITS -1)

    #        temp_bytes*value of lsb
    temp_c = temp_bytes*MAX31856_CONST_CJ_LSB

    return temp_c
