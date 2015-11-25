import serial
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
#bluetoothSerial.write( str(param) )
bluetoothSerial.write(str(dev))
print bluetoothSerial.readline()
