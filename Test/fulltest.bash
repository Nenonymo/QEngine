#!/bin/bash

n=10000 #Amount of simulations

input_file="./testMaster.txt" #Test master file

while IFS=' ' read -r test_name file_address number; do
    output=$(./../QEngine.exe "$n" < "$file_address") #Run the simulation

    count=$(echo "$output" | grep -o "\<$number\>" | wc -l) #Count the good results

    ratio=$(echo "scale=3; $count / $n" | bc) #Calculate frequency of the result

    echo "$test_name - result=$number - precision = $ratio" #Output precision
done < "$input_file"