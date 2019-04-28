### m_statictext
def set_sText(self, value):
    self.SetLabel(value) 

def get_sText(self):
    return self.GetLabel()       
    
### m_choice 
def set_choice(self, value):    
    self.SetSelection(value)

def get_choice(self):
    return self.GetSelection()

### m_ctrltext
def set_value(self, value):
    self.SetValue(value)       
    
def get_value(self):
    return self.GetValue() 
          

# set sampling period value 
def set_samplingPeriod(self, value):
    self.SetValue(ascii(value) + 'ms')
    
# get %per value as int     
def get_perc_int_value(self):
    return int(self.GetValue().split('%')[0])

### list alarm functions    
def clear_list(self):
    self.DeleteAllItems()    
     
def new_list(self):    
    self.InsertColumn(0,'Mensaje de Falla')    

def new_alarm(self, value):    
    index = self.GetItemCount()    
    self.InsertItem(index, '')
    self.SetItem(index, 0, '%.2i - '%(index) + value)                  
    self.SetColumnWidth(0, -1)        
        
#CRC calculation function
def crc_calc(self, length):       
    sum = 0
    for i in range(length): 
        sum+=self[i+2]
    sum = 0xff - sum
    sum&=0xff
    return sum

# int to hex converter    
def add_value_in_hex(self, bytes):        
    if bytes == 1:
        return "%.2x"%(self)  
    elif bytes == 2:
        return "%.4x"%(self)  
    elif bytes == 3:
        return "%.6x"%(self)  

# add heading in messages for protocol 
def add_heading(self, length):
    return '7e' + "%.2x"%(length) + self    