#!/bin/bash
cat words.txt |awk '{$1=$1}1'|tr -s ' '|tr " " "\n"|sort|uniq -c|sort -k 1 -n -r|awk  '{ print $2, $1 }'
