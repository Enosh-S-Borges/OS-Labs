#!/bin/bash

#Write a shell script for Arithmetic operations using case statement

echo "Enter first number: "
read -r num1
echo "Enter second number: "
read -r num2
echo "Select an operation: "
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
read -r choice
case $choice in
    1)
        result=$((num1 + num2))
        echo "Result: $result"
        ;;
    2)
        result=$((num1 - num2))
        echo "Result: $result"
        ;;
    3)
        result=$((num1 * num2))
        echo "Result: $result"
        ;;
    4)
        if [ "$num2" -ne 0 ]; then
            result=$((num1 / num2))
            echo "Result: $result"
        else
            echo "Error: Division by zero is not allowed."
        fi
        ;;
    *)
        echo "Invalid choice."
        ;;
esac