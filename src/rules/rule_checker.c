#include "../tagger/tags.h"
#include "rule_checker.h"
#include "rule_parser.h"
#include <stdbool.h>

bool rem_prefix(char *word_data){return true;}
bool rem_suffix(char *word_data){return true;}
bool prefix_equals(char *word_data){return true;}
bool suffix_equals(char *word_data){return true;}
bool add_prefix(char *word_data){return true;}
bool add_suffix(char *word_data){return true;}
bool prev_wd_is(char *word_data){return true;}
bool next_wd_is(char *word_data){return true;}
bool contains_char(char *word_data){return true;}

bool prev_tag_is(contextual_info_t info){return true;}
bool next_tag_is(contextual_info_t info){return true;}
bool prev_2_tag_is(contextual_info_t info){return true;}
bool next_2_tag_is(contextual_info_t info){return true;}
bool prev_1_or_2_tag_is(contextual_info_t info){return true;}
bool next_1_or_2_tag_is(contextual_info_t info){return true;}
bool prev_1_or_2_or_3_tag_is(contextual_info_t info){return true;}
bool next_1_or_2_or_3_tag_is(contextual_info_t info){return true;}
bool prev_tag_is_x_and_next_tag_is_y(contextual_info_t info){return true;}
bool prev_tag_is_x_and_next_2_tag_is_y(contextual_info_t info){return true;}
bool next_tag_is_x_and_next_2_tag_is_y(contextual_info_t info){return true;}

/* checks if a contextual (known word rule) 
    rule applies to a given word index*/
bool apply_contextual_rule(contextual_rule_t rule, int index){
    contextual_info_t info;
    info.arg1 = rule.arg1;
    info.arg2 = rule.arg2;
    info.cur_index = index;
    return known_word_rules[rule.triggerfn](info);
}