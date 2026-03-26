#!/bin/bash

#Write a shell script for Fibonacci series

echo "Enter the number of terms: "
read -r n
a=0
b=1
count=0
if [ "$n" -le 0 ]; then
    echo "Please enter a positive integer."
elif [ "$n" -eq 1 ]; then
    echo "Fibonacci series: $a"
else
    echo "Fibonacci series: "
    while [ "$count" -lt "$n" ]; do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
        count=$((count + 1))
    done
    echo
fi