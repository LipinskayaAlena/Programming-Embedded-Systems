#!/bin/bash
# shows forecast for Minck each 5 seconds
source config.ini
while true
do
wget https://tut.by/ -q index.html
RESULT=$(sed -n 's/.*<span class="w-weather_temt">\(.*\)&deg;<\/span>.*/\1/ip;T;q' index.html)
echo $RESULT
rm index.html
sleep $time
done
