#include <stdbool.h>
#include <stdlib.h>

typedef struct rule_arg_t{
    size_t cur_index;
    char *x;
}rule_arg_t;

typedef enum{
    PREV_TAG_IS,
    NEXT_TAG_IS,
    PREV_2_TAG_IS,
    NEXT_2_TAG_IS,
    PREV_1_OR_2_TAG_IS, 
    NEXT_1_OR_2_TAG_IS,
    PREV_1_OR_2_OR_3_TAG_IS,
    NEXT_1_OR_2_OR_3_TAG_IS,
    PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y,
    PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y,
    NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y
}known_word_rules_t;

typedef enum{
    REM_PREFIX, 
    REM_SUFFIX,
    PREFIX_EQUALS, 
    SUFFIX_EQUALS, 
    ADD_PREFIX,
    ADD_SUFFIX,
    PREV_WD_IS, 
    NEXT_WD_IS,
    CONTAINS_CHAR 
}unknown_word_rules_t;

bool rem_prefix(rule_arg_t*);
bool rem_suffix(rule_arg_t*);
bool prefix_equals(rule_arg_t*);
bool suffix_equals(rule_arg_t*);
bool add_prefix(rule_arg_t*);
bool add_suffix(rule_arg_t*);
bool prev_wd_is(rule_arg_t*);
bool next_wd_is(rule_arg_t*);
bool contains_char(rule_arg_t*);

bool prev_tag_is(rule_arg_t*);
bool next_tag_is(rule_arg_t*);
bool prev_2_tag_is(rule_arg_t*);
bool next_2_tag_is(rule_arg_t*);
bool prev_1_or_2_tag_is(rule_arg_t*);
bool next_1_or_2_tag_is(rule_arg_t*);
bool prev_1_or_2_or_3_tag_is(rule_arg_t*);
bool next_1_or_2_or_3_tag_is(rule_arg_t*);
bool prev_tag_is_x_and_next_tag_is_y(rule_arg_t*);
bool prev_tag_is_x_and_next_2_tag_is_y(rule_arg_t*);
bool next_tag_is_x_and_next_2_tag_is_y(rule_arg_t*);
/* rules for unknown words */
bool (*unknown_word_rules[9]) (rule_arg_t*) = {
    rem_prefix, //removing prefix creates a known word
    rem_suffix,
    prefix_equals, //prefix is X
    suffix_equals, 
    add_prefix, //adding prefix X creates a known word
    add_suffix,
    prev_wd_is, //previous word is X
    next_wd_is,
    contains_char //word contains character X
};
/* rules for known words */
bool (*known_word_rules[11]) (rule_arg_t*) = {
    prev_tag_is,
    next_tag_is,
    prev_2_tag_is, //word two before is tagged X
    next_2_tag_is,
    prev_1_or_2_tag_is, //word one before or two before is tagged X
    next_1_or_2_tag_is,
    prev_1_or_2_or_3_tag_is,
    next_1_or_2_or_3_tag_is,
    prev_tag_is_x_and_next_tag_is_y,
    prev_tag_is_x_and_next_2_tag_is_y, //word 2 before is tagged Y and word 1 before is tagged X
    next_tag_is_x_and_next_2_tag_is_y
};