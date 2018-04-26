#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include "../dictionary/dictionary_generator.h"
#include "../lib/hashmap.h"
#include "../io/corpus_io.h"
#include "../rules/rules.h"
#include "tags.h"
#include "tagger.h"

/******** start of the initial tagging methods ********/

void apply_initial_tags(corpus_t corpus, hashmap_t map){
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
void apply_initial_tag(char *word, hashmap_t hash_map, size_t index, corpus_t corpus){
    int* hashed_value = (int *)hashmap_get(&hash_map, word);
    if(!hashed_value)
        apply_initial_unknown_word_tag(word, index, corpus);
    else{
        corpus.machine_tags[index] = *hashed_value;
    }
}
/* called if the word cannot be found in the hashmap (unknown). 
   This runs basic checks for a small number of common tags before giving up */
void apply_initial_unknown_word_tag(char *word, size_t index, corpus_t corpus){
    int num_type;
    int tag;
    if(corpus.info[index].ignore_flag){
        if(corpus.human_tags[index] == NUL)
            corpus.machine_tags[index] = NUL;
        else if((tag = get_ignored_tag(word)))
            corpus.machine_tags[index] = tag;
        else{
            printf("ERROR: ignore flag was applied to word, but a tag was not found.\n");
            //ignore flag is only applied to punctuation and null, tagging should be straightforward
            exit(EXIT_FAILURE);
        }   
    }
    else if((tag = number_type(word))!=0)
        corpus.machine_tags[index] = tag;
    else if((tag = proper_noun_type(word, corpus, index))!=0)
        corpus.machine_tags[index] = tag;
    else if(tag == 0)
        corpus.machine_tags[index] = FU; // "unclassified"
    //Do this eventually,
    /* relies on properties of the word for tagging */
}
int proper_noun_type(char * word, corpus_t corpus, size_t index){
    if (isupper(word[0]) && 
        corpus.machine_tags[index] != PER &&
        corpus.machine_tags[index] != QUE &&
        corpus.machine_tags[index] != DQ &&
        corpus.machine_tags[index] != EXC){
            if(word[word_length(word)-1] == 's')
                return NN2;
            else
                return NN1;
        }
    else 
        return 0;
}

int number_type(char * word){
    bool is_hyphenated = false;
    bool is_number = false;
    char c = word[0];
    int i = 0;
    int tag;
    while(c != '\0'){
        c = word[i];
        is_number = (isdigit(c) || c == '.' || c == ',');
        is_hyphenated = (c == '-');
        if(!is_number && !is_hyphenated)
            return 0; // no cardinal tag found
        i++;
    }
    if(is_number){
        if(is_hyphenated)
            tag = MCMC;
        else if(i == 1 && word[0] == '1')
            tag = MC1;
        else
            tag = MC;
    }
    return tag;
}
int get_ignored_tag(char *word){
    switch(word[0]){
        case ':':
            return COL;
        case ';':
            return SCOL;
        case '(':
            return LPAR;
        case ')':
            return RPAR;
        case '.':
            return PER;
        case ',':
            return COM;
        case '?':   
            return QUE;
        case '!':
            return EXC;
        default:
             return 0;
    }
}
void apply_rules_to_corpus(rules_list_t rules, corpus_t corpus){
    for(int i = 0; i < rules.length; i++)
        apply_rule_to_corpus(rules.rules[i], corpus);
}
void apply_rules_to_indices(rules_list_t rules, corpus_t corpus){
    for(int i = 0; i < rules.length; i++)
        apply_rule_to_corpus(rules.rules[i], corpus);
}
/******** end of the initial tagging methods ********/

/* applies rules from a text file (not part of machine learning) */
void apply_rule_to_corpus(contextual_rule_t rule, corpus_t corpus){
    //store indices rule applies to, then alter the tags
    int64_t indices[corpus.num_lines];
    size_t index = 0;
    for(int i = 0; i < corpus.num_lines; i++)
        if(check_contextual_rule(rule, i, corpus))
            indices[index++] = i;
    for(int i = 0; i < index; i++)
        corpus.machine_tags[indices[i]] = rule.tag2;
}
/* checks if a contextual (known word) 
   rule applies, given contextual information */
bool check_contextual_rule(contextual_rule_t rule, size_t index, corpus_t corpus){
    return corpus.machine_tags[index] == rule.tag1 && contextual_rules[rule.triggerfn](corpus, index, rule.arg1, rule.arg2);
}
