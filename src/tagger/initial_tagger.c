#include <stdio.h>
#include <strings.h>
#include "../dictionary/dictionary_generator.h"
#include "../lib/hashmap.h"
#include "tags.h"
void apply_initial_tags(char * mem_map, map_t map){
    // loop through each line in the file and call apply_initial tag
}
/* applies initial tag based on tag frequency for a word
   args: 
        -char *mem_map_line: pointer to start of a line in mem map
        -map_t map: the hashmap with frequencies
*/
void apply_initial_tag(char *mem_map_line, map_t map){
    //memory map is a pointer to the beginning of the line in the memory map
    int hashed_value;
    // find the place to store the null byte in the string for the hashmap
    int word_len = word_length(mem_map_line);
    // buffer for storing a null terminated copy of the line
    char word_copy[word_len];
    strncpy(word_copy, mem_map_line, word_len);
    word_copy[word_len] = '\0';
    if(hashmap_get(map, word_copy, 
    (void **)&hashed_value) == MAP_MISSING)
        apply_initial_unknown_word_tag(mem_map_line);
    else    
        apply_tag(hashed_value, &mem_map_line[word_len]);
}
/* called if the word cannot be found in the hashmap */
void apply_initial_unknown_word_tag(char *mem_map_line){
    /* relies on properties of the word for tagging */
}
