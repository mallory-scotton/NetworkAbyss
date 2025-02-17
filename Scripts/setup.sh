#!/bin/bash

# Parse command line arguments
sources=$1
extension=${2:-.cpp}

# Find all the already builded objects
objects=`find -type f -iname "*.o" 2>/dev/null | sed "s|\.o$||"`

# Get the number of file in the source
toCompile=`echo $sources | wc -w`

# Loop through the sources
for source in $sources; do
  # Get the source file without extension
  basename=`basename "$source" $extension`

  # Check if there's a matching object
  if echo "$objects" | grep -q "^$basename$"; then
    # Merge the paths
    sourcePath="$source"
    objectPath="$basename.o"

    # If the source is older than the object
    if [[ "$sourcePath" -ot "$objectPath" ]]; then
      # Get the dependency file
      dependency=`echo "$objectPath" | sed "s/\.o/\.d/"`

      # Get the headers from the dependency file
      headers=`< $dependency xargs | grep -oE "[^ ]+\.h\w*"`

      echo "$headers"

      # Prepare a need to recompile
      recompile=0

      # Loop through headers
      for header in $headers; do
        # If the header is newer than the object
        if [[ "$header" -nt "$objectPath" ]]; then
          recompile=1
          break
        fi
      done

      # If the recompilation is not needed
      if [[ $recompile -eq 0 ]]; then
        ((toCompile=$toCompile-1))
      fi
    fi
  fi
done

# Save the number of compilated file
echo "0/$toCompile" > .build
