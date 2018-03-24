#include <stdlib.h>
#include "tags.h"
void apply_tag(int tag_hash, char * line){
    int i = 0;
    /* find end of word (delimited by tab)*/
    while (line[i] != '\t')
        i++;
    hash_to_tag(tag_hash, &line[i]);
}
char * get_tagged_text(int tag, int index){
    return NULL;
}