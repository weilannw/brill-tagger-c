#!/bin/bash
awk -F "[_\r\n]" '{ 
	# if the pattern exists, print a nulled out 
	# line to signify the pattern appeared.
	if (skip_if_pattern())
	print "null\tnull\tnull\tnull\tnull"
	else
	print $1 
}
# skips 11 lines if there are 11 @\tii lines in a row
# for some reason this pattern appears a lot and 
# I have no idea what it means. Very annoying.
function skip_if_pattern(){
	split($1, arr,'\t')
	print arr[3]
	if (arr[3] == "@")
	return 1
	else 
	return 0
}
function goto_next_if_pattern(){

}
' testing-corpus.txt | 
awk -F "\t" 'BEGIN { 
	spaces = "     "
	substring = " " 
	end_ind = 0
}
{	
	endind = end_index($NF)
	substring = substr($NF, 0, endind)
	printf("%s\t%s%.*s\n", $3, substring, 5-endind, spaces);
}
# finds either last index, or @ symbol
function end_index(TAG){
	len = length(TAG)
	ind = index(TAG, "@")
	if(ind) 
	return ind-1
	return len
}
END { print $1 }
'
#substr("     ", 0, 5-(length($NF)))
