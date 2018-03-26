#include <stdlib.h>
#include "corpus_io.h"
#include "../tagger/tags.h"
void apply_tag(int tag_hash, char * line){
    /* this will insert the tag string after the tab delim */
    hash_to_tag(tag_hash, &line[word_length(line)]);
}
char * get_tagged_text(int tag, int index){
    return NULL;
}
int word_length(char * line){
    int i = 0;
    while (line[i] != '\t'){
        if(i > LINE_MAX_LENGTH) 
            return -1; // error (avoids long looping for invalid file)
        i++;
    }
    return i;
}