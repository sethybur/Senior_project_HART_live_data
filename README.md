ECEC 499 senior project with HART 
Ground Station:
  Ground Station Operation Instructions:
    1.	Plug the meshtastic device into the furthest USB port on the USB splitter. The USB splitter plugs into the power port in the middle of the device.
    2.	Plug in the raspberry pi’s power to the power port closest to the edge of the device. This will be plugged into a battery bank.
    3.	It should send a file every minute to the phone which is identified in the code.
  How to change which phone it is connected to:
    1.	Power the raspberry pi, connect keyboard and mouse, and monitor. Wait for raspberry pi to boot to the desktop. (Not windows, running a version of Linux)
    2.	Click on file icon in top left.
    3.	Navigate to /users/vaughn/documents/send_file.py
    4.	Edit MAC Address in quotation marks to desired MAC address
  How to find your MAC address:
    1.	When in the desktop click on Bluetooth icon
    2.	Pair phone
    3.	Click on connected device details
    4.	MAC address of the device should be listed
