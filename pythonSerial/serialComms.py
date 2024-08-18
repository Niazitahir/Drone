import serial
import serial.tools.list_ports as port_list
import keyboard
import time

ser = serial.Serial()
validInp = "123456789"
def printAllComms():
    ports = list(port_list.comports())
    for p in ports:
        print (p)
        
def startSerial(com:int) -> bool:
    ser.baudrate = 115200
    ser.port = f'COM' + str(com)
    print(ser)
    #Serial<id=0xa81c10, open=False>(port='COM3', baudrate=19200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    ser.open() #consider adding an exception catcher
    print(ser.is_open)
    # ser.close()
    # print(ser.is_open)

def pollSerial():
    msg = []
    counter = 0
    while(True):
        temp = ser.read().decode('utf-8')
        if (not temp.isalnum() or counter > 12):
            break
        msg.append(temp)
        counter+=1
    try:
        print(msg)
    except:
        print("Error")
    return 1
def writeSerial():
    key = keyboard.read_key(True)
    key = str(key)
    if (key in validInp):
        print(key)
        ser.write(bytes(key, 'utf-8')) 
        time.sleep(0.05) 
        data = ser.readline() 
        return data
    return -1 

    #print(key)

if __name__ == "__main__":
    startSerial(5)
    while(True):
        print(writeSerial())
