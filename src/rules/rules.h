#ifndef rules_h
#define rules_h
#include <stdbool.h>
#include "../tagger/tags.h"
#include "../corpus/corpus_io.h"
extern bool (*contextual_rules[13])(corpus_t, size_t, int, int);
/*
Trigger function numbers: 
    0:PREV_TAG_IS
    1:NEXT_TAG_IS
    2:PREV_2_TAG_IS
    3:NEXT_2_TAG_IS
    4:PREV_1_OR_2_TAG_IS
    5:NEXT_1_OR_2_TAG_IS
    6:PREV_1_OR_2_OR_3_TAG_IS
    7:NEXT_1_OR_2_OR_3_TAG_IS
    8:PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y
    9:PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y
    10:NEXT_TAG_IS_X_AND_PREV_2_TAG_IS_Y
    11:NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y
    12:PREV_TAG_IS_X_AND_PREV_2_TAG_IS_Y
*/
typedef struct contextual_rule_t{
    int tag1;
    int tag2;
    int8_t triggerfn;
    int arg1;
    int arg2;
}contextual_rule_t;

/* length is stored for freeing */
typedef struct rules_list_t{
    contextual_rule_t *rules;
    int32_t length;
}rules_list_t;

typedef enum contextual_rules_enum_t{
    PREV_TAG_IS=0,
    NEXT_TAG_IS=1,
    PREV_2_TAG_IS=2,
    NEXT_2_TAG_IS=3,
    PREV_1_OR_2_TAG_IS=4, 
    NEXT_1_OR_2_TAG_IS=5,
    PREV_1_OR_2_OR_3_TAG_IS=6,
    NEXT_1_OR_2_OR_3_TAG_IS=7,
    PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y=8,
    PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y=9,
    NEXT_TAG_IS_X_AND_PREV_2_TAG_IS_Y=10,
    NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y=11,
    PREV_TAG_IS_X_AND_PREV_2_TAG_IS_Y=12
}contextual_rules_enum_t;


/*contextual rules rely on contextual info (tags of previous and next words) */
bool prev_tag_is(corpus_t, size_t, int, int);
bool next_tag_is(corpus_t, size_t, int, int);
bool prev_2_tag_is(corpus_t, size_t, int, int);
bool next_2_tag_is(corpus_t, size_t, int, int);
bool prev_1_or_2_tag_is(corpus_t, size_t, int, int);
bool next_1_or_2_tag_is(corpus_t, size_t, int, int);
bool prev_1_or_2_or_3_tag_is(corpus_t, size_t, int, int);
bool next_1_or_2_or_3_tag_is(corpus_t, size_t, int, int);
bool prev_tag_is_x_and_next_tag_is_y(corpus_t, size_t, int, int);
bool prev_tag_is_x_and_next_2_tag_is_y(corpus_t, size_t, int, int);
bool next_tag_is_x_and_prev_2_tag_is_y(corpus_t, size_t, int, int);
bool next_tag_is_x_and_next_2_tag_is_y(corpus_t, size_t, int, int);
bool prev_tag_is_x_and_prev_2_tag_is_y(corpus_t, size_t, int, int);

/*unknown word rules take a char* because it allows for processing of 
word itself rather than surrounding tags */
bool rem_prefix(char*);
bool rem_suffix(char*);
bool prefix_equals(char*);
bool suffix_equals(char*);
bool add_prefix(char*);
bool add_suffix(char*);
bool prev_wd_is(char*);
bool next_wd_is(char*);
bool contains_char(char*);

#endif
