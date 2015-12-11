#! /usr/bin/python
import serial, cgi, os, re, sys, string, requests, subprocess

alarmSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)

while 1:
	print "Waiting for the alarm to proc..."
	activated = alarmSerial.read(1)
	if activated == "2":
		print "Alarm activated! Recieved %s. Sending mail..."%activated
		os.system("echo 'PEASSOPENE' | mail -s 'ALARMMMM' joanrc93@gmail.com")
#payload = {"username":"pti", "password":"pti", "deviceID":"", "newstate":activated}
	#r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)
		print "Request sent! Going back to the listen state..."
	else: print "%s recieved, going back to the listen state..."%activated
