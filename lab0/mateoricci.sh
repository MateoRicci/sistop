#!/bin/bash

grep "model name" /proc/cpuinfo #1

grep "model name" /proc/cpuinfo  | wc -l #2

wget https://www.gutenberg.org/files/11/11-0.txt && sed -i 's/Alice/Mateo/g' 11-0.txt && mv 11-0.txt mateo_in_wonderwall.txt #3 descarga - modifica - renombra

sort -n -k 5 weather_cordoba.in | awk 'NR==1{print $1, $2, $3}' && sort -nr -k 5 weather_cordoba.in | awk 'NR==1{print $1, $2, $3}' #4, maximos y minimos sobre el maximo

sort -n -k 3 atpplayers.in #5

awk '{diff = $7 - $8;print $0, diff;}' "superliga.in" | sort -k2nr -k9nr #6, se agrega una nueva columna asi mostramos la diferencia tambien

ip link show | awk '/ether/ {print "MAC address:", $2}' #7

#8
mkdir suits && cd suits && for i in {01..10}; do touch suits_S01E"$i"_es.srt; done
for file in *; do mv "$file" "$(echo "$file" | sed 's/_es//g')"; done

#opcional

ffmpeg -i exercise_9_a.49 -ss 00:00:04 -to 00:00:20 exercise_9_a_solved.mp4 #a

ffmpeg -i vocals_ok.mp3 -i base_ok.mp3 -filter_complex amix=inputs=2:duration=longest exercise_9_b.mp3 #b


