#!/bin/bash

# Setup script name
name=$(basename $0)

# Flag to indicate if any file contains mixed tabs and spaces
mixed_indentation=false

# Find all text files (as per .gitattributes)
TEXT_FILES=$(git diff --cached --name-only --diff-filter=ACM)

# Regular expression pattern for lines with mixed tabs and spaces
pattern='^ *\t'

# Loop over the text files
for FILE in $TEXT_FILES; do
  # Check if the file is a text file
  if file "$FILE" | grep -q text; then
    # Check if the file contains lines with mixed tabs and spaces
    if grep -Pq "$pattern" "$FILE"; then
      echo "$name: File $FILE contains lines with mixed tabs and spaces."
      echo "$name: Please fix the indentation and try again."
      mixed_indentation=true
    fi
  fi
done

# If any file contains mixed indentation, abort the commit
if $mixed_indentation; then
  exit 1
fi

exit 0
