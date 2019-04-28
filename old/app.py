# -*- coding: utf-8 -*-
#importing wx files
import wx
#import the newly created GUI file
import gui
#import handle for functions
import functions
#import serial comm
import serial
#import serial tools
import serial.tools.list_ports as port_list
#import binascii
import binascii
#import MAX31856 constants 
import MAX31856 
#import function for time handle 
from time import localtime, strftime, sleep, time 
#import logging
import logging
#import matplotlib  
import matplotlib.pyplot as plt
import matplotlib.animation as anim
#import numpy for math handle
import numpy as np

#Global variables#
##################

# Constant
MAXIMUM_TAP = 127 # taps limit
TIME_TO_RUN_AUTOCONVERT = 1500 # miliseconds
TIME_TO_RUN_CLEAR_FLT = 2000 # miliseconds
PERIOD_TO_READ_USB_CHAR = 100 # miliseconds
PERIOD_TO_PROCESS_USB_CHAR = 100 # miliseconds
PERIOD_TO_CLEAR_FAULT = 500 # miliseconds
PERIOD_TO_CLEAR_LIST_FLT = 750 # miliseconds
FLT_DIFFERENCE_TIME = 1 # seconds
DELAY_TO_SEND_DEFAULT_CONFIG = 500 # miliseconds
POWER_STAND_BY = 10 # perc. Minimum power 
MIN_POWER = 114 # taps (10%)
MAX_POWER = 0 # taps (100%)
MIN_POWER_PER = 10 # 10% 
USB_SERIAL_NUMBER = '12345678'
BIT_START = 0x7E # start byte of protocol message 
LENGTH_OF_MSG = 0x05 # length of protocol message
MSG_TYPE_THERMOCUPLE = '00' # id thermocouple message
MSG_TYPE_POTENCIOMETER = '01' # id potenciometer message
MSG_TYPE_COMMAND_POWER = '02' # id command power message
MSG_TYPE_TICK = '03' # id tick from uC message
MSG_TYPE_THERMOCUPLE_INT = 0x00 # id thermocouple message 
MSG_TYPE_POTENCIOMETER_INT = 0x01 # id potenciometer message
MSG_TYPE_COMMAND_POWER_INT = 0x02 # id command power message
MSG_TYPE_TICK_INT = 0x03 # id tick from uC message
MSG_TYPE_SYSTEM_RESET_INT = 0x04 # id Reset the entire device
COMMAND_POWER_ON = 0x01 # id to turn software control 
COMMAND_POWER_OFF = 0x00 # id to turn manual control 
AUTO_TUNNING = 0 # auto-tunning calibration option
SLOW_APPROACH = 1 # slow approach calibration option
PID_AUTO = 0 # pid auto control option
PID_MANUAL = 1 # pid manual control option
DIFF_MEAN_SEC = 6 # samples, mean of the derivate
DIFF_MEAN = 3 # samples, mean of the derivate
DIFF_EQU_TO_ZERO = 1 # C/seg, Null derivative limit
DELTA_U = 25 # perc, step to auto-tunning calibration
DELTA_U_TAPS = 32 # taps, step to auto-tunning calibration in taps
TIME_TO_REACH_MAXIMUM_DERIVATE = int((DIFF_MEAN_SEC/DIFF_MEAN)*15) # 15 seconds, time to detect slow approach 
TIME_TO_FINISH_TUNNING = int((DIFF_MEAN_SEC/DIFF_MEAN)*7) # 7 seconds, delay to finish  
TIME_TO_SAVE_CSV = 10 # seconds to save csv 
DECREASE_PWR_SLOW_APPROACH = 10 # perc, power to decrease in slow approach
PID_TOLERANCE = 2 # ºC, dead-band pid
UP = 1
EQUAL = 0
DOWN = -1
SLOW_HEATING = 0x80
FAST_HEATING = 0x08
TEMP_TO_COOLING = 200 # ºC less for cooling
#validation constants 
ERROR_VALUE = '####' 
TEMP_VALID_MAX = 1500 # °C
TEMP_VALID_MIN = 0    # °C 
PERC_VALID_MAX = 100  # perc
PERC_VALID_MIN = 10   # perc

#variables for data logger
g_pwr_horno = ''
g_sampling_period = 160 
g_logger = None
g_handler = None 
g_data_per_second = 0 
g_csv_name = ''
g_csv_data_temp = []
g_csv_file = None 
g_csv_data_pwr = []
g_csv_time_to_save = 0
g_csv_time = 0

#variables for control
g_temp_obj = 0 # objective temp.
g_temp_cutoff_step_1 = 0 # cutting temperature at the step 1 
g_step_1 = 0 # power step 1
g_step_2 = 0 # power step 2
g_procedure_str = '' # show steps for all the process 

#variables for pid method
g_pid_file_name = 'pid_auto' # data file for pid constants 
g_Kp = 0 # Kp (porportional gain)
g_Ki = 0 # Ki (integral gain)
g_Ti = 0 # Ti (integration period)
g_integral = 0 # integral error
g_pid = 0 # pid control variable 
g_dynamic = False # change set point dynamic

#variables for auto-tunning
g_time_to_detect_stationary = 10 # consideration of null derivate

#variables for slow approach
g_slow_approach_filename = 'slow_approach' # data file for s.a. constants 
g_maximum_derivate = 0.5 # 3ºC/seg limit of maximum derivate 
g_temp_cooling = 0 # slow approach test restart temp.
g_tries = 0 # attemps to detect derivate limit

#variables for all method
g_ControlOn = False # activate control 
g_CalibrationOn = False # activate calibration
g_method = False # specific method for both cal./control
g_first_step = False # first step in routine
g_second_step = False # second step in routine
g_third_step = False # third step in routine
g_finish = False # wait for delay when it finished 
g_data_for_estimate = [] # save the mean of x samples 
g_diff_data = [] # save the mean of derivate x samples
g_fault_status = False

#variables for plot
g_temp_data = [] # list of temp. data
g_power_data = [] # list of power data
g_animation = None # animation object
g_stop_animation = True # activate animation 
g_fig = None # figure object
g_ax = None # subplot 1
g_ax2 = None # subplot 2
g_logger_status = False # activate logger when plot is on 

#variables for USB
g_usb_serial = serial.Serial() # serial object
g_usb_serial_status = True # serial status flag
g_usb_serial_buffer = b'' # serial buffer handle  
g_buffer_busy = False # flag to process data 

#variables for protocol
g_bit_start = False # bit start flag
g_length_found = False # length found flag
g_new_msg = False # new msg flag
g_last_alarm_time = 0 # counter for time alarm elapsed  
g_msg_length = 0 # length of msg 
g_counter = 0 # handle for protocol msg 
g_msg_recieve = '' # new msg recieve handle 
g_reg_values = [0x00, 0x03, 0xFF, 0x7F, 0xC0, 0x7F, 0xFF, 0x80, 0x00, 0x00] # reg MAX31856 default 

# cold-junction compensation
g_cold_junction = ''

#thermocouple test set initial params for MAX31856
g_thermocouple_test = [0x7E,0x05,0x00,0x00,0x00,0x00,0x00,0xFF,
                    0x7E,0x05,0x00,0x01,0x00,0x00,0x00,0xFE,#thermocouple check                                                                                                                                           
                    0x7E,0x05,0x00,0x82,0x00,0x00,0x00,0x7D,#clear MASK 
                    0x7E,0x05,0x00,0x83,0x7D,0x00,0x00,0xFF,#CJH 125ºC
                    0x7E,0x05,0x00,0x84,0xE7,0x00,0x00,0x94,#CJL -25ºC
                    0x7E,0x05,0x00,0x85,0x4B,0x86,0x00,0xA9,#LTH 1200ºC
                    0x7E,0x05,0x00,0x87,0xF6,0x88,0xA0,0x5A,#LTL -150ºC
                    0x7E,0x05,0x00,0x89,0x00,0x00,0x00,0x76,#CJOFF 0ºC                      
                    0x7E,0x05,0x01,0x72,0x00,0x00,0x00,0x8C]#Pot = 10% (POWER_STAND_BY)                    
                    
