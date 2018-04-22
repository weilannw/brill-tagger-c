#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "../dictionary/dictionary_generator.h"
#include "../lib/hashmap.h"
#include "../io/corpus_io.h"
#include "../rules/rules.h"
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
void apply_rule_to_corpus(contextual_rule_t rule, char *corpus, size_t corpus_size){
    //store indices rule applies to, then alter tags
    
    /*size_t cur_index;
    contextual_info_t info;
    while(cur_index < corpus_size && goto_next_tag_index(&cur_index, corpus, corpus_size)){
        store_contextual_info(&info, cur_index, corpus, corpus_size);
        if(tag_to_hash(&corpus[cur_index] ) == rule.tag1 && check_contextual_rule(rule, info))
            apply_tag(rule.tag2,  &corpus[cur_index]);
    }*/
}
/*returns bool indicating if contextual info was stored
  this method allows for checking contextual rules,
  nulls break continuity so bounds are set at the beginning/end 
  of the corpus and at a null.*/
bool store_contextual_info(contextual_info_t *info, size_t index, corpus_t *corpus){
    if(corpus->applied_tags[index] == NUL)
        return false;
    info->corpus = corpus;
    info->index = index;
    int lowerbound = -3;
    int upperbound = 3;
    int diff;
    if(index < 3)
        lowerbound = -index;
    else if ((diff = corpus->num_lines-1-index) < 3)
        upperbound = diff;
    for(int i = -1; i >= lowerbound; i--)
        if(corpus->applied_tags[index+i] == NUL){
            lowerbound = i;
            break;
        }
    for(int i = 1; i <= upperbound; i++)
        if(corpus->applied_tags[index+i] == NUL){
            upperbound = i;
            break;
        }
    info->prev_bound = lowerbound;
    info->next_bound = upperbound;
    return true;
}
/* checks if a contextual (known word) 
   rule applies, given contextual information */
bool check_contextual_rule(contextual_rule_t rule, contextual_info_t info){
    return contextual_rules[rule.triggerfn](info, rule.arg1, rule.arg2);
}
