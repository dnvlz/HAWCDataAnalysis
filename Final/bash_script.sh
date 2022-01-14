#!/bin/bash
declare -a StringArray=("0" "1" "2" "3" "4" "5" "6" "7" "8" "9")
 
for val in ${StringArray[@]}
do
    root -l -b -q "ajuste_lunar.C(\"$val\",\"_charge\")" 
done