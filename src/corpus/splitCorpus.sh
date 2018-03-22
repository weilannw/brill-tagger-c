#!/bin/bash 
percent=$1 #percentage of corpus used for training
filename="corpus.txt"
testing="testing-corpus.txt"
training="training-corpus.txt"
linecount=$(printf $(wc -l "$filename"))
bcinput="$percent / 100 * $linecount"
splitlinecount=$(echo "$bcinput" | bc -l)
trunc="$(printf $(echo "$splitlinecount" | tr '.' ' '))"
split -l "$trunc" "$filename"
mv xaa "$training"
mv xab "$testing"