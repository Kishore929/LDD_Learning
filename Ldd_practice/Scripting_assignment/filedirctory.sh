#!/bin/bash

# Check if at least one argument is provided
if [ $# -lt 1 ]; then
    echo "❌ Error: Please provide at least one filename or directory as an argument."
    echo "✅ Usage: $0 <file_or_directory> [file_or_directory ...]"
    exit 1
fi

# Iterate over all the arguments
for arg in "$@"; do
    # Check if the argument is a file
    if [ -f "$arg" ]; then
        # If it's a file, print the number of lines in the file
        num_lines=$(wc -l < "$arg")
        echo "$arg is a file with $num_lines line(s)."
    # Check if the argument is a directory
    elif [ -d "$arg" ]; then
        # If it's a directory, just print it's a directory
        echo "$arg is a directory."
    else
        # If it's neither a file nor a directory (could be a symlink or something else)
        echo "$arg is not a valid file or directory."
    fi
done

exit 0
