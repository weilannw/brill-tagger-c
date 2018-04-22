#include <stdbool.h>
#include "../tagger/tags.h"
#include "../io/corpus_io.h"
#include "rule_checker.h"
#include "rule_parser.h"

bool rem_prefix(char *word_data){return true;}
bool rem_suffix(char *word_data){return true;}
bool prefix_equals(char *word_data){return true;}
bool suffix_equals(char *word_data){return true;}
bool add_prefix(char *word_data){return true;}
bool add_suffix(char *word_data){return true;}
bool prev_wd_is(char *word_data){return true;}
bool next_wd_is(char *word_data){return true;}
bool contains_char(char *word_data){return true;}

bool prev_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[0] == tag1);
}
bool next_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1);
}
bool prev_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[1] == tag1);
}
bool next_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[1] == tag1);
}
bool prev_1_or_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[0] == tag1 ||
            info.prev_tags[1] == tag1);
}
bool next_1_or_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1 ||
            info.next_tags[1] == tag1);
}
bool prev_1_or_2_or_3_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[0] == tag1 ||
            info.prev_tags[1] == tag1 ||
            info.prev_tags[2] == tag1 );
}
bool next_1_or_2_or_3_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1 ||
            info.next_tags[1] == tag1 ||
            info.next_tags[2] == tag1 );
}
bool prev_tag_is_x_and_next_tag_is_y(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[0] == tag1 &&
            info.next_tags[0] == tag2);
}
bool prev_tag_is_x_and_next_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    return (info.prev_tags[0] == tag1 &&
            info.next_tags[1] == tag2);
}
bool next_tag_is_x_and_prev_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1 &&
            info.prev_tags[1] == tag2);
}
bool next_tag_is_x_and_next_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1 &&
            info.next_tags[1] == tag2);
}
bool prev_tag_is_x_and_prev_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    return (info.next_tags[0] == tag1 &&
            info.next_tags[1] == tag2);
}
/* anything beyond a NUL tag is treated as out of bounds */
void store_contextual_info(contextual_info_t *info, size_t index, char *corpus, size_t corpus_size){
    size_t cur_index = index;
    info->corpus = corpus;
    info->prev_tags[0] = get_next_tag_hash(&cur_index, corpus, corpus_size, true);
    info->prev_tags[1] = get_next_tag_hash(&cur_index, corpus, corpus_size, true);
    info->prev_tags[2] = get_next_tag_hash(&cur_index, corpus, corpus_size, true);
    cur_index = index;
    info->next_tags[0] = get_next_tag_hash(&cur_index, corpus, corpus_size, false);
    info->next_tags[1] = get_next_tag_hash(&cur_index, corpus, corpus_size, false);
    info->next_tags[2] = get_next_tag_hash(&cur_index, corpus, corpus_size, false);
}
int get_next_tag_hash(size_t *cur_index, char *corpus, size_t corpus_size, bool prev){
    bool outofbounds = false;
    size_t index = *cur_index;
    int hash;
    outofbounds = (prev) ? goto_prev_tag_index(&index, corpus):
                    goto_next_tag_index(&index, corpus, corpus_size);
    hash = (!outofbounds) ? tag_to_hash(&corpus[index]) : NUL;
    if(hash != NUL) *cur_index = index;
    //cur_index is only updated if hash is not NUL - (NUL is part of the tag enum)
    //anything beyond a null tagged word is ignored, and anything out of 
    //bounds is tagged null. These are synonymous in the code, since null
    //tagged words break continuity.
    return hash;
}    
/* checks if a contextual (known word) 
    rule applies given contextual information */
bool check_contextual_rule(contextual_rule_t rule, contextual_info_t info){
    return known_word_rules[rule.triggerfn](info, rule.arg1, rule.arg2);
}