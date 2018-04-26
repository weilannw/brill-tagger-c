#ifndef tagger_h
#define tagger_h

#include "../lib/hashmap.h"

bool ignore_tag(int);
int number_type(char*);
int proper_noun_type(char *, corpus_t, size_t);
int get_ignored_tag(char *);
void apply_initial_tags(corpus_t, hashmap_t);
void apply_initial_tag(char *, hashmap_t, size_t, corpus_t);
void apply_initial_unknown_word_tag(char *, size_t, corpus_t);
void apply_rules_to_corpus(rules_list_t, corpus_t);
void apply_rule_to_corpus(contextual_rule_t, corpus_t);
bool check_contextual_rule(contextual_rule_t, size_t, corpus_t);
//bool store_contextual_info(contextual_info_t *, size_t, corpus_t*);

#endif
