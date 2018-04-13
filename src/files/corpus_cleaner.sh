#!/bin/bash
# Author: Nicholas Weiland
# Sorry about this
# adds tag padding space, removes garbage data, and only keeps
# the useful columns --> [word] [tag]
CORPUSFILE=$1
awk -F "[_\r\n]" '
BEGIN {
	bad_lines = 0
	indicator = "NULL\tNULL\tNULL\t!#$&*()_+"
				#hash for !#$&*()_+ is -759758147 
}
{ 
	# sometimes patterns of 11 lines of @ symbols occur. These
	# are deleted and replaced with a one-line 
	# special indicator string. If the pattern is detected, 
	# bad_lines is 10. When bad_lines is not 0, 
	# decrement and skip the line, otherwise print the line.
	# html elements are also replaced with
	# the special string. These garbage words are usually tagged with null.
	if (bad_lines > 1)
	 	bad_lines--
	else if (bad_lines == 1){
		bad_lines--
		print indicator
	}
	else if (pattern_occurred())
	 	bad_lines = 10
	else if (current_line_is_garbage())
		print indicator
	else
		print $1 
}
# Checks if current and next 10 lines are @\tii lines.
# For some reason this pattern appears a lot and 
# I have no idea what it means. Very annoying.
function pattern_occurred(){
    if(!atsign_line($0))
        return 0
	else{
		# gets the next 10 lines and outputs them delimited by newline
        sedcmd = "RESULTX=\"$(sed -n '"'"'" FNR + 1 "," FNR + 10 "p;" FNR + 11 "q'"'"' " FILENAME "; echo x)\"; RESULT=\"${RESULTX%x}\"; printf \"%s\" \"$RESULT\"; "
		for(i = 0; i < 10; i++){
            sedcmd | getline nextline
            if (!atsign_line(nextline)){
                close(sedcmd)
                return 0
            }
		}
		#if it got to this return, there were 10 @\tii lines
		close(sedcmd)
		return 1
	}
}
#checks if word is @ symbol
function atsign_line(line){
    len = split(line, wlp, "\t")
	return len >= 4 && wlp[3] == "@"
}
#detects html lines
function current_line_is_garbage(){
	len = split($0, wlp, "\t")
	return (len < 4 || wlp[4] == null && substr(wlp[3], 0, 1) == "<")
}
' $CORPUSFILE | awk -F "\t" 'BEGIN {
	spaces = "     "
	substring = " "
	endind = 0
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
'
