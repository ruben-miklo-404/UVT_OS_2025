#!/bin/bash

if [ -z "$1" ]; 
then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

DIR="$1"

if [ ! -d "$DIR" ]; 
then
    echo "Error: '$DIR' is not a valid directory."
    exit 1
fi

find "$DIR" -type f -exec du -b {} +