#activate auto-convertion
g_thermocouple_auto_on = [0x7E,0x05,0x00,0x80,0x80,0x00,0x00,0x00]                                                                      

#activate 4 sample average 
g_thermocouple_avg_4 = [0x7E,0x05,0x00,0x81,0x00,0x00,0x00,0x00]

#clear fault bit interrupt 
g_thermocouple_FLT_Clear = [0x7E,0x05,0x00,0x80,0x02,0x00,0x00,0x00]

#50Hz, Interrupt mode
g_thermocouple_reg0 = [0x7E,0x05,0x00,0x80,0x05,0x00,0x00,0x00]

def SystemReset():
    if not g_usb_serial_status:
        write_register(MSG_TYPE_THERMOCUPLE_INT, 0x80, 0x05, 0x00, 0x00) 
        write_register(MSG_TYPE_THERMOCUPLE_INT, 0x81, 0x03, 0x00, 0x00)
        write_register(MSG_TYPE_SYSTEM_RESET_INT, 0x00, 0x00, 0x00, 0x00)                       
        print('Restarting')
        
def emergency_stop(self):
    global g_ControlOn
    global g_CalibrationOn
    global g_first_step
    global g_second_step
    global g_third_step
    global g_finish
    
    emergency_stop_set_labels(self)                
    g_ControlOn = False 
    g_CalibrationOn = False 
    g_first_step = False 
    g_second = False 
    g_third_step = False 
    g_finish = False
    
    set_power = set_power_in_perc(POWER_STAND_BY)
    write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)    
    
def set_power_in_perc(self):
    return MAXIMUM_TAP - round((self/100)*MAXIMUM_TAP)

def taps_to_perc(self):
    return '%i'%(((MAXIMUM_TAP-self)/MAXIMUM_TAP)*100) + '%'

def perc_to_taps(self):
    value = int(self.split('%')[0])
    return set_power_in_perc(value)
    
def time_in_secs():
    time_now = localtime()
    return time_now[3]*3600 + time_now[4]*60 + time_now[5]
        
def stop_all_timer(self):
    self.m_timer2.Stop()
    self.m_timer3.Stop()
    self.m_timer4.Stop()
    self.m_timer5.Stop()             
    
def set_initial_usb_status(self):
    # status
    functions.set_sText(self.m_staticText24, 'Com. USB: no conectado')
    functions.set_sText(self.m_staticText25, 'Com. Termocupla: ')
    functions.set_sText(self.m_staticText26, 'Com. Potenciometro: ')

def raise_error(self, arg_value = ''):
    if self == 'USB error':
        wx.MessageBox('USB No conectado', \
                        'Error', wx.OK | wx.ICON_ERROR) 
        
    elif self == 'Control and Calibration are equals':
        wx.MessageBox('El control y la calibración están ambos activados \
                        \nDesactive ambos y vuelva a intentarlo', \
                        'Error', wx.OK | wx.ICON_ERROR) 
                        
    elif self == 'Calibration finished':
        wx.MessageBox('Proceso de calibración terminado', \
                        'Información', wx.OK | wx.ICON_INFORMATION) 

    elif self == 'Calibration time exceed':
        wx.MessageBox('Proceso de calibración terminado por tiempo excedido', \
                        'Información', wx.OK | wx.ICON_INFORMATION) 
        
    elif self == 'Calibration negative derivative':        
        wx.MessageBox('Proceso de calibración terminado por incremento negativo', \
                        'Información', wx.OK | wx.ICON_INFORMATION)
    
    elif self == 'Calibration is running':
        wx.MessageBox('La calibración esta en proceso \
                       \nFinalice la actual para comenzar otra', \
                        'Error', wx.OK | wx.ICON_ERROR)

    elif self == 'Control is running':
        wx.MessageBox('El control esta en proceso \
                       \nFinalice la actual para comenzar calentamiento rapido', \
                        'Error', wx.OK | wx.ICON_ERROR) 
                                
    elif self == 'temp error':        
        string = 'Error al leer dato: ' + str(arg_value) 
        # string += '\nEl rango es de 10 - 100'
        wx.MessageBox(string, 'Temperatura fuera de Rango', wx.OK | wx.ICON_ERROR)    

    elif self == 'perc error':        
        string = 'Error al leer dato: ' + str(arg_value) 
        string += '\nEl rango es de 10 - 100'
        wx.MessageBox(string, 'Potencia fuera de Rango', wx.OK | wx.ICON_ERROR)

    elif self == 'Calibracion existente':
        return wx.MessageBox('Existe una calibración previa para el objetivo \
                        \n¿Desea utilizar dichos parametros?', \
                        'Información', wx.YES_NO | wx.ICON_INFORMATION) 
        
def validate_temp(self):
    if self >= TEMP_VALID_MIN and self <= TEMP_VALID_MAX:
        return True 
    else: return FALSE 
    
def validate_perc(self):
    if self >= PERC_VALID_MIN and self <= PERC_VALID_MAX:
        return True 
    else: return FALSE 
    
def get_temp(self):
    try:
        value = int((functions.get_value(self)).split('ºC')[0])
        if validate_temp(value): return value 
        
    except:
        if 'value' in locals():
            raise_error('temp error', arg_value = value)        
        else:
            raise_error('temp error', arg_value = functions.get_value(self))        
        return ERROR_VALUE
        
def get_perc(self):
    try:
        value = int((functions.get_value(self)).split('%')[0])
        if validate_perc(value): return value         
        
    except:        
        if 'value' in locals():
            raise_error('perc error', arg_value = value)        
        else:
            raise_error('perc error', arg_value = functions.get_value(self))        
        return ERROR_VALUE
        
def set_temp(self, data):
    functions.set_value(self, ascii(data) + 'ºC')                             

def set_perc(self, data):
    functions.set_value(self, ascii(data) + '%')                                 
        
def get_auto_parameters():    
    file = open(g_pid_file_name, 'r')
    a = file.read().split(';')
    
    kp = float(a[0].split('=')[1])
    ti = float(a[1].split('=')[1])
    file.close()
            
    return kp, ti
        
def get_slow_approach_params():
    temp = []
    pwr = []
    
    file = open(g_slow_approach_filename, 'r')
    a = file.readlines()
    for i in a:
        temp.append(int(i.split()[0]))
        pwr.append(int(i.split()[1]))
            
    return temp, pwr 
    
def write_slow_approach_params(self, pwr_step):
    file = open(g_slow_approach_filename, 'w')    
    
    for i, k in enumerate(self):
        file.write(ascii(k) + '\t' + ascii(pwr_step[i]) + '\n')
        
    file.close()
    
def create_csv():
    global g_csv_name
    global g_csv_file
    global g_csv_data_temp
    global g_csv_data_pwr
    global g_csv_time_to_save
    global g_csv_time
    
    g_csv_name = 'capture_'
    g_csv_name = g_csv_name + strftime("%Y%m%d_%H-%M-%S.csv", localtime())
    g_csv_file = open(g_csv_name, 'a')
    g_csv_data_temp.clear()
    g_csv_data_pwr.clear()
    g_csv_time_to_save = 0
    g_csv_time = 0
    g_csv_file.write('Tiempo[seg];Temperatura[ºC];Potencia[%]\n')
    
def refresh_file():
    global g_csv_file
    
    g_csv_file.close()
    g_csv_file = open(g_csv_name, 'a')
    
