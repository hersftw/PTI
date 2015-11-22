#! /usr/bin/python
import cgi, os, re, sys, string, time

print "Content-type: text/html\n\n"
form = cgi.FieldStorage()
state = form['state'].value

f = open('test.txt', 'w')
f.write(state)
f.close()

print "<p>Estat guardat: %s</p>"%state