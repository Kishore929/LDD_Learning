#!/bin/sh

echo enter a number
read givennum


#if [ $givennum -ne 0 ]
#then
#x=$(echo $givennum | rev)
#echo $x
#fi


if [ "$givennum" -ne 0 ]; then
    reverse=0
    num=$givennum

    while [ "$num" -ne 0 ]; do
        digit=$((num % 10))
        reverse=$((reverse * 10 + digit))
        num=$((num / 10))
    done

    echo "Reversed number: $reverse"
fi