def activate_manual_control(self):
    # power 
    self.m_textCtrl14.SetEditable(True)    
    self.m_button51.Show()
    # general 
    functions.set_sText(self.m_staticText76, 'Manual')     
    
def deactivate_manual_control(self):
    # power
    self.m_textCtrl14.SetEditable(False)    
    self.m_button51.Hide()
    # general
    functions.set_sText(self.m_staticText692, '') 
    functions.set_sText(self.m_staticText841, '') 
    functions.set_sText(self.m_staticText82, '')
    functions.set_sText(self.m_staticText85, '')          

def debug_print_pid_params():
    print('..............................\n')
    print('temp. objetivo: ', g_temp_obj)           
    print('temp. de quiebre: ', g_temp_cutoff_step_1)
    print('potencia step 1: ', g_step_1)
    print('potencia step 2: ', g_step_2)
    print('Kp = ', g_Kp, 'Ki = %.3f'%(g_Ki), 'Ti = ', g_Ti)
    print('integral error: ', g_integral)
    print('pid offset: ', taps_to_perc(g_pid))    
    print('method: ', hex(g_method))
    print('temp. cooling = ', g_temp_cooling)
    print('Derivada: ', g_maximum_derivate)
    
def debug_print_cal_params():    
        print('temp. objetivo: ', g_temp_obj)    
        print('temp. corte: ', g_temp_cutoff_step_1)                            
        print('potencia step 1: ', g_step_1)
        print('potencia step 2: ', g_step_2)
        print('tiempo estacionario: ', g_time_to_detect_stationary)        
        print('derivada nula: ', DIFF_EQU_TO_ZERO)                            
    
def emergency_stop_set_labels(self):
    #general 
    functions.set_sText(self.m_staticText70, 'OFF')
    functions.set_sText(self.m_staticText76, 'Manual')       
    functions.set_sText(self.m_staticText68, 'OFF')
    functions.set_sText(self.m_staticText692, '') 
    functions.set_sText(self.m_staticText841, '')
    functions.set_sText(self.m_staticText82, '')
    functions.set_sText(self.m_staticText85, '')    

    activate_manual_control(self)    

def plot_cont():
    global g_fig
    global g_ax
    global g_ax2
    global g_temp_data
    global g_power_data
    
    g_temp_data.clear()
    g_power_data.clear()
    g_fig = plt.figure()
    
    # mismo grafico distinta escala
    g_ax = g_fig.add_subplot(1,1,1)
    g_ax2 = g_ax.twinx()
    
    # dos graficos distintos
    # g_ax = g_fig.add_subplot(2,1,1)
    # g_ax2 = g_fig.add_subplot(2,1,2)

def update(i):        
    global g_ax
    global g_ax2
    
    #scale in samples
    # x = range(len(g_temp_data))    
    
    #scale in seconds
    if len(g_temp_data) and (not g_stop_animation):
        x = np.linspace(0, (len(g_temp_data)-1)*(g_sampling_period/1000), len(g_temp_data))
        x = x.tolist()
        
        g_ax.clear()
        g_ax2.clear()
        
        g_ax.grid(b=True, which='major', axis='both', linewidth=0.3)
        # g_ax.set_xlabel('Tiempo [s]') 
        # g_ax.set_ylabel('Temperatura [°C]')
        
        g_ax.plot(x, g_temp_data, linewidth = 0.8)        
        
        # g_ax2.grid(b=True, which='major', axis='both', linewidth=0.3) #solo en dos graficos 
        g_ax2.plot(x, g_power_data, linewidth = 0.6, color='r')                
    
def logger_init():
    global g_handler
    global g_logger
    
    g_logger = logging.getLogger(__name__)
    g_logger.setLevel(logging.INFO)
    
    # create a file g_handler
    g_handler = logging.FileHandler('app.log')
    g_handler.setLevel(logging.INFO)

    # create a logging format
    formatter = logging.Formatter('%(asctime)s%(message)s')
    g_handler.setFormatter(formatter)

    # add the handlers to the logger
    g_logger.addHandler(g_handler)

    g_logger.info(' -- Control Logger Init --')    
    
def flt_clear():
    global g_thermocouple_FLT_Clear
    
    #CLEAR STATUS BIT 
    g_thermocouple_FLT_Clear[4] = g_reg_values[MAX31856.REG_READ_CR0] | MAX31856.CR0_FAULTCLR                                  
    g_thermocouple_FLT_Clear[7] = functions.crc_calc(g_thermocouple_FLT_Clear, LENGTH_OF_MSG)                            
    
    if not g_usb_serial_status: g_usb_serial.write(serial.to_bytes(g_thermocouple_FLT_Clear))
    else: raise_error('USB error')    
                
def send_auto_on():
    global g_thermocouple_auto_on
    global g_thermocouple_avg_4
    
    #Send prom = 4 
    g_thermocouple_avg_4[4] = g_reg_values[MAX31856.REG_READ_CR1] & MAX31856.REG_CR1_MASK_TERMTYPE
    g_thermocouple_avg_4[4] = g_thermocouple_avg_4[4] | MAX31856.PROM4
    g_thermocouple_avg_4[7] = functions.crc_calc(g_thermocouple_avg_4, LENGTH_OF_MSG)           
    if not g_usb_serial_status: g_usb_serial.write(serial.to_bytes(g_thermocouple_avg_4))     
    else: raise_error('USB error')
    
    #Send auto-convertion on     
    g_thermocouple_auto_on[4] = MAX31856.REG_CR0_VALUE    
    g_thermocouple_auto_on[7] = functions.crc_calc(g_thermocouple_auto_on, LENGTH_OF_MSG)               
    if not g_usb_serial_status: g_usb_serial.write(serial.to_bytes(g_thermocouple_auto_on))     
    else: raise_error('USB error')      
    
def write_register(msg, reg1, value1, reg2, value2):    
    data = []
    
    data.append(reg1)
    data.append(value1)
    data.append(reg2)
    data.append(value2)    
    data.insert(0,msg)
    data.insert(0,LENGTH_OF_MSG)
    data.insert(0,BIT_START)    
    data.append(functions.crc_calc(data, LENGTH_OF_MSG))
    
    if not g_usb_serial_status: g_usb_serial.write(serial.to_bytes(data))
    else: raise_error('USB error')
        
def create_register(msg, reg1, value1, reg2, value2):    
    data = []
    
    data.append(reg1)
    data.append(value1)
    data.append(reg2)
    data.append(value2)    
    data.insert(0,msg)
    data.insert(0,LENGTH_OF_MSG)
    data.insert(0,BIT_START)    
    data.append(functions.crc_calc(data, LENGTH_OF_MSG))
    
    print(data)
    return serial.to_bytes(data)

def check_usb_serial(self):     
    global g_usb_serial
    global g_usb_serial_status
    
    if g_usb_serial_status: 
        port_name = ''
        port_serial_number = ''
            
        com_ports = list(port_list.comports())
        for i in com_ports:
            if i.serial_number == USB_SERIAL_NUMBER:
                port_name = i.device        
                port_serial_number = USB_SERIAL_NUMBER
    
        if port_name and port_serial_number:        
            try:
                g_usb_serial = serial.Serial( port=port_name, baudrate=115200)
                g_usb_serial.set_buffer_size(rx_size = 4096, tx_size = 4096)                
                g_usb_serial.reset_input_buffer()
                g_usb_serial.reset_output_buffer()                      
                g_usb_serial_status = False
                self.m_timer2.Start(PERIOD_TO_READ_USB_CHAR) # readCharUSB
                self.m_timer3.Start(DELAY_TO_SEND_DEFAULT_CONFIG) # testing thermocouple                
            except serial.SerialException as error:
                print('No conectado', error)    
                g_usb_serial_status = True                
                g_usb_serial.close()
                stop_all_timer(self)
            
            if g_usb_serial.is_open:                                                
                # status
                functions.set_sText(self.m_staticText24, 'Com. USB: ' + port_name)
                # general
                functions.set_sText(self.m_staticText74, 'Endendido...esperando comunicación')                
        else:
            # general
            functions.set_sText(self.m_staticText74, 'Apagado')

