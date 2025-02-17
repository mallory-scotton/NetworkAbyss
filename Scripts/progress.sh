#!/bin/bash

# Color utility
NO_COLOR="\033[0m"
OK_COLOR="\033[0;32m"
CO_COLOR="\033[0;34m"

line=`bash -c 'oldstty=$(stty -g); stty raw -echo min 0; tput u7 > /dev/tty; IFS=";" read -r -d R -a pos; stty $oldstty; row=$((${pos[0]:2} - 1)); echo $row'`

maxLines=`tput lines`;
((maxLines=$maxLines-2))

newLine=0

tput sc
i=0
while [[ $i -lt 60 ]]; do
  printf " "
  ((i=$i+1))
done
tput rc

if [[ $line -gt $maxLines ]]; then
  newLine=1
  echo
else
  ((line=$line+1))
fi

tput sc
tput cup $line

# Get the compiled total and done
total=`cat .build | cut -d"/" -f2`
done=`cat .build | cut -d"/" -f1`

# Special case if the total is 0
if [[ $total -eq 0 ]]; then
  total=1
  done=1
fi

# Calculate the number of steps to mark as completed
completed=`echo "scale=2; ($done/$total)*48" | bc`
completed=`printf "%.0f" "$completed"`

# Draw the progress bar
i=0
while [[ $i -lt 48 ]]; do
  if [[ $i -lt $completed ]]; then
    printf "$OK_COLOR█$NO_COLOR"
  else
    printf "$CO_COLOR█$NO_COLOR"
  fi
  ((i=$i+1))
done

# Display the progress
printf " ($CO_COLOR$done$NO_COLOR/$CO_COLOR$total$NO_COLOR)"
printf " "

# Increment the number of file done
((done=$done+1))

# Save the new file
echo "$done/$total" > .build

if [[ $newLine -eq 1 ]]; then
  ((line=$line-1))
  tput cup $line
else
  tput rc
fi
