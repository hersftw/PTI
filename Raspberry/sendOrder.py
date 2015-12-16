#! /usr/bin/python

import serial, cgi, os, re, sys, string, time, requests, hashlib, random
from time import sleep

params = cgi.FieldStorage()
device = params['deviceID'].value
state = params['newstate'].value

#print "Content-type: text/html\n\n"

outdoorSerial = serial.Serial( "/dev/ttyACM0", baudrate=9600)
#outdoorSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600) #If using Bluetooth
indoorSerial = serial.Serial( "/dev/ttyACM1", baudrate=9600)
#indoorSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600) #If using Bluetooth
tempSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)
#tempSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600) #If using Bluetooth
alarmSerial = serial.Serial( "/dev/ttyUSB1", baudrate=9600)
#alarmSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600) #If using Bluetooth
	
if device == "3": # Outdoor lights
	m = random.getrandbits(256)
	m = str(m)
	hashm = hashlib.sha256(m).hexdigest()
	outdoorSerial.write(m)
	hashr = outdoorSerial.read(32)
	hashr = hashr.encode('hex')
	if hashr == hashm:
		outdoorSerial.write(state)
		state = outdoorSerial.readline()

if device == "4": # Indoor lights
	m = random.getrandbits(256)
	m = str(m)
	hashm = hashlib.sha256(m).hexdigest()
	indoorSerial.write(m)
	hashr = indoorSerial.read(32)
	hashr = hashr.encode('hex')
	if hashr == hashm:
		indoorSerial.write(state)
		state = indoorSerial.readline()		
		
if device == "5": # Alarm
	m = random.getrandbits(256)
	m = str(m)
	hashm = hashlib.sha256(m).hexdigest()
	alarmSerial.write(m)
	hashr = alarmSerial.read(32)
	hashr = hashr.encode('hex')
	if hashr == hashm:
		alarmSerial.write(state)
		state = alarmSerial.readline()

tempSerial.write("1") # Everytime we get a POST request, we update the temperature
tempS = tempSerial.readline()
temp = int(float(tempS)+0.5)

payload = {"username":"pti", "password":"pti", "deviceID":"2", "newstate":temp}
r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)