#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "../dictionary/dictionary_generator.h"
#include "../lib/hashmap.h"
#include "../io/corpus_io.h"
#include "tags.h"
#include "tagger.h"

/******** start of the initial tagging methods ********/

void apply_initial_tags(char * mem_map, map_t map){
    // loop through each line in the file and call apply_initial tag
    // this will be parallelized
}

/* applies initial tag based on tag frequency for a word
 * args: 
 *       char *: 
 *          pointer to start of a line in mem map
 *       map_t: 
 *          the hashmap with tag frequencies for each word 
 */
void apply_initial_tag(char *mem_map_line, map_t hash_map){
    //mem_map_line is a pointer to the beginning of the line in the memory map
    int hashed_value;
    // find the place to store the null byte in the string for the hashmap
    int word_len = word_length(mem_map_line);
    // buffer for storing a null terminated copy of the line
    char word_copy[word_len];
    strncpy(word_copy, mem_map_line, word_len);
    word_copy[word_len-1] = '\0';
    // fall through to unknown word tag method if word is not known,
    // otherwise apply the tag to the line in the file
    if(hashmap_get(hash_map, word_copy, 
    (void **)&hashed_value) == MAP_MISSING)
        apply_initial_unknown_word_tag(mem_map_line);
    else    
        apply_tag(hashed_value, &mem_map_line[word_len]);
}
/* called if the word cannot be found in the hashmap */
void apply_initial_unknown_word_tag(char *mem_map_line){

    /* relies on properties of the word for tagging */
}

/******** end of the initial tagging methods ********/
