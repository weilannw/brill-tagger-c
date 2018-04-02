#include <stdbool.h>
#include "../tagger/tags.h"
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

bool prev_tag_is(contextual_info_t info){
    return tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 1, true)]) == info.tag1;
}
bool next_tag_is(contextual_info_t info){
    return tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 1, false)]) == info.tag1;
}
bool prev_2_tag_is(contextual_info_t info){
    return tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 2, true)]) == info.tag1;
}
bool next_2_tag_is(contextual_info_t info){
    return tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 2, false)]) == info.tag1;
}
bool prev_1_or_2_tag_is(contextual_info_t info){
    int tag_ind1; 
    return tag_to_hash(info.corpus[
                        (tag_ind1 = get_tag_index(info.tag_index, info.corpus, 1, true))
                                  ]
                      ) == info.tag1 ||
           tag_to_hash(info.corpus[
                                    get_tag_index(tag_ind1, info.corpus, 1, true)
                                  ]
                       ) == info.tag1;
}
bool next_1_or_2_tag_is(contextual_info_t info){
    int tag_ind1; 
    return tag_to_hash(info.corpus[
                        (tag_ind1 = get_tag_index(info.tag_index, info.corpus, 1, false))
                                  ]
                      ) == info.tag1 ||
           tag_to_hash(info.corpus[
                                    get_tag_index(tag_ind1, info.corpus, 1, false)
                                  ]
                      ) == info.tag1;
}
bool prev_1_or_2_or_3_tag_is(contextual_info_t info){
    int tag_ind1; 
    int tag_ind2;
    return tag_to_hash(info.corpus[
                        (tag_ind1 = get_tag_index(info.tag_index, info.corpus, 1, true))
                                  ]
                      ) == info.tag1 ||
           tag_to_hash(info.corpus[
                        (tag_ind2 = get_tag_index(tag_ind1, info.corpus, 1, true))
                                  ]
                      ) == info.tag1 ||
            tag_to_hash(info.corpus[
                            get_tag_index(tag_ind2, info.corpus, 1, true)
                                   ]
                      ) == info.tag1;
}
bool next_1_or_2_or_3_tag_is(contextual_info_t info){
    int tag_ind1; 
    int tag_ind2;
    return tag_to_hash(info.corpus[
                        (tag_ind1 = get_tag_index(info.tag_index, info.corpus, 1, false))
                                  ]
                      ) == info.tag1 ||
           tag_to_hash(info.corpus[
                        (tag_ind2 = get_tag_index(tag_ind1, info.corpus, 1, false))
                                  ]
                      ) == info.tag1 ||
            tag_to_hash(info.corpus[
                            get_tag_index(tag_ind2, info.corpus, 1, false)
                                   ]
                      ) == info.tag1;
}
bool prev_tag_is_x_and_next_tag_is_y(contextual_info_t info){
    return tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 1, true)]) == info.tag1 &&
           tag_to_hash(info.corpus[get_tag_index(
        info.tag_index, info.corpus, 1, false)]) == info.tag2;
}
bool prev_tag_is_x_and_next_2_tag_is_y(contextual_info_t info){return true;}
bool next_tag_is_x_and_next_2_tag_is_y(contextual_info_t info){return true;}

/* checks if a contextual (known word) 
    rule applies to a given word index */
bool apply_contextual_rule(contextual_rule_t rule, int index, char *corpus){
    contextual_info_t info;
    info.tag1 = rule.arg1;
    info.tag2 = rule.arg2;
    info.tag_index = index;
    info.corpus = corpus;
    return known_word_rules[rule.triggerfn](info);
}