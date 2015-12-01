import serial, cgi, os, re, sys, string, time, requests
from time import sleep

params = cgi.FieldStorage()
device = params['device'].value
state = params['state'].value
 
tempSerial = serial.Serial( "/dev/ttyUSB0", baudrate=9600)
ledSerial = serial.Serial( "/dev/ttyACM0", baudrate=9600)

sleep(2)

#res = device+":"+state
#ledSerial.write(res)
ledSerial.write(state)
print ledSerial.readline()

tempSerial.write("1") #Ask for the temperature
temp = tempSerial.readline()
print temp

r = requests.post("http://fiberparty.upc.edu:8080/", data = {"temp":temp})