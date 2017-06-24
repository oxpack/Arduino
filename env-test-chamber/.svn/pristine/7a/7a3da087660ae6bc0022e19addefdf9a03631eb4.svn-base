#!/usr/bin/python2

import serial
import sys
import time
from subprocess import call



def setpt_cmd(n):
	#this function generates the checksum and makes a string that the controller will then change
	#the setpoint

	#start identifier
	stx = '*'

	#acknowledge identifier
	ack = '^'
	
	#address.Use 00
	aa = '00'

	#command for setting fixed desired control setting
	cmd = '1c'
	dd = str(hex(int(float(n)*100)).lstrip("0x")).zfill(8)

	#build command substring
	com_str = aa + cmd + dd 
	j = 0
	for c in com_str:
		j = j + ord(c)
	chk = hex(j%256).lstrip("0x").zfill(2)
	return stx + com_str + chk + '\r'


def setpt_chg(n):
	#setup serial port
	global ser
	try:
		ser = serial.Serial(
		port='/dev/ttyUSB0',
		baudrate=9600,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS,
		timeout = 1
		)
		#try writing to the port
		ser.write(setpt_cmd(n))
		ret = ser.read(12)
		ser.close()
	except Exception as e1:
		print("error " ,str(e1))
	
if __name__ == "__main__":
	setpt = float(sys.argv[1])
	if (setpt< 10.0) or (setpt > 40.0):
		print('usage: serial_basic.py temp   10<temp<40')
		sys.exit(1)
	else:
		setpt_chg(setpt)

	
#read temperature and display with time stamp
def temp_read():
	try:
		ser = serial.Serial(
		port='/dev/ttyUSB0',
		baudrate=9600,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS,
		timeout = 1
		)
		ser.write("*0001c1\r")
		ret = ser.read(12)
		ser.close()
		ret = "0x" + ret[5:9]
		t_process = float(int(ret,0))/100
		return t_process
	except Exception as e1: 
		print("error ",str(e1))

def temp_rec(temperature):	
	# this takes the current temperature and puts in into the database
	# this would be nice to use the native python rrd calls

	rrd_cmd_str = "rrdtool update etc.rrd N:" + str(temperature) 
	call(rrd_cmd_str,shell=True)

def make_gr():
	#this should all be native code but isn't figure it out later
	call("./graph.sh",shell=True)
