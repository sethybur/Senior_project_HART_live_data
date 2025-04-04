#libraries you need
import subprocess
import matplotlib.pyplot as plt
import csv
import time
import os
import serial

#initializing variables and such
x_vals= []
y_vals= []
i=0

#serial receive and writes to a file, file is sent to a phone
ser = serial.Serial('/dev/ttyUSB0', baudrate= 9600, timeout=1)
try:
	#while loop, this should run as long as nothing ends in an error
	while True:
		data = ser.readline().decode('utf-8').strip()
		if data:
			#the data that comes in needs to be formatted before being written to the file
			print(data)
			with open('~/Documents/text.txt','a') as file:
				file.write(data)
		time.sleep(60)
		#you can put the graphing code here and change the file being sent and receive the graphs
		#everything in the while loop in serial_rec.py can go here
		
		#this is where you can change the mac address replace 0C:02:BD:89:E4:B1 with your mac address, this is the send function
		subprocess.Popen('obexftp --nopath --noconn --uuid none --bluetooth 0C:02:BD:89:E4:B1 --channel 12 -p ~/Documents/text.txt', shell=True)
		time.sleep(2)
except KeyboardInterrupt:
	print("exiting")
finally:
	ser.close()

