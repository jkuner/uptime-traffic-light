#!/usr/bin/python

from xml.dom import minidom
import urllib2
import time
import datetime
import serial
import time

ser = serial.Serial('/dev/tty.usbserial-A6004pY7', 19200)
ser.write('3')

# doc=minidom.parse("sample.xml")

headers = {'x-api-key': 'MY_API_KEY'}

# Send the GET request
url = 'https://api.newrelic.com/api/v1/accounts/ACCOUNT/applications/APP/threshold_values.xml'      
req = urllib2.Request(url, None, headers)

while 1:

	# Read the response
	resp = urllib2.urlopen(req).read()

	doc = minidom.parseString(resp)

	array = doc.getElementsByTagName('threshold-values')

	values = array[0].getElementsByTagName('threshold_value')



	for value in values:
		a = dict(value.attributes.items())
		if a['name'] == "Response Time":
			response_time =  int(a['metric_value'])


	print response_time

	if response_time < 230:
		print "GREEN!!"
		ser.write('3')
	elif 230 <= response_time < 295:
		print "YELLOW!!"
		ser.write('2')
	elif response_time >= 295:
		print "RED!!"
		ser.write('1')	
	else:
		print "huh"


	time.sleep(60)
