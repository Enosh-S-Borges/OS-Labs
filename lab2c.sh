#!/bin/bash

#Write a shell script to check whether a given number is palindrome or not

echo "Enter a number: "
read -r num
original_num=$num
reverse_num=0
while [ "$num" -gt 0 ]; do
    digit=$((num % 10))
    reverse_num=$((reverse_num * 10 + digit))
    num=$((num / 10))
done
if [ "$original_num" -eq "$reverse_num" ]; then
    echo "The number is a palindrome."
else
    echo "The number is not a palindrome."
fi