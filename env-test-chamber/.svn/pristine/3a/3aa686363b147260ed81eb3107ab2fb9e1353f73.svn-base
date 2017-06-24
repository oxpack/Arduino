#!/bin/bash
function graph {
rrdtool graph $1  --height=200 --width=750 --color=BACK#FFFFFF  --start $2 --vertical-label "°C"  DEF:temp_ave=etc.rrd:temperature:AVERAGE DEF:temp_min=etc.rrd:temperature:MIN DEF:temp_max=etc.rrd:temperature:MAX  LINE2:temp_ave#555555 LINE1:temp_min#444444 LINE1:temp_max#666666
}

#hourly
graph etc-1h.png end-1h

#daily
graph etc-1d.png end-1d

#weekly
graph etc-1w.png end-1w

#monthly
graph etc-1m.png end-1m

cp *.png /var/www/html
