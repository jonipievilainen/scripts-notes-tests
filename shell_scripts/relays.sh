#!/bin/bash

array=(24 10 9 11 25 8 7 12 5 6 13 19 26 16 20 21)
for id in ${array[@]}
do
    echo $id
	gpio -g mode $id out
	gpio -g write $id 0
	sleep 1
	gpio -g write $id 1
	sleep 1
done


##sed -i -e 's/\r$//' scriptname.sh
