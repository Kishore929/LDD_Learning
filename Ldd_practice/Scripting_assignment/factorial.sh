#!/bin/bash

# Check if the user has provided an argument
if [ $# -ne 1 ]; then
    echo "❌ Error: Please provide a single integer as an argument."
    echo "✅ Usage: $0 <integer>"
    exit 1
fi

# Check if the input is a valid integer
if ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "❌ Error: '$1' is not a valid integer."
    exit 1
fi

# Get the number from the argument
num=$1
factorial=1

# Calculate factorial using a loop
for ((i=1; i<=num; i++)); do
    factorial=$((factorial * i))
done

# Print the result
echo "The factorial of $num is $factorial"

exit 0
