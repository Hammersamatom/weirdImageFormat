#!/bin/bash

for file in ./pokemon/*/*.4bpp.lz;
do
	#echo "$file"
	FILE=$(echo "$file" | sed 's/.4bpp.lz/.png/')
	echo "$FILE"
	zopflipng -md "$FILE" "$FILE"
done

