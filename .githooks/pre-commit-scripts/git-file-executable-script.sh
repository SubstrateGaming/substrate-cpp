#!/bin/sh

FILES=$(git diff --cached --name-only --diff-filter=ACM | grep '\.sh$')
for file in $FILES; do
   if [ -f "$file" ]; then
      echo "Setting execute permission on $file"
      git update-index --chmod=+x "$file"
      git add "$file"
   fi
done

exit 0
