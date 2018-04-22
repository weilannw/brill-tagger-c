#ifndef tagger_h
#define tagger_h

void apply_initial_tags(char *, map_t);
void apply_initial_tag(char *, map_t);
void apply_initial_unknown_word_tag(char *);
void apply_rule_to_corpus(contextual_rule_t, char *, size_t);
bool store_contextual_info(contextual_info_t *, size_t, corpus_t*);

#endif