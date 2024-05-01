#!/bin/bash

for file in ./pokemon/*/*.4bpp.lz;
do
	#echo "$file"
	FILE=$(echo "$file" | sed 's/.4bpp.lz/.png/')
	echo "$FILE"
	convert "$FILE" -depth 8 "$FILE".rgba
	./a.out "$FILE".rgba "$FILE".rle
done

echo "LZ Total: $(find pokemon/* -name "*.4bpp.lz" -exec du -cb {} + | grep total)"
echo "RLE Total: $(find pokemon/* -name "*.rle" -exec du -cb {} + | grep total)"
echo "PNG Total: $(find pokemon/* -name "*.png" -not -name "footprint.png" -exec du -cb {} + | grep total)"
