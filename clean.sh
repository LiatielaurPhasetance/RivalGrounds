#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Define the path to the build directory
BUILD_DIR="$SCRIPT_DIR/build"

# Check if the current directory is the build directory
if [ "$(pwd)" != "$BUILD_DIR" ]; then
    echo "Please change directory to $BUILD_DIR first!"
    exit 1
fi

ask_permission() {
    while true; do
        read -p "$1 (y/n): " answer
        case $answer in
            [Yy]* ) return 0;;  # User agreed
            [Nn]* ) return 1;;  # User disagreed
            * ) echo "Please answer yes or no.";;  # Invalid input
        esac
    done
}

if ask_permission "Do you want to proceed with deleting all files in the build directory?"; then
    echo "Proceeding with the operation..."
    rm -rf *
else
    echo "Operation canceled."
fi

