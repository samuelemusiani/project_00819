#!/bin/bash

SRC_FILES=$(find src/ -name "*pp")
ETC_FILES=$(find etc/ -name "*pp")

echo "Fomatting files in src/ :"
for file in $SRC_FILES;
do 
  echo "Formatting $file"
  clang-format -i "$file";
done

echo "Fomatting files in etc/ :"
for file in $ETC_FILES;
do 
  echo "Formatting $file"
  clang-format -i "$file";
done
