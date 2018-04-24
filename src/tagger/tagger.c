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

void apply_initial_tags(corpus_t corpus, map_t map){
    for(size_t i = 0; i < corpus.num_lines; i++){
        apply_initial_tag(corpus.words[i], map, i, corpus);
    }
}

/* applies initial tag based on tag frequency for a word
 * args: 
 *       char *: 
 *          pointer to start of a line in mem map
 *       map_t: 
 *          the hashmap with tag frequencies for each word 
 */
void apply_initial_tag(char *word, map_t hash_map, size_t index, corpus_t corpus){
    int hashed_value;
    size_t tempfix = index; // due to mem leak, this is needed because index becomes 0 after hashmap get
    if(hashmap_get(hash_map, word,
    (void **)&hashed_value) == MAP_MISSING)
        apply_initial_unknown_word_tag(word, index, corpus);
    else if (ignore_tag(hashed_value))
        corpus.applied_tags[tempfix] = corpus.tags[tempfix];
    else
        corpus.applied_tags[tempfix] = hashed_value;
}
/* called if the word cannot be found in the hashmap (unknown) */
void apply_initial_unknown_word_tag(char *word, size_t index, corpus_t corpus){

    //Do this eventually,
    /* relies on properties of the word for tagging */
}
/******** end of the initial tagging methods ********/
void apply_rule_to_corpus(contextual_rule_t rule, corpus_t corpus){
    //store indices rule applies to, then alter tags
    //contextual_info_t info;
    //malloc contextual info elsewhere, free at the end
    
    /*for(size_t i = 0; i < corpus.num_lines; i++){
        if(check_contextual_rule(rule, ){

        }
    }*/
    /*size_t cur_index;
    contextual_info_t info;
    while(cur_index < corpus_size && goto_next_tag_index(&cur_index, corpus, corpus_size)){
        store_contextual_info(&info, cur_index, corpus, corpus_size);
        if(tag_to_hash(&corpus[cur_index] ) == rule.tag1 && check_contextual_rule(rule, info))
            apply_tag(rule.tag2,  &corpus[cur_index]);
    }*/
}
/* checks if a contextual (known word) 
   rule applies, given contextual information */
bool check_contextual_rule(contextual_rule_t rule, size_t index, corpus_t corpus){
    return contextual_rules[rule.triggerfn](corpus, index, rule.arg1, rule.arg2);
}
