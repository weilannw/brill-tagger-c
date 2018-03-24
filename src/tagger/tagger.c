#include <stdlib.h>
#include "tags.h"
/* applies the tag to the place in memory where the tag starts */
void apply_tag(int tag_hash, char * line){
    hash_to_tag(tag_hash, &line[find_start_of_tag(line)]);
}
char * get_tagged_text(int tag, int index){
    return NULL;
}
/* find start end of word (delimited by tab)*/
int find_start_of_tag(char * line){
    int i = 0;
    while (line[i] != '\t' && i >= LINE_MAX_LENGTH)
        i++;
    if(line )
    return i;
}