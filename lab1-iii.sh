#!/bin/bash

#Write a shell script for finding the maximum of three numbers

echo "Enter three numbers: "
read -r num1 num2 num3
if [ "$num1" -ge "$num2" ] && [ "$num1" -ge "$num3" ]; then
    echo "The maximum number is: $num1"
elif [ "$num2" -ge "$num1" ] && [ "$num2" -ge "$num3" ]; then
    echo "The maximum number is: $num2"
else
    echo "The maximum number is: $num3"
fi