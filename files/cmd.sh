#!/bin/bash
CORPUSFILE=$1
PADDINGLEN=$2
PADDING=''
SEDPADDING=''
for (( i=0; i<${PADDINGLEN}; i++ ))
do PADDING+=' '
done
SEDPADDING=${PADDING:$PADDINGLEN-2}
SEDPADDING2=${PADDING:$PADDINGLEN-4}
gsed -i '/@	ii   $/{
        N;N;N;N;N;N;N;N;N;N;
        s/@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n@	ii'"$SEDPADDING"'\n/@	null'"$SEDPADDING2"'/}' "$CORPUSFILE"
