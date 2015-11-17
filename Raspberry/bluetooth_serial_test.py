import serial
from time import sleep
 
bluetoothSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600 )
  
count = None
while count == None:
	try:
		count = int(raw_input( "Please enter the number of times to blink the LED "))
	except:
		pass    # Ignore any errors that may occur and try again
						   
bluetoothSerial.write( str(count) )
print bluetoothSerial.readline()
