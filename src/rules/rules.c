#include <stdbool.h>
#include "../tagger/tags.h"
#include "../io/corpus_io.h"
#include "rules.h"

/* rules for known words */
bool (*contextual_rules[13])(contextual_info_t, int, int) = {
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
    next_tag_is_x_and_prev_2_tag_is_y,
    next_tag_is_x_and_next_2_tag_is_y,
    prev_tag_is_x_and_prev_2_tag_is_y
};

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
    return (info.prev_bound <= -1 && 
            info.corpus->applied_tags[info.index-1] == tag1);
}
bool next_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_bound >= 1 && 
            info.corpus->applied_tags[info.index+1] == tag1);
}
bool prev_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.prev_bound <= -2 && 
            info.corpus->applied_tags[info.index-2] == tag1);
}
bool next_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return (info.next_bound >= 2 &&
            info.corpus->applied_tags[info.index+2] == tag1);
}
bool prev_1_or_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return ((info.prev_bound >= -1 && info.corpus->applied_tags[info.index-1] == tag1) ||
            (info.prev_bound >= -2 && info.corpus->applied_tags[info.index-2] == tag1));
}
bool next_1_or_2_tag_is(contextual_info_t info, int tag1, int tag2){
    return ((info.prev_bound >= 1 && info.corpus->applied_tags[info.index+1] == tag1) ||
            (info.prev_bound >= 2 && info.corpus->applied_tags[info.index+2] == tag1));
}
bool prev_1_or_2_or_3_tag_is(contextual_info_t info, int tag1, int tag2){
    return ((info.prev_bound >= -1 && info.corpus->applied_tags[info.index-1] == tag1) ||
            (info.prev_bound >= -2 && info.corpus->applied_tags[info.index-2] == tag1) ||
            (info.prev_bound >= -3 && info.corpus->applied_tags[info.index-3] == tag1));
}
bool next_1_or_2_or_3_tag_is(contextual_info_t info, int tag1, int tag2){
    return ((info.prev_bound >= 1 && info.corpus->applied_tags[info.index+1] == tag1) ||
            (info.prev_bound >= 2 && info.corpus->applied_tags[info.index+2] == tag1) ||
            (info.prev_bound >= 3 && info.corpus->applied_tags[info.index+3] == tag1));
}
bool prev_tag_is_x_and_next_tag_is_y(contextual_info_t info, int tag1, int tag2){
    if(info.prev_bound > -1 || info.next_bound < 1)
        return false;
    return (info.corpus->applied_tags[info.index-1] == tag1 &&
            info.corpus->applied_tags[info.index+1] == tag2);
}
bool prev_tag_is_x_and_next_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    if(info.prev_bound > -1 || info.next_bound < 2)
        return false;
    return (info.corpus->applied_tags[info.index-1] == tag1 &&
            info.corpus->applied_tags[info.index+2] == tag2);
}
bool next_tag_is_x_and_prev_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    if(info.prev_bound > -2 || info.next_bound < 1)
        return false;
    return (info.corpus->applied_tags[info.index-2] == tag1 &&
            info.corpus->applied_tags[info.index+1] == tag2);
}
bool next_tag_is_x_and_next_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    if(info.next_bound < 2)
        return false;
    return (info.corpus->applied_tags[info.index+1] == tag1 &&
            info.corpus->applied_tags[info.index+2] == tag2);
}
bool prev_tag_is_x_and_prev_2_tag_is_y(contextual_info_t info, int tag1, int tag2){
    if(info.prev_bound > -2)
        return false;
    return (info.corpus->applied_tags[info.index-1] == tag1 &&
            info.corpus->applied_tags[info.index-2] == tag2);
}
