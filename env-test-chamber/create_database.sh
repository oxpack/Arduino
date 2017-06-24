rrdtool create etc.rrd --step 15 \
	DS:temperature:GAUGE:60:-5:50 \
	RRA:AVERAGE:0.5:1:1440 \
	RRA:MIN:0.5:1:1440 \
	RRA:MAX:0.5:1:1440 \
	RRA:AVERAGE:0.5:30:17520 \
	RRA:MIN:0.5:30:17520 \
	RRA:MAX:0.5:30:17520
	
#command for updating database with new data
	rrd update etc.rdd N:10.55
	