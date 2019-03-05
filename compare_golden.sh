#!/bin/bash

for i in `ls data/*.in`; do
    golden="${i/in/out}"
    $1 < $i > out2.txt
    diff -b $golden out2.txt
    if [ $? -eq 0 ]; then
        echo "$i pass"
    else
        echo "$i fail"
    fi
done
