from CommonFunc import *

#Ping command frames to send

#Data to be sent
Frame1 ="48656c6c6f"

response = ""
   
print "serial com script"
CommonFunc.OpenSerialPort()
#Send the list of frames 
CommonFunc.SendData(Frame1)
## Read frame sent from Application by serial port
CommonFunc.ReadData(response)	    
## Close serial port
CommonFunc.CloseSerialPort()


		



























