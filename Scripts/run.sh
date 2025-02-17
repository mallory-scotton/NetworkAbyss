#!/bin/bash

# Color constants
CO_COLOR="\033[0;34m"
OB_COLOR="\033[0;36m"
OK_COLOR="\033[0;32m"
ER_COLOR="\033[0;31m"
WA_COLOR="\033[0;33m"
NO_COLOR="\033[m"

# Text constant
compiling=`echo "compiling"`

# Get the filename without extension and path
filename=$(basename "$2")

# Print fthe current object
printf "%b%-46b" "$CO_COLOR$compiling " "$OB_COLOR$filename$NO_COLOR"

# Execute the command and parse the log
eval "$1" 2> "$2.log" | grep -v '\[.*%\]' | tee -a "$2.log"
RESULT=$?

# Check the result of the command
if [[ $RESULT -ne 0 ]]; then
  printf "%b%b\n" "$ER_COLOR" "[✖]$NO_COLOR          "
  rm -rf .build
  echo
elif [ -s "$2.log" ]; then
  printf "%b%b\n" "$WA_COLOR" "[⚠]$NO_COLOR          "
else
  printf "%b%b\n" "$OK_COLOR" "[✓]$NO_COLOR          "
fi

# Print the possible logs
if [ -f "$2.log" ]; then
  cat "$2.log"
fi
rm -f "$2.log"

# Exit with the same status has the command
exit $RESULT
