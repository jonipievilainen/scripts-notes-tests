#!/bin/bash

echo "" > /home/pi/rclone.log

sudo find /mnt/tera/ -name "._*" -exec rm -rf {} \;

rclone copy /mnt/tera/ teralevy:/tera_1/ -v --log-file /home/pi/rclone.log

OUTPUT1="$(grep 'Transferred' /home/pi/rclone.log)"
OUTPUT2="$(grep 'Errors' /home/pi/rclone.log)"
now=$(date)

echo "${OUTPUT1} \n ${OUTPUT2}" | mail -s "Rclone changes ${now}" r1jo1jo1@gmail.com
