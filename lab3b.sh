#Write a shell script to generate prime numbers

#!/bin/bash
echo "Enter the number of prime numbers to generate: "
read -r n
count=0
num=2
while [ $count -lt $n ]; do
    is_prime=1
    for ((i = 2; i <= num / 2; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            is_prime=0
            break
        fi
    done
    if [ $is_prime -eq 1 ]; then
        echo "$num"
        ((count++))
    fi
    ((num++))
done