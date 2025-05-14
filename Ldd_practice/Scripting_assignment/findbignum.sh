#!/bin/sh



echo "Enter first number:"
read a
echo "Enter second number:"
read b
echo "Enter third number:"
read c

big=$a

if [ "$b" -gt "$big" ]; then
  big=$b
fi

if [ "$c" -gt "$big" ]; then
  big=$c
fi

echo "🔢 Biggest number is: $big"
