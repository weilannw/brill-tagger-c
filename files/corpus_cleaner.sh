#!/bin/bash
# Author: Nicholas Weiland
# adds tag padding space, removes garbage data, and only keeps
# the useful columns --> [word] [tag]
CORPUSFILE=$1
DESTFILE=$2
PADDINGLEN=$3
PADDING=''
SEDPADDING=''
for (( i=0; i<${PADDINGLEN}; i++ ))
do PADDING+=' '
done
SEDPADDING=${PADDING:$PADDINGLEN-2}
SEDPADDING2=${PADDING:$PADDINGLEN-4}

awk -F "[_\r\n]" '{ print $1 }' "$CORPUSFILE" |
awk -F "\t" 'BEGIN {
	paddinglen = '${PADDINGLEN}'
	padding = "'"$PADDING"'"
	tag = ""
	taglen = 0
}
{
	taglen = end_index($NF)
	tag = substr($NF, 0, taglen)
	printf("%s\t%s%.*s\n", $3, tag, paddinglen-taglen, padding)
}
# finds either last index, or @ symbol index
function end_index(TAG){
	len = length(TAG)
	ind = index(TAG, "@")
	if(ind)
	return ind-1
	return len
}
' > "$DESTFILE"