def process_data(self):
    global g_usb_serial_buffer
    global g_bit_start
    global g_length_found
    global g_new_msg
    global g_msg_length 
    global g_counter
    global g_msg_recieve 

    for i in g_usb_serial_buffer:        
        if (i == BIT_START) and (g_bit_start == False):  
            g_msg_recieve += functions.add_value_in_hex(i, 1)             
            g_bit_start = True
        
        elif (g_bit_start == True) and (g_length_found == False):
            g_msg_recieve += functions.add_value_in_hex(i, 1)
            g_msg_length = i
                        
            if g_msg_length == LENGTH_OF_MSG: 
                g_length_found = True
                g_counter = 0
            else:
                g_bit_start = False
                g_length_found = False
                g_new_msg = False                
                g_msg_length = 0
                g_counter = 0
                g_msg_recieve = '' 
        
        elif (g_bit_start == True) and (g_length_found == True): 
            g_msg_recieve += functions.add_value_in_hex(i, 1)
            g_counter+=1
            if g_counter == (g_msg_length + 1): 
                g_bit_start = False
                g_length_found = False
                g_new_msg = True                
            
        if g_new_msg == True:            
            print('nuevo mensaje = ', g_msg_recieve)                                   
            process_msg(self)
            g_new_msg = False
            g_counter = 0
            g_msg_length = 0
            g_msg_recieve = '' 

    g_usb_serial_buffer = b''
    
def process_msg(self):                
    #global register
    global g_reg_values
    global g_cold_junction    
    #pid 
    global g_Kp
    global g_Ti    
    global g_integral 
    global g_pid
    #slow approach
    global g_method
    global g_tries
    #all method
    global g_CalibrationOn
    global g_ControlOn
    global g_step_2
    global g_first_step 
    global g_second_step
    global g_third_step
    global g_finish
    global g_data_for_estimate 
    global g_diff_data 
    global g_procedure_str
    #plot
    global g_temp_data
    global g_power_data
    #logger
    global g_pwr_horno
    global g_data_per_second
    global g_csv_data_pwr
    global g_csv_data_temp
    global g_csv_file
    global g_csv_time
    global g_csv_time_to_save    
    #alarm 
    global g_last_alarm_time    
    global g_fault_status
    
    msg_type = g_msg_recieve[4:6] 
    data = g_msg_recieve[6:14]
        
    if msg_type == MSG_TYPE_THERMOCUPLE:
        # print('data = ', data)
        data_send = int(data[0:2],16)
        data_recieve = int(data[2:4],16) #correjir en registros de dos bytes
        
        # READ register REG_READ_LTCBH and REG_READ_LTCBM (2 bytes) Thermocouple temp. 
        if data_send == MAX31856.REG_READ_LTCBH:            
                                                                                           
            data_recieve = MAX31856.lt_read(int(data[2:4], 16), int(data[4:6], 16), int(data[6:8], 16))               
            temp = '%.1f'%(data_recieve)                                   
            
            # # # CONTROL MODE # # # 
            if g_ControlOn and (not g_CalibrationOn):
                
                # # # PID METHOD ROUTINE # # #            
                if g_method == SLOW_HEATING:
                    if not g_first_step: 
                        set_power = set_power_in_perc(g_step_1) 
                        write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
                        g_pid = set_power_in_perc(g_step_2)                        
                        g_first_step = True
                    
                    elif g_first_step and (not g_second_step) and (data_recieve >= g_temp_cutoff_step_1):
                        set_power = set_power_in_perc(g_step_2) 
                        write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
                        g_second_step = True

                    elif not g_third_step:
                        if ((g_dynamic == UP) and (data_recieve >= g_temp_obj)) or \
                            ((g_dynamic == DOWN) and (data_recieve <= g_temp_obj)) or \
                                ((g_dynamic == EQUAL) and (data_recieve >= g_temp_obj)): 
                                
                                g_data_for_estimate.clear()
                                g_diff_data.clear()
                                g_third_step = True 

                                #general (borrar) 
                                functions.set_sText(self.m_staticText692, 'Error: ')
                                functions.set_sText(self.m_staticText841, 'pid: ')                   
                                                                                  
                    elif g_third_step:                                                      
                        pid_error = g_temp_obj - data_recieve                        
                        
                        # general
                        functions.set_sText(self.m_staticText82, '%.3f'%(pid_error) + 'ºC')
                        
                        if abs(pid_error) <= PID_TOLERANCE: 
                            pid_error = 0                        
                            
                        e_IT = (g_Ki * pid_error) + g_integral
                        e_PR = g_Kp * pid_error                        
                        PID = ((-1)*(e_PR + e_IT)) + g_pid                        
                        
                        pid_str = taps_to_perc(PID)
                        
                        # general
                        functions.set_sText(self.m_staticText85, pid_str)                                                                                                   
                        
                        g_integral = e_IT 
                        
                        if PID <= MAX_POWER: PID = MAX_POWER
                        elif PID >= MIN_POWER: PID = MIN_POWER
                        write_register(MSG_TYPE_POTENCIOMETER_INT, int(PID), 0x00, 0x00, 0x00)
                        
                elif g_method == FAST_HEATING:
                    # set power to step_1
                    if (not g_first_step):                                                     
                        set_power = set_power_in_perc(g_step_1) 
                        write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)                    
                        g_first_step = True
                        
                        g_procedure_str = ''
                        g_procedure_str += 'Paso 1/3: Ejecutando potencia al ' + str(g_step_1) + '%@' + str(g_temp_cutoff_step_1) + 'ºC'
                        
                        # general 
                        functions.set_sText(self.m_staticText692, g_procedure_str)                        
                        functions.set_sText(self.m_staticText841, '') 
                        functions.set_sText(self.m_staticText76, 'Acercamiento Suave')
                    
                    # set power of step_2 to step_1 - DECREASE, overpass cutoff 1 
                    elif g_first_step and (not g_second_step) and (data_recieve >= g_temp_cutoff_step_1):
                        g_step_2 = g_step_1 - (DECREASE_PWR_SLOW_APPROACH*g_tries)
                        if g_step_2 <= MIN_POWER_PER: 
                            g_ControlOn = False                            
                            g_ControlOn = False 
                            g_CalibrationOn = False 
                            
                            activate_manual_control(self)
                            emergency_stop_set_labels(self)                
        
                            set_power = set_power_in_perc(POWER_STAND_BY)
                            write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)    
                            raise_error('Calibration finished forced')
                            
                        else:
                            set_power = set_power_in_perc(g_step_2) 
                            write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
                            g_second_step = True               
                            
                            g_diff_data.clear()
                            g_data_for_estimate.clear()
                                                        
                            g_procedure_str += '\nPaso 2/3: Ejecutando potencia al ' + str(g_step_2) + '%@' + str(g_temp_obj) + 'ºC'
                            
                            # general 
                            functions.set_sText(self.m_staticText692, g_procedure_str)
                        
                    # analyze diff overpass the windows
                    elif g_first_step and g_second_step and (not g_third_step):
                        g_data_for_estimate.append(data_recieve)
                        
                        # promdia DIFF_MEAN muestras de la derivada
                        if len(g_data_for_estimate) >= DIFF_MEAN:
                            g_diff_data.append(np.mean(np.diff(g_data_for_estimate)))
                            g_data_for_estimate.clear()
                        
                        # tiempo limite para atravesar la ventana 
                        if len(g_diff_data) > TIME_TO_REACH_MAXIMUM_DERIVATE:
                            if g_tries:
                                fisrt_minimum = g_step_2 + DECREASE_PWR_SLOW_APPROACH
                            else:
                                fisrt_minimum = g_step_2
                                
                            # escribe archivo
                            file = open(g_slow_approach_filename, 'a')
                            file.write(ascii(g_temp_cutoff_step_1) + '\t' + ascii(fisrt_minimum) + '\n')
                            file.close()                                                                                                 
                                                                                                                                                                                                                                    
                            # general 
                            string = '\nParámetros: Ts: ' + ascii(g_temp_cutoff_step_1) + 'ºC' + ' - Ps: ' + ascii(fisrt_minimum) + '%'  
                            functions.set_sText(self.m_staticText841, string)

                            g_third_step = True
                            g_finish = True 
                            
                            # find parameters, send control to stand by
                            set_power = set_power_in_perc(POWER_STAND_BY)
                            write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
                            
                        # atraviesa ventana de control y toma un promedio de las ultimas 3 muestras 
                        if (data_recieve >= g_temp_obj) and (len(g_diff_data) >= 3):
                                                                                    
                            # general 
                            g_procedure_str += '\nPaso 3/3: Obteniendo derivada'
                            functions.set_sText(self.m_staticText692, g_procedure_str)
                            
                            derivada = np.mean([g_diff_data[-1], g_diff_data[-2], g_diff_data[-3]])                            
                            minimum = min(g_diff_data)
                            string = 'Derivada: '+ '%.3f'%(derivada*6) + 'ºC/seg'
                            
                            # general 
                            functions.set_sText(self.m_staticText841, string)
                            
                            # si hubo un bache se queda con la potencia anterior
                            if minimum < 0: 
                                if g_tries:
                                    fisrt_minimum = g_step_2 + DECREASE_PWR_SLOW_APPROACH
                                else:
                                    fisrt_minimum = g_step_2
                                                               
                                # escribe archivo
                                file = open(g_slow_approach_filename, 'a')
                                file.write(ascii(g_temp_cutoff_step_1) + '\t' + ascii(fisrt_minimum) + '\n')
                                file.close()  
                                
                                # general 
                                string = functions.get_sText(self.m_staticText841)
                                string += '\nParámetros: Ts: ' + ascii(g_temp_cutoff_step_1) + 'ºC' + ' - Ps: ' + ascii(fisrt_minimum) + '%'
                                
                                g_step_2 = fisrt_minimum
                                
                                g_third_step = True
                                g_finish = True
                                
                                # find parameters, send control to stand by
                                set_power = set_power_in_perc(POWER_STAND_BY)
                                write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)                                     

                                
                            # si esta por debajo de la derivada maxima y no hubo baches se queda con este valor 
                            elif (derivada <= g_maximum_derivate) and (derivada >= 0) and (minimum >= 0):                                 
                                
                                # escribe archivo
                                file = open(g_slow_approach_filename, 'a')
                                file.write(ascii(g_temp_cutoff_step_1) + '\t' + ascii(g_step_2) + '\n')
                                file.close()                                  
                                                                                                
                                # general
                                string = functions.get_sText(self.m_staticText841)
                                string += '\nParámetros: Ts: ' + ascii(g_temp_cutoff_step_1) + 'ºC' + ' - Ps: ' + ascii(g_step_2) + '%'
                                functions.set_sText(self.m_staticText841, string)

                                g_third_step = True
                                g_finish = True

                                # find parameters, send control to stand by
                                set_power = set_power_in_perc(POWER_STAND_BY)
                                write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)                                     
                                                                
                            # default vuelve a intentar con otra potencia 
                            else:                                 
                                g_third_step = True
                                set_power = set_power_in_perc(POWER_STAND_BY)
                                write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)  
                                
                                # general
                                string = functions.get_sText(self.m_staticText841)
                                string += '\nDerivada excede el limite, enfriando para proximo intento' 
                                functions.set_sText(self.m_staticText841, string) 
                                
                    # wait for cooling
                    elif g_third_step and (not g_finish):   
                        if data_recieve <= g_temp_cooling:
                            g_tries += 1
                            g_third_step = False
                            g_second_step = False
                            g_first_step = False
                            
                    elif g_finish:                        
                        if data_recieve <= g_temp_cooling:
                            
                            # desactivate control 
                            g_method = SLOW_HEATING                            
                            g_finish = False
                            g_first_step = False
                            g_second_step = False 
                            g_third_step = False
                                                                                                                
                            # general 
                            functions.set_sText(self.m_staticText692, '')                        
                            functions.set_sText(self.m_staticText841, '') 
                            functions.set_sText(self.m_staticText76, 'Control PID')                                                      
                            
                            # clear global variables  
                            g_diff_data.clear()
                            g_data_for_estimate.clear()

                                                             
            # # # CALIBRATION MODE # # #       
            elif g_CalibrationOn and (not g_ControlOn):
                
                # # # AUTO TUNNING # # #
                
                # set power to step_1
                if (not g_first_step): 
                    set_power = set_power_in_perc(g_step_1) 
                    write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)                    
                    g_first_step = True
                    
                    g_procedure_str = ''
                    g_procedure_str += 'Paso 1/3: Ejecutando potencia al' + str(g_step_1) + '%@' + str(g_temp_cutoff_step_1) + 'ºC'
                    
                    # general 
                    functions.set_sText(self.m_staticText692, g_procedure_str)
                
                # set power to step_2 across cutoff 1 
                elif g_first_step and (not g_second_step) and (data_recieve >= g_temp_cutoff_step_1):
                    set_power = set_power_in_perc(g_step_2) 
                    write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
                    g_second_step = True 
                    g_diff_data.clear()
                    g_data_for_estimate.clear()                        
                    
                    g_procedure_str += '\nPaso 2/3: Esperando regimen estacionario al ' + str(g_step_2) + '%'
                    
                    # general 
                    functions.set_sText(self.m_staticText692, g_procedure_str)
                
                # wait for stability 
                elif g_first_step and g_second_step and (not g_third_step):
                    g_data_for_estimate.append(data_recieve)                        
                    
                    if len(g_data_for_estimate) >= DIFF_MEAN:
                        g_diff_data.insert(0, np.mean(np.diff(g_data_for_estimate)))
                        g_data_for_estimate.clear()                            
                    
                        if len(g_diff_data) >= g_time_to_detect_stationary:
                            accumulated = np.sum(abs(np.array(g_diff_data[0:g_time_to_detect_stationary])))
                            
                            # general 
                            functions.set_sText(self.m_staticText841, 'Error acum.: ' + '%.3f'%(accumulated) + 'ºC/seg')
                            g_diff_data.pop()
                            
                            if accumulated <= DIFF_EQU_TO_ZERO:
                                set_power = set_power_in_perc(g_step_2 + DELTA_U) 
                                write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)                                                                                                            
                                g_diff_data.clear()
                                g_data_for_estimate.clear()
                                g_third_step = True 

                                g_procedure_str += '\nPaso 3/3: Ejecutando Zieger-Nichols Test'
                                
                                # general 
                                functions.set_sText(self.m_staticText692, g_procedure_str)                                    
                                                         
                                
                # Ziegler - Nichols test 
                elif g_third_step and (not g_finish):   
                    g_data_for_estimate.append(data_recieve)
                    
                    if len(g_data_for_estimate) >= DIFF_MEAN:
                        g_diff_data.append(np.mean(np.diff(g_data_for_estimate)))                            
                        maximum = max(g_diff_data)
                        maximum_index = g_diff_data.index(maximum)
                        g_data_for_estimate.clear()
                    
                        if maximum_index < (len(g_diff_data) - 1):                                
                            
                            # estimates parameters                                
                            tau = maximum_index * DIFF_MEAN
                            alfa = maximum
                            g_Kp = (0.9*DELTA_U_TAPS)/(alfa*tau)
                            g_Ti = 3*tau
                            
                            # general 
                            functions.set_sText(self.m_staticText841, 'Parámetros: Kp: ' + '%.3f'%(g_Kp) \
                                                                       + ' - Ti:' + '%.3f'%(g_Ti) )
                            
                            # save results in file 
                            file = open(g_pid_file_name, 'w')
                            file.write('Kp=' + '%.3f'%(g_Kp) + ';Ti=' + '%.3f'%(g_Ti))
                            file.close()   

                            # save derivate values in file 
                            file = open('diff_data', 'a')
                            file.write('New test' + '\n') 
                            for i in g_diff_data:
                                file.write(str(i) + '\n')                                        
                            file.close()                                                             
                            
                            # clear global variables  
                            g_diff_data.clear()
                            g_data_for_estimate.clear()                                
                            g_finish = True                                 
                
                elif g_finish:
                    #wait for 5 seconds to collect more data 
                    g_data_for_estimate.append(data_recieve)
                    if len(g_data_for_estimate) >= TIME_TO_FINISH_TUNNING:
                        # find parameters, send control to stand by
                        set_power = set_power_in_perc(POWER_STAND_BY)
                        write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)        
                            
                        # desactivate control 
                        g_CalibrationOn = False
                        activate_manual_control(self)
                        g_finish = False
                        raise_error('Calibration finished')
                        
                        # general 
                        functions.set_sText(self.m_staticText68, 'OFF')                                                      
                        
                        # clear global variables  
                        g_diff_data.clear()
                        g_data_for_estimate.clear()
                    
            
            # plot
            power = int((self.m_staticText66.GetLabel()).split('%')[0])
            g_temp_data.append(float(temp))
            g_power_data.append(power)	
            
            # logger 
            g_logger.info('\t' + g_cold_junction + '\t' + temp + '\t' + g_pwr_horno)                
            if g_logger_status:
                g_csv_data_pwr.append(power)
                g_csv_data_temp.append(data_recieve)
                if len(g_csv_data_temp) == DIFF_MEAN_SEC:
                    temperature = np.mean(g_csv_data_temp)
                    power = np.mean(g_csv_data_pwr)
                    g_csv_time_to_save += 1
                    g_csv_time += 1
                    g_csv_file.write('%i'%g_csv_time + ';' + '%.1f'%temperature + ';' + '%i'%power + '\n')
                    
                    g_csv_data_pwr.clear()
                    g_csv_data_temp.clear()                    
                    
                    if g_csv_time_to_save == TIME_TO_SAVE_CSV:
                        refresh_file()
                        g_csv_time_to_save = 0                        
            
            # console             
            print(temp + 'ºC')            
            
            # general 
            functions.set_sText(self.m_staticText64, temp + 'ºC')            
            functions.set_sText(self.m_staticText63, strftime('%T', localtime()))

        # READ register REG_READ_CJTH and REG_READ_CJTL (2 bytes) Cold Junction temp. 
        elif data_send == MAX31856.REG_READ_CJTH:            
            data_recieve = MAX31856.cj_read(int(data[2:4],16), int(data[4:6],16))
            
            g_cold_junction = '%.1f'%(data_recieve)                                                                        
            
            # console 
            print(g_cold_junction + 'ºC')
            
            # general 
            functions.set_sText(self.m_staticText65, g_cold_junction + 'ºC')
                                       
        # READ register CR0
        elif data_send == MAX31856.REG_READ_CR0:
            g_reg_values[MAX31856.REG_READ_CR0] = data_recieve                        
                
        # READ register CR1
        elif data_send == MAX31856.REG_READ_CR1:            
            g_reg_values[MAX31856.REG_READ_CR1] = data_recieve            
                
            # Thermocuple type
            termocupla = data_recieve & MAX31856.REG_CR1_MASK_TERMTYPE
            if termocupla == MAX31856.B_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_B)                
            elif termocupla == MAX31856.E_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_E)                
            elif termocupla == MAX31856.J_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_J)                
            elif termocupla == MAX31856.K_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_K)                
            elif termocupla == MAX31856.N_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_N)                
            elif termocupla == MAX31856.R_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_R)                
            elif termocupla == MAX31856.S_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_S)                
            elif termocupla == MAX31856.T_TYPE:
                functions.set_choice(self.m_choice5, MAX31856.TERM_T)                
            elif termocupla == MAX31856.GAIN8:
                functions.set_choice(self.m_choice5, MAX31856.GAIN_8)                
            elif termocupla == MAX31856.GAIN32:
                functions.set_choice(self.m_choice5, MAX31856.GAIN_32)                
                
        # READ register MASK
        elif data_send == MAX31856.REG_READ_MASK:                
            g_reg_values[MAX31856.REG_READ_MASK] = data_recieve
            
        # READ register CJHF
        elif data_send == MAX31856.REG_READ_CJHF:                
            g_reg_values[MAX31856.REG_READ_CJHF] = data_recieve                                                

        # READ register CJLF
        elif data_send == MAX31856.REG_READ_CJLF:                
            g_reg_values[MAX31856.REG_READ_CJLF] = data_recieve            
                
        # READ register REG_READ_LTHFTH and REG_READ_LTHFTL (2 bytes) 
        elif data_send == MAX31856.REG_READ_LTHFTH:            
            byte1 = int(data[2:4],16)
            byte2 = int(data[4:6],16)
            g_reg_values[MAX31856.REG_READ_LTHFTH] = byte1
            g_reg_values[MAX31856.REG_READ_LTHFTL] = byte2 

            data_recieve = int(MAX31856.lt_read(byte1, byte2, 0))                        
            functions.set_sText(self.m_staticText72, ascii(data_recieve) + 'ºC')
            
        # READ register REG_READ_LTLFTH and REG_READ_LTLFTL (2 bytes) 
        elif data_send == MAX31856.REG_READ_LTLFTH:                         
            byte1 = int(data[2:4],16)
            byte2 = int(data[4:6],16)
            g_reg_values[MAX31856.REG_READ_LTLFTH] = byte1
            g_reg_values[MAX31856.REG_READ_LTLFTL] = byte2            
            
        # READ register REG_READ_CJTO 
        elif data_send == MAX31856.REG_READ_CJTO:                          
            g_reg_values[MAX31856.REG_READ_CJTO] = data_recieve
            
        # READ register REG_READ_FAULT 
        elif data_send == MAX31856.REG_READ_FAULT:
            elements = self.m_listCtrl1.GetItemCount            
            fault = 0
            
            if elements: 
                functions.clear_list(self.m_listCtrl1)                
                g_last_alarm_time = time_in_secs()
                self.m_timer4.Start(PERIOD_TO_CLEAR_LIST_FLT)
                                
            if data_recieve & MAX31856.FAULT_CJRANGE:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_CJRANGE)
                fault += 1
                
            if data_recieve & MAX31856.FAULT_TCRANGE:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_OPEN)                    
                fault += 1
                
            if data_recieve & MAX31856.FAULT_CJHIGH:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_CJHIGH)                    
                fault += 1
                
            if data_recieve & MAX31856.FAULT_CJLOW:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_CJLOW)                    
                fault += 1
                
            if data_recieve & MAX31856.FAULT_TCHIGH:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_TCHIGH)                    
                fault += 1
                
            if data_recieve & MAX31856.FAULT_TCLOW:
                pass
                # functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_TCLOW)                    
                # fault += 1
                
            if data_recieve & MAX31856.FAULT_OVUV:
                functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_OVUV)                    
                fault += 1
                
            if data_recieve & MAX31856.FAULT_OPEN:
                pass
                # functions.new_alarm(self.m_listCtrl1, MAX31856.STR_FAULT_OPEN)                           
                # fault += 1
                
            if fault > 1: 
                functions.set_sText(self.m_staticText74, ascii(fault) + ' fallas encontradas')
            else: 
                functions.set_sText(self.m_staticText74, ascii(fault) + ' falla encontrada')
            
            flt_clear()
            if not g_fault_status:
                emergency_stop(self)
                g_fault_status = True 
                
        # Test de inicio 
        if(data_send == MAX31856.REG_READ_CR1 and 
            data_recieve == MAX31856.REG_DEF_CR1):            
            # status 
            functions.set_sText(self.m_staticText25, 'Com. Termocupla: Ok')
            functions.set_sText(self.m_staticText26, 'Com. Potenciómetro: Ok')
            
        print('REG GLOBAL = ', g_reg_values)
        print('...................................................................................')
    
    elif msg_type == MSG_TYPE_POTENCIOMETER:
        print('data = ', data)
        data = int(data[0:2],16) 
        g_pwr_horno = taps_to_perc(data)        
                
        functions.set_sText(self.m_staticText66, g_pwr_horno)        
        print(g_pwr_horno)
        print('...................................................................................')
        
    elif msg_type == MSG_TYPE_TICK:
        int_data = int(data[2:8], 16)
        
        # # # TODO
        
    elif msg_type == MSG_TYPE_COMMAND_POWER:
        int_data = int(data[0:2], 16)
        
        if int_data == COMMAND_POWER_ON:
            functions.set_choice(self.m_choice8, COMMAND_POWER_ON)
            print('Command power on - Software')
            print('...................................................................................')
            
        elif int_data == COMMAND_POWER_OFF:
            functions.set_choice(self.m_choice8, COMMAND_POWER_OFF)
            print('Command power off - Furnace')
            print('...................................................................................')
                        
#inherit from the MainFrame created in wxFowmBuilder and create CalcFrame
class MyProject(gui.MainFrame):
    # constructor
    def __init__(self,parent):        
        #initialize parent class        
        gui.MainFrame.__init__(self,parent)          
        functions.new_list(self.m_listCtrl1)          
        logger_init()                 
        emergency_stop_set_labels(self)
        set_initial_usb_status(self)        
                
    # destructor
    def OnClose(self, event):                        
        self.m_timer1.Stop()
        stop_all_timer(self)        
        SystemReset()
        g_usb_serial.close()
        sleep(0.5)
        self.Destroy()        
        
    # TIMER 1
    def checkSerialStatus(self, event):
        check_usb_serial(self)
        
    # TIMER 2
    def readCharUSB(self, event):        
        global g_usb_serial_buffer
        global g_usb_serial_status
        global g_usb_serial
        global g_buffer_busy
                
        try:
            if g_usb_serial.is_open:
                if g_usb_serial.in_waiting:                                
                    g_buffer_busy = True
                    g_usb_serial_buffer+= g_usb_serial.read(g_usb_serial.in_waiting)
                    g_buffer_busy = False                                
                    process_data(self) 
            
        
        except serial.SerialException as error:
            functions.set_sText(self.m_staticText24, 'Com. USB: no conectado')
            functions.set_sText(self.m_staticText25, 'Com. Termocupla: ')
            functions.set_sText(self.m_staticText26, 'Com. Potenciometro: ')
            g_usb_serial.close()
            g_usb_serial_status = True
            stop_all_timer(self)
            raise_error('USB error')                    

    # TIMER 3
    def setInitialConfig(self, event):                                  
        if not g_usb_serial_status:                                    
            g_usb_serial.write(serial.to_bytes(g_thermocouple_test))                       
            self.m_timer3.Stop()
            self.m_timer5.Start(TIME_TO_RUN_AUTOCONVERT)
        
        else: raise_error('USB error')
                        
    # TIMER 4 
    def clearListFault(self, event):
        global g_fault_status
        
        time_now = time_in_secs()
        
        if (time_now - g_last_alarm_time) > FLT_DIFFERENCE_TIME:
            self.m_timer4.Stop()            
            functions.clear_list(self.m_listCtrl1) 
            functions.set_sText(self.m_staticText74, 'Sin fallas')
            g_fault_status = False 
            
    # TIMER 5 
    def autoConversionOn(self, event):        
        self.m_timer5.Stop()
        functions.set_sText(self.m_staticText74, 'Sin fallas')                            
        send_auto_on()        
        
    # General windows
    def emergencyStop(self, event):
        emergency_stop(self)

    def changeCommandPower(self, event):
        choice = functions.get_choice(self.m_choice8)
        if choice == COMMAND_POWER_ON: 
            write_register(MSG_TYPE_COMMAND_POWER_INT, 0x01, 0, 0, 0)
        
        elif choice == COMMAND_POWER_OFF: 
            write_register(MSG_TYPE_COMMAND_POWER_INT, 0x00, 0, 0, 0)            
        
    def selectTermRange(self, event):
        bytes_to_send = b''
        choice = functions.get_choice(self.m_choice5)                
        
        if choice == MAX31856.B_TYPE:            
            tc_max = 1820                                    
            tc_min = 300            
            
        elif choice == MAX31856.E_TYPE:                        
            tc_max = 1000                                    
            tc_min = -150                        
            
        elif choice == MAX31856.J_TYPE:                        
            tc_max = 1200                                    
            tc_min = -150                        
            
        elif choice == MAX31856.K_TYPE:                        
            tc_max = 1300                                    
            tc_min = -150                        
            
        elif choice == MAX31856.N_TYPE:                        
            tc_max = 1300                                    
            tc_min = -150                        
            
        elif choice == MAX31856.R_TYPE:                        
            tc_max = 1768                                    
            tc_min = 0                        
            
        elif choice == MAX31856.S_TYPE:                        
            tc_max = 1500                                    
            tc_min = 0                        
            
        elif choice == MAX31856.T_TYPE:                        
            tc_max = 400                                    
            tc_min = -150                        
            
        else:
            tc_max = 1500                                    
            tc_min = 0                        
                                   
        choice |= (g_reg_values[MAX31856.REG_READ_CR1] & MAX31856.REG_CR1_MASK_AVGMODE)    
        write_register(MSG_TYPE_THERMOCUPLE_INT, MAX31856.REG_WRITE_CR1, choice, 0, 0)
                        
        # WRITE REG_LTHFTH and REG_LTHFTL 2 bytes        
        tc_max_high, tc_max_low = MAX31856.lt_write(tc_max)        
        if (g_reg_values[MAX31856.REG_READ_LTHFTH] != tc_max_high) or (g_reg_values[MAX31856.REG_READ_LTHFTL] != tc_max_low):        
            print('TC_MAX Changed')        
            bytes_to_send += create_register(MSG_TYPE_THERMOCUPLE_INT, MAX31856.REG_WRITE_LTHFTH, tc_max_high, MAX31856.REG_WRITE_LTHFTL, tc_max_low)    

        # WRITE REG_LTLFTH and REG_LTLFTL 2 bytes
        tc_min_high, tc_min_low = MAX31856.lt_write(tc_min)                
        if (g_reg_values[MAX31856.REG_READ_LTLFTH] != tc_min_high) or (g_reg_values[MAX31856.REG_READ_LTLFTL] != tc_min_low):
            print('TC_MIN Changed')            
            bytes_to_send += create_register(MSG_TYPE_THERMOCUPLE_INT, MAX31856.REG_WRITE_LTLFTH, tc_min_high, MAX31856.REG_WRITE_LTLFTL, tc_min_low)

        if len(bytes_to_send):
            if not g_usb_serial_status: g_usb_serial.write(bytes_to_send)
            else: raise_error('USB error')                    
    
    
    # Controller windows                                     
    def sendControlParams(self, event):        
        global g_temp_obj                  
        global g_temp_cutoff_step_1        
        global g_temp_cooling
        global g_step_1
        global g_step_2                 
        #pid
        global g_Kp
        global g_Ki
        global g_Ti
        global g_integral        
        global g_dynamic
        #general        
        global g_method
        global g_ControlOn
        global g_first_step
        global g_second_step
        global g_third_step  
        global g_finish
                               
        if not g_CalibrationOn:
                    
            # read temp 
            if g_temp_obj: 
                temp_obj_anterior = g_temp_obj 
                g_temp_obj = get_temp(self.m_textCtrl12)
            else: 
                g_temp_obj = get_temp(self.m_textCtrl12)
                temp_obj_anterior = g_temp_obj 
                
            # method
            g_method = functions.get_value(self.m_radioBtn1)            
            if g_method: 
                g_method = SLOW_HEATING 
                g_step_2 = 100
                g_temp_cutoff_step_1 = g_temp_obj - 10
            else: 
                g_method = FAST_HEATING
                                                                                                           
            g_temp_cooling = g_temp_obj - TEMP_TO_COOLING 
            
            #pid data
            functions.set_sText(self.m_staticText76, 'Control PID')                                                        
            g_Kp, g_Ti = get_auto_parameters()                        
            
            if g_Ti == 'inf': g_Ki = 0                        
            else: 
                g_Ti = float(g_Ti)            
                g_Ki = g_Kp/g_Ti
                        
            g_logger.info('\t' + 'T.obj = ' + str(g_temp_obj) + '\t' + 'Kp = ' + str(g_Kp) +  '\t' + 'Ti = ' + str(g_Ti))  
                                                                                                                                      
            # pid dynamic 
            if g_temp_obj > temp_obj_anterior:                
                g_method = SLOW_HEATING
                g_dynamic = UP 
                g_step_1 = 100
                g_step_2 = 100
                g_temp_cutoff_step_1 = g_temp_obj-100                
                g_first_step = False
                g_second_step = False
                g_third_step = False  
            
            elif g_temp_obj < temp_obj_anterior: 
                g_method = SLOW_HEATING
                g_dynamic = DOWN
                g_step_1 = 10
                g_step_2 = 10
                g_temp_cutoff_step_1 = g_temp_obj+100                
                g_first_step = False
                g_second_step = False
                g_third_step = False  
            
            elif temp_obj_anterior == g_temp_obj: 
                g_dynamic = EQUAL
                g_step_1 = 100
                if g_method == FAST_HEATING:
                    if not g_ControlOn:
                        cutoff_temp, step_2 = get_slow_approach_params()                
                        for i, k in enumerate(cutoff_temp): 
                            if k == (g_temp_obj-15):                                                                 
                                if raise_error('Calibracion existente') == wx.YES:
                                    g_temp_cutoff_step_1 = k
                                    g_step_2 = step_2[i]
                                    g_method = SLOW_HEATING                                     
                                else:
                                    functions.set_sText(self.m_staticText76, 'Acercamiento Suave')
                                    g_temp_cutoff_step_1 = g_temp_obj-15
                                    g_step_2 = 0
                                    cutoff_temp.remove(k)
                                    step_2.remove(step_2[i])
                                    write_slow_approach_params(cutoff_temp, step_2)
                                      
                                    
                        if g_method is not SLOW_HEATING:                        
                            functions.set_sText(self.m_staticText76, 'Acercamiento Suave')
                            g_temp_cutoff_step_1 = g_temp_obj-15
                            g_step_2 = 0                            
                            
                    else: raise_error('Control is running')

            g_tries = 0
            g_integral = 0                                           
            g_ControlOn = True
            g_finish = False
                                                                     
            functions.set_value(self.m_textCtrl12, str(g_temp_obj) + 'ºC')                                       
            functions.set_sText(self.m_staticText70, 'ON@'+str(g_temp_obj) + 'ºC')
                                                                                        
            deactivate_manual_control(self)
        
            debug_print_pid_params()
            
        else: raise_error('Control and Calibration are equals')                
        
    def cancelControl(self, event):
        global g_ControlOn
        global g_first_step
        global g_second_step
        global g_third_step
        global g_finish
              
        if g_ControlOn:
            
            g_ControlOn = False        
            g_first_step = False
            g_second_step = False
            g_third_step = False
            g_finish = False 
            
            set_power = set_power_in_perc(POWER_STAND_BY)
            write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00) 

            emergency_stop_set_labels(self)
            activate_manual_control(self)       

    # Calibration windows    
    def sendCalibrationParams(self, event):        
        #general
        global g_CalibrationOn
        global g_first_step
        global g_second_step
        global g_third_step
        global g_finish
        global g_temp_obj
        global g_temp_cutoff_step_1
        global g_step_1 
        global g_step_2                    
        
        if not g_ControlOn:        
            if not g_CalibrationOn:
                                        
                functions.set_sText(self.m_staticText76, 'Auto Tunning')                 
                
                g_temp_cutoff_step_1 = get_temp(self.m_textCtrl171)
                g_step_2 = get_perc(self.m_textCtrl18)
                
                set_temp(self.m_textCtrl171, g_temp_cutoff_step_1)                                 
                set_perc(self.m_textCtrl18, g_step_2) 
                                           
                # general                
                functions.set_sText(self.m_staticText68, 'ON')
                                                                                                                                                    
                g_CalibrationOn = True
                g_first_step = False
                g_second_step = False
                g_third_step = False
                g_finish = False
                
                g_step_1 = 100
                
                deactivate_manual_control(self)
                
                debug_print_cal_params()
            
            else: raise_error('Calibration is running')                                                            
        else: raise_error('Control and Calibration are equals')                                                
    
    def cancelCalibration(self, event):        
        global g_CalibrationOn        
        global g_first_step
        global g_second_step
        global g_third_step
        global g_finish
        
        if g_CalibrationOn:

            g_CalibrationOn = False
            g_first_step = False
            g_second_step = False
            g_third_step = False
            g_finish = False
                                    
            set_power = set_power_in_perc(POWER_STAND_BY)
            write_register(MSG_TYPE_POTENCIOMETER_INT, set_power, 0x00, 0x00, 0x00)
            
            emergency_stop_set_labels(self)
            activate_manual_control(self)
                        
    # Plot windows
    def startCapture(self, event):                                       
        global g_animation
        global g_stop_animation
        global g_logger_status
        
        g_logger_status = True
        g_stop_animation = False
        create_csv()        
        
        plot_cont()
        g_animation = anim.FuncAnimation(g_fig, update, interval = 500, repeat=False)
        plt.show()
                       
    def stopCapture(self, event):
        global g_stop_animation
        global g_logger_status
        
        g_stop_animation = True
        g_logger_status = False
        g_csv_file.close()

    # Potenciometer windows
    def sendPotValue(self, event):  
        power = get_perc(self.m_textCtrl14)
        if power is not ERROR_VALUE: 
            value = set_power_in_perc(power)
            functions.set_value(self.m_textCtrl14, ascii(power) + '%')
            write_register(MSG_TYPE_POTENCIOMETER_INT, value, 0x00, 0x00, 0x00)                           
        
    
        
#mandatory in wx, create an app, False stands for not deteriction stdin/stdout
#refer manual for details
app = wx.App(False)
 
#create an object of MyProject
frame = MyProject(None)
#show the frame
frame.Show(True)    
#start the applications
app.MainLoop()        
    
            