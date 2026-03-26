#!/bin/bash

#Write a shell script for comparing two strings

echo "Enter string-1: "
read -r str1
echo "Enter string-2: "
read -r str2
if [ "$str1" = "$str2" ]; then
    echo "The strings are equal."
else
    echo "The strings are not equal."
fi