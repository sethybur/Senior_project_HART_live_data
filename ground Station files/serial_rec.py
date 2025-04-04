#serial receive
import serial
ser = serial.Serial('/dev/ttyUSB0', baudrate= 9600, timeout=1)
try:
	while True:
		data = ser.readline().decode('utf-8').strip()
		if data:
			print(data)
			with open('text.txt','a') as file:
				file.write(data)
except KeyboardInterrupt:
	print("exiting")
finally:
	ser.close()
	
#code for graphing
import subprocess
import matplotlib.pyplot as plt
import csv
import time
import os

x_vals= []
y_vals= []
i=0
while(True):
	with open('/home/vaughn/Documents/mock_data.csv','r') as csvfile:
		lines =csv.reader(csvfile, delimiter=',')
		for row in lines:
			number = int(row[0])
			y_vals.append(number)
			x_vals.append(i)
			i+=1
	plt.cla()
	plt.plot(x_vals,y_vals)
	plt.savefig('/home/vaughn/Documents/plot.png')
	time.sleep(60)
	subprocess.Popen('obexftp --nopath --noconn --uuid none --bluetooth 0C:02:BD:89:E4:B1 --channel 12 -p ~/Documents/plot.png', shell=True)
	x_vals= []
	y_vals= []
	os.remove('/home/vaughn/Documents/plot.png')
	

