#!/bin/bash

OUTPUT_FILE=camera_index_new.h

# clear the output file
> $OUTPUT_FILE

for file in `ls *.html`; do
    echo "Compressing: $file"
    gzip -kf "$file" && \
    echo "Converting $file to byte array"
    echo "/* Contents of file "$file".gz */" >> $OUTPUT_FILE
    xxd -i -u $file".gz" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
done