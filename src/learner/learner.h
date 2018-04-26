#ifndef learner_h
#define learner_h
#include "../lib/hashmap.h"
#include "../util/dynamic_array.h"
#include <stddef.h>
#include "../rules/rules.h"
#include "../io/corpus_io.h"



typedef struct error_t{
    size_t number;
    dynamic_array_t indices;
    int machine_tag; // tag is this
    int human_tag; // should be this
}error_t;
/*errors sorted by their frequency*/
typedef struct sorted_error_list_t{
    size_t length;
    error_t *errors;
}sorted_error_list_t;

typedef struct pattern_t{
    int prevtag3;
    int prevtag2;
    int prevtag1;
    int nexttag1;
    int nexttag2;
    int nexttag3;
}pattern_t;

/* 
 first find error,
 find most frequent pattern
 find most frequent rule

 if next greatest number of errors is less 
 than most frequent pattern minus the number of 
 non-error words of same tag and pattern, stop looking
 and add to list of learned rules 
*/
int cmpfunc (const void *, const void *);

int find_most_frequent(int*, size_t);
int get_rule_error_improvement(corpus_t, contextual_rule_t, error_t);
sorted_error_list_t* error_frequencies(corpus_t);

sorted_error_list_t* errors_sorted_by_frequency(hashmap_t);
pattern_t find_patterns(corpus_t corpus, error_t error);
void find_best_rule(corpus_t corpus);
void add_rule(contextual_rule_t *rule);
void learner_init();
#endif
