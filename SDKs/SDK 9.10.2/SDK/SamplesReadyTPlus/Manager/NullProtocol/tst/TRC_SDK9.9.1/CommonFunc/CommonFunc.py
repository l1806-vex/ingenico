import serial
import string
import struct
import random
import time
import binascii

from ConfigNullProtocol import *

response = ""

##convert '\x01\x23' -> '0123'
def hex2str(hex):
    return binascii.hexlify(hex)
	
#convert '0123' -> '\x01\x23'
def str2hex(str):
    return binascii.unhexlify(str)

##This function will calculate datta buffer CRC
def crc(data):
	print "crc function"
	crc = 0xFFFF
	for byte in data:
		crclo = crc & 0xFF
		crchi = (crc >> 8) & 0xFF
		a = crclo ^ ord(byte)
		b = a ^ ((a << 4) & 0xFF)
		crclo = crchi ^ ((b >> 4) & 0x0F)
		crchi = b
		crchi ^= (b >> 5)
		crclo ^= ((b << 3) & 0xFF)
		crc = (crclo | (crchi << 8));
	crc ^= 0xFFFF
	return chr(crc & 0xff) + chr((crc >> 8) & 0xff)
	
##This function will open serial port
def CreateSerialPort(com_port):
	print "CreateSerialPort function"
	try:
		serial_port = serial.Serial(com_port, timeout=0, writeTimeout=10,
									baudrate=COM_BAUDRATE)
		#print "open serial port"
	except Exception as ex:
		print "Failed to create a serial port on port:", com_port
		raise ex
		
	return serial_port
		
def OpenSerialPort():
    try:
        if serial_port.isOpen() == False:
            serial_port.open()
        print "Serial port opened"
    except Exception as ex:
        print "___"
        
##This function will close serial port
def CloseSerialPort():
    print "CloseSerialPort function"
    try:
        serial_port.close()
    except Exception as ex:
        print "Failed to close the port:", com_port
        raise ex

##This function will read Ack response	
def ReadAck():
	print "ReadAck function"
	#Read ACK in one byte
	dataAck = serial_port.read(1)
	return dataAck

##This function will write ack response
def WriteAck():
	print "WriteAck function"
	#Write Ack in one byte
	serial_port.write('\x06')
	
##This function will send data to serial port
def SendData(data):
    print "SendData function"
    try:
        ## frames to send to ECR proxy
        DataToSend = str2hex(data) + crc(str2hex(data))
        resp_data = 0
        # the ACK byte is equal to 0x06
        serial_port.write(DataToSend)
        Wait(1) 		
        #Read ACK		
        resp_data = ReadAck()	
        print hex2str(resp_data)
        #Wait(1) 

    except Exception as ex:
        print "There was an error writing to the port", com_port
        raise ex
    
##This function will read data from serial port		
def ReadData(data):
    print "ReadData function"
    timespent = 0
    try:
        ## Reading the data sent from ECR proxy
        while (len(data) == 0 or len(data) == FRAME_LEN):
            data = serial_port.read(FRAME_LEN)
            Wait(0.5)
            timespent = timespent + 1
            if len(data) == FRAME_LEN:
                WriteAck()

        #Send ACK
        WriteAck()
        #wait 0.5 second
        Wait(0.5) 

    except Exception as ex:
        print "There was an error reading from the port", com_port
        raise ex
    #check if the user has canceled the transaction from the terminal.
    if len(data) == END_FRAME_LEN:
        if hex2str(data).upper().find(FRAME_OK) == -1:
            print "\n\n************************************"
            print "Transaction NOT correctly terminated"
            print "************************************\n\n"
        else:
            print "\n\n***********************************************"
            print "Transaction correctly terminated ==> Payment OK"
            print "***********************************************\n\n"
        return 1
    else:
        return 0
        
##This function will make a system sleep		
def Wait(nbScond):
    print "Wait function"
    ##wait for (nbScond) second.
    time.sleep(nbScond)	

#This function is used to exchange Data
def ExchangeFrame(Frame):
	print "ExchangeFrame function"
	## Send frame to ECR proxy by serial port
	SendData(Frame)
	## Read frame sent from ECR proxy by serial port
	return ReadData(response)
	   

##Serial port handler
serial_port = CreateSerialPort(com_port)







