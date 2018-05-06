#!/bin/bash
for f in `ls input_*.txt`; do
    bench < $f >out1.txt
    P2486 < $f >out2.txt
    diff out1.txt out2.txt
    if [ $? -eq 0 ]; then
        echo "$f passed"
    else
        echo "$f failed"
    fi
done

