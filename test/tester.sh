#!/bin/bash

# Define an array of binary paths
binaries=(
  /bin/ls
  /bin/pwd
  /bin/mount
  /bin/df
  /bin/du
  /usr/bin/find
  /usr/bin/diff
  /usr/bin/diff3
  /usr/bin/lsblk
  /usr/bin/ifconfig
  /usr/bin/ip
  /usr/bin/ss
  /usr/bin/netstat
  /usr/bin/lsof
  /usr/bin/nc
)

# Loop through the array and execute each binary
for binary in "${binaries[@]}"; do
    # Check if the binary file exists
    if [ -x "$binary" ]; then
        echo "Executing $binary..."
        # Execute the binary
        "$binary" > out
        ../woody_woodpacker "$binary" > /dev/null
        ./woody  > woody_out
        diff out woody_out 
        echo "[+]"
    else
        echo "Error: $binary does not exist or is not executable."
    fi
done

