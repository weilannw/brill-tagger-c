#ifndef tagger_h
#define tagger_h
#include "../dictionary/dictionary_generator.h"

void apply_initial_tags(char *, map_t);
void apply_initial_tag(char *, map_t);
void apply_initial_unknown_word_tag(char *);

typedef struct word_tag_pair_t{
    char *line_ptr; // pointer to beginning of line in memory_map
    int tag;
}word_tag_pair_t;


#endif