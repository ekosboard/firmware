#!/bin/bash

NAME=$1

if [ -z "$NAME" ]; then
    echo "Usage: create_widget <name>"
    exit 1
fi

NAME_UPPER=$(echo "$NAME" | tr '[:lower:]' '[:upper:]')
NAME_CAPITALIZED=$(echo "$NAME" | sed -E 's/(^|_)(.)/\U\2/g' | sed 's/_/ /g')

# paths
HEADER="../include/widget/${NAME}.h"
SOURCE="../widget/${NAME}.c"
JSON="../../../littlefs/template/${NAME}.json"

mkdir -p "$(dirname "$HEADER")"
mkdir -p "$(dirname "$SOURCE")"
mkdir -p "$(dirname "$JSON")"

# generate files
sed \
    -e "s/{{NAME}}/$NAME/g" \
    -e "s/{{NAME_UPPER}}/$NAME_UPPER/g" \
    -e "s/{{NAME_CAPITALIZED}}/$NAME_CAPITALIZED/g" \
    template.h > "$HEADER"

sed \
    -e "s/{{NAME}}/$NAME/g" \
    -e "s/{{NAME_UPPER}}/$NAME_UPPER/g" \
    template.c > "$SOURCE"

sed \
    -e "s/{{NAME}}/$NAME/g" \
    -e "s/{{NAME_CAPITALIZED}}/$NAME_CAPITALIZED/g" \
    template.json > "$JSON"

echo "✅ Widget '$NAME' created"
