#!/bin/bash

input_file="testMaster.txt"

while IFS=' ' read -r test_name file_address number; do
    output=$(./../QEngine.exe 1000 < "$file_address")

    count=$(echo "$output" | grep -o "\<$number\>" | wc -l)

    ratio=$(echo "scale=3; $count / 1000" | bc)

    echo "File: $test_name - result=$number - precision = $ratio"
done < "$input_file"