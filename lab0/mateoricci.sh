#!/bin/bash

echo ""
echo "--------------"
echo "Ejercicio 1"
echo ""

{   #try
    grep "model name" /proc/cpuinfo 
} || {  #catch
    echo "Error en el ejercicio 1"
}

echo ""
echo "--------------"
echo "Ejercicio 2"
echo ""

{   #try
    grep "model name" /proc/cpuinfo  | wc -l
} || {  #catch
    echo "Error en el ejercicio 2"
}

echo ""
echo "--------------"
echo "Ejercicio 3"
echo ""

{   #try
    wget https://www.gutenberg.org/files/11/11-0.txt && sed -i 's/Alice/Mateo/g' 11-0.txt && mv 11-0.txt mateo_in_wonderwall.txt #descarga - modifica - renombra
} || {  #catch
    echo "Error en el ejercicio 3"
}

echo ""
echo "--------------"
echo "Ejercicio 4"
echo ""

{   #try
    sort -n -k 5 weather_cordoba.in | awk 'NR==1{print $1, $2, $3}' && sort -nr -k 5 weather_cordoba.in | awk 'NR==1{print $1, $2, $3}' #maximos y minimos sobre el maximo
} || {  #catch
    echo "Error en el ejercicio 4"
}

echo ""
echo "--------------"
echo "Ejercicio 5"
echo ""

{   #try
    sort -n -k 3 atpplayers.in
} || {  #catch
    echo "Error en el ejercicio 5"
}

echo ""
echo "--------------"
echo "Ejercicio 6"
echo ""

{   #try
    awk '{diff = $7 - $8;print $0, diff;}' "superliga.in" | sort -k2nr -k9nr #se agrega una nueva columna asi mostramos la diferencia tambien
} || {  #catch
    echo "Error en el ejercicio 6"
}

echo ""
echo "--------------"
echo "Ejercicio 7"
echo ""

{   #try
    ip link show | awk '/ether/ {print "MAC address:", $2}'
} || {  #catch
    echo "Error en el ejercicio 7"
}

echo ""
echo "--------------"
echo "Ejercicio 8"
echo ""

{   #try
    mkdir suits && cd suits && for i in {01..10}; do touch suits_S01E"$i"_es.srt; done
} || {  #catch
    echo "Error en el ejercicio 8-a"
}

{   #try
    for file in *; do mv "$file" "$(echo "$file" | sed 's/_es//g')"; done
} || {  #catch
    echo "Error en el ejercicio 8-b"
}


echo ""
echo "--------------"
echo "Ejercicio opcional"
echo ""

{   #try
    ffmpeg -i exercise_9_a.49 -ss 00:00:04 -to 00:00:20 exercise_9_a_solved.mp4
} || {  #catch
    echo "Error en el ejercicio opcional-a"
}

{   #try
    ffmpeg -i vocals_ok.mp3 -i base_ok.mp3 -filter_complex amix=inputs=2:duration=longest exercise_9_b.mp3
} || {  #catch
    echo "Error en el ejercicio opcional-b"
}
