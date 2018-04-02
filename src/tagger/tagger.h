#ifndef tagger_h
#define tagger_h
#include "../dictionary/dictionary_generator.h"

void apply_initial_tags(char *, map_t);
void apply_initial_tag(char *, map_t);
void apply_initial_unknown_word_tag(char *);

#endif