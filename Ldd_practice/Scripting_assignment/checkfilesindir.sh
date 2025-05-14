#!/bin/bash

# Check if a directory is provided as an argument
if [ $# -ne 1 ]; then
    echo "❌ Error: Please provide a directory as an argument."
    echo "✅ Usage: $0 <directory>"
    exit 1
fi

# Check if the given argument is a valid directory
if [ ! -d "$1" ]; then
    echo "❌ Error: '$1' is not a valid directory."
    exit 1
fi

# List all files (excluding directories) in the specified directory
echo "Listing files in directory '$1':"
for file in "$1"/*; do
    if [ -f "$file" ]; then  # Check if it's a file (not a directory)
        echo "$file"
    fi
done

exit 0
