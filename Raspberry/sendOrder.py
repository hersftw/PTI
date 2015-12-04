#! /usr/bin/python

import serial, cgi, os, re, sys, string, time, requests
from time import sleep

params = cgi.FieldStorage()
device = params['deviceID'].value
state = params['newstate'].value

print "Content-type: text/html\n\n"

print "<p>"+device+"</p>"
print "<p>"+state+"</p>"

tempSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)
ledSerial = serial.Serial( "/dev/ttyACM0", baudrate=9600)
#sleep(2)

#res = device+":"+state
#ledSerial.write(res)

ledSerial.write(state)
print "<p> Estat: "+ledSerial.readline()+"</p>"

tempSerial.write("1") #Ask for the temperature
tempS = tempSerial.readline()
print "<p>Temp string: "+tempS+"</p>"
temp = int(float(tempS)+0.5)

print "<p> Temp: %d</p>"%temp

payload = {"username":"pti", "password":"pti", "deviceID":"2", "newstate":temp}
r = requests.post("http://fiberparty.upc.es:8080/PTIRestBackend/webresources/devicesstatepi", data = payload)
