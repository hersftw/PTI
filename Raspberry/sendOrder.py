#! /usr/bin/python

import serial, cgi, os, re, sys, string, time, requests, hashlib, random
from time import sleep

params = cgi.FieldStorage()
device = params['deviceID'].value
state = params['newstate'].value

#print "Content-type: text/html\n\n"

ledSerial = serial.Serial( "/dev/ttyACM0", baudrate=9600)
tempSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)
alarmSerial = serial.Serial( "/dev/ttyUSB1", baudrate=9600)

if device == "3": # Led/Rele
	m = random.getrandbits(256)
	m = str(m)
	hashm = hashlib.sha256(m).hexdigest()
	ledSerial.write(m)
	hashr = ledSerial.read(32)
	hashr = hashr.encode('hex')
	if hashr == hashm:
		ledSerial.write(state)
		state = ledSerial.readline()

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

tempSerial.write("1") #Ask for the temperature
tempS = tempSerial.readline()
temp = int(float(tempS)+0.5)

payload = {"username":"pti", "password":"pti", "deviceID":"2", "newstate":temp}
r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)
