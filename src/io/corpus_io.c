#include <stdlib.h>
#include <stdbool.h>
#include "corpus_io.h"
#include "../tagger/tags.h"
 // todo: create memory maps of the corpus

/* get index of tag in corpus + or - 1 line. result is stored in 
the current index pointer */
size_t goto_next_tag_index(size_t *cur_index, char *corpus, bool prev){
    int inc = prev ? -1 : 1;
    while (corpus[*cur_index] != '\t')
        *cur_index += inc;
    *cur_index += prev ? 1 : -(TAG_BUFFER_LENGTH-1);
    return *cur_index;
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