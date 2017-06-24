#!/usr/bin/python2

import sys
import time
import serial_functions


setpt = float(sys.argv[1])
if (setpt< 10.0) or (setpt > 40.0):
	print('usage: serial_basic.py temp   10<temp<40')
	sys.exit(1)
else:
	serial_functions.setpt_chg(setpt)

	
#read temperature and display with time stamp
t_process = 0.0
i=0

while True :
	#request current temperature
	t_process = serial_functions.temp_read()
	print(t_process)
	serial_functions.temp_rec(t_process)
#make the graphs every 4th cycle
	if i % 4 == 0:
		serial_functions.make_gr()
	i += 1
	time.sleep( 15 )
	

