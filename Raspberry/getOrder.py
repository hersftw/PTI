#! /usr/bin/python
import serial, cgi, os, re, sys, string, requests

alarmSerial = serial.Serial( "/dev/ttyUSB1", baudrate=9600)

while 1:
	print "Waiting for the alarm to proc..."
	activated = alarmSerial.readline()
	print "Alarm activated! Recieved %s. Sending post request..."%activated
	payload = {"username":"pti", "password":"pti", "deviceID":"", "newstate":activated}
	r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)
	print "Request sent! Going back to the listen state..."