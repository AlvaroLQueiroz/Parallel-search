#!/bin/bash


amountPcs=$1
fileName=$2

echo "Counting numbers..."
amountNumbers=$(wc -l < $fileName)
echo "There are $amountNumbers numbers in the file."
echo

echo "Separating the numbers in files..."
split -d -n r/$amountPcs $fileName PC
echo "Separated in $amountPcs files"
echo

echo "Compiling the program..."
make
echo "Compiled"
echo

echo "Sending files to other machines"
# TODO
echo "Completed"
echo
