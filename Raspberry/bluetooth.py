import serial, cgi, os, re, sys, string, time
from time import sleep
 
bluetoothSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600 )
  
count = None
while count == None:
	try:
		dev = int(raw_input( "Please enter the device ID: "))
		count = int(raw_input( "Please enter the state of the art: "))
	except:
		pass    # Ignore any errors that may occur and try again
param = "dev"+str(dev)+":"+str(count)
#param = "dev"+form['dev'].value+":"+form['state'].value
bluetoothSerial.write( str(param) )
#bluetoothSerial.write(str(dev))
print bluetoothSerial.readline()