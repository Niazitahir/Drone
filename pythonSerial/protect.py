import serial
import time
ser = serial.Serial()
def startSerial(com:int) -> bool:
    ser.baudrate = 115200
    ser.port = f'COM' + str(com)
    print(ser)
    #Serial<id=0xa81c10, open=False>(port='COM3', baudrate=19200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    ser.open() #consider adding an exception catcher
    print(ser.is_open)
    # ser.close()
    # print(ser.is_open)
   
def writeSerial():
    ser.write(bytes(1, 'utf-8')) 
    time.sleep(0.05) 
    #print(key)
 
if __name__ == "__main__":
    startSerial(5)
    writeSerial()