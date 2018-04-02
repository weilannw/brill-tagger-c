#include <stdlib.h>
#include <stdbool.h>
#include "corpus_io.h"
#include "../tagger/tags.h"
 // todo: create a memory map of the corpus called corpus
#define TAGLEN 5 
// ^length of tag buffer not including null byte or newline
/* get index of tag in corpus + or - specified number of lines
   (goes backwards if bool flag is true), 0 returning the current
   index */
int get_tag_index(int cur_index, char *corpus, int how_many, bool backwards){
    if(how_many == 0) 
        return cur_index;
    int inc = backwards ? -1 : 1;
    for (int i = 0; i < how_many; i+=((corpus[cur_index] == '\t') ? 1 : 0))
        cur_index += inc;
    cur_index += backwards ? 1 : -TAGLEN;
    return cur_index;
}  
void apply_tag(int tag_hash, char * line){
    /* this will insert the tag string in the specified location */
    hash_to_tag(tag_hash, &line[word_length(line)]);
}
char * get_tagged_text(int tag, int index){
    return NULL;
}
//char * get_next_line(int index)
int word_length(char * line){
    int i = 0;
    while (line[i] != '\t'){
        if(i > LINE_MAX_LENGTH) 
            return -1; // error (avoids long looping for invalid file)
        i++;
    }
    return i;
}