#! /usr/bin/python

import serial, cgi, os, re, sys, string, time, requests, hashlib, random
from time import sleep

params = cgi.FieldStorage()
device = params['deviceID'].value
state = params['newstate'].value

print "Content-type: text/html\n\n"

#print "<p>"+device+"</p>"
#print "<p>"+state+"</p>"

tempSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)
ledSerial = serial.Serial( "/dev/ttyACM0", baudrate=9600)
#alarmSerial = serial.Serial( "/dev/ttyUSB1", baudrate=9600)


#res = device+":"+state
#ledSerial.write(res)
if (device == "3"):
	print "<p>DADEVAISISTHREE</p>"
	m = random.getrandbits(256)
	m = str(m)
	hashm = hashlib.sha256(m).hexdigest()
	#print hashm
	ledSerial.write(m)
	hashr = ledSerial.read(32)
	hashr = hashr.encode('hex')
	#print hashr
	if (hashr == hashm):
		print "<p>OKDAHASH</p>"
		ledSerial.write(state)
		state = ledSerial.readline()
		print "<p>Penispolla</p>"
	else:
		print "<p>HAFALLAOELSHASHASHA</p>"
	print "<p>HASHM: "+hashm+"</p>"
	print "<p>HASHR: "+hashr+"</p>"
	#print "<p> Estat: "+ledSerial.readline()+"</p>"
#elif (device == "5"):
	#alarmSerial.write(state)
print "<p>TEVIADARLATEMP</p>"
tempSerial.write("1") #Ask for the temperature
tempS = tempSerial.readline()
temp = int(float(tempS)+0.5)

print "<p> Temp: %d</p>"%temp

#payload = {"username":"pti", "password":"pti", "deviceID":"2", "newstate":temp}
#r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)
