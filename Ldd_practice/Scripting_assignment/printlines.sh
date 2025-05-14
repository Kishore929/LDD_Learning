#!/bin/sh

# Check if all 3 arguments are given
if [ $# -ne 3 ]; then
    echo "❌ Error: Missing arguments."
    echo "✅ Usage: $0 <filename> <start_line> <end_line>"
    exit 1
fi

filename=$1
start=$2
end=$3

# Check if file exists
if [ ! -f "$filename" ]; then
    echo "❌ File not found: $filename"
    exit 1
fi

# Validate that start and end are numbers
if ! [ "$start" -eq "$start" ] 2>/dev/null || ! [ "$end" -eq "$end" ] 2>/dev/null; then
    echo "❌ Start and end lines must be integers."
    exit 1
fi

# Show lines using sed
sed -n "${start},${end}p" "$filename"
