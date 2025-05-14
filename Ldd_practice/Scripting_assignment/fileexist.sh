#!/bin/sh

if [ -n $1 ]
then
filename=$1
else
    echo "❌ Error: No filename provided."
    echo "✅ Usage: $0 <filename>"
    exit 1
fi

if [ -f $filename ]
then
echo file exist
else 
echo file does not exist
fi

exit 0