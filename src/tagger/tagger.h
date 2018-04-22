#ifndef tagger_h
#define tagger_h

void apply_initial_tags(corpus_t corpus, map_t);
void apply_initial_tag(char *word, map_t hash_map, int a, corpus_t corpus);
void apply_initial_unknown_word_tag(char *word, int a, corpus_t corpus);
void apply_rule_to_corpus(contextual_rule_t, char *, size_t);
bool store_contextual_info(contextual_info_t *, size_t, corpus_t*);

#endif
