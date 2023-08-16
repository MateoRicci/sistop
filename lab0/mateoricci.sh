#!/bin/bash

grep "model name" /proc/cpuinfo 

grep "model name" /proc/cpuinfo  | wc -l

wget https://www.gutenberg.org/files/11/11-0.txt && sed -i 's/Alice/Mateo/g' 11-0.txt && mv 11-0.txt mateo_in_wonderwall.txt