# Write a shell script for finding the largest of N numbers (storing the numbers in an array)

#!/bin/bash
echo "Enter the number of elements: "
read -r n
declare -a arr
echo "Enter the numbers: "
for ((i = 0; i < n; i++)); do
    read -r arr[i]
done
largest=${arr[0]}
for ((i = 1; i < n; i++)); do
    if [ "${arr[i]}" -gt "$largest" ]; then
        largest=${arr[i]}
    fi
done
echo "The largest number is: $largest"