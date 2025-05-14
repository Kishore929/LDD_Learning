#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -lt 2 ]; then
    echo "❌ Error: Please provide a word and at least one file."
    echo "✅ Usage: $0 <word> <file1> [file2 ...]"
    exit 1
fi

# The first argument is the word to search for
word=$1
shift  # Shift the arguments to the left so $@ contains only file names

# Iterate over each file provided as argument
for filename in "$@"; do
    # Check if file exists
    if [ ! -f "$filename" ]; then
        echo "❌ File not found: $filename"
        continue
    fi

    # Delete lines containing the specified word using sed
    sed -i "/$word/d" "$filename"

    # Inform the user
    echo "✅ Lines containing '$word' have been deleted from $filename"
done

exit 0
