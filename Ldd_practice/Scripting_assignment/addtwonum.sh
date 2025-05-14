#!/bin/sh

# Check if exactly 2 arguments are passed
if [ $# -eq 2 ]; then
    var1=$1
    var2=$2
    echo Sum: $(expr $var1 + $var2)
else
    echo "❌ Please provide exactly 2 numbers."
    echo "✅ Usage: $0 <num1> <num2>"
fi

exit 0


