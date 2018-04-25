#ifndef tagger_h
#define tagger_h

bool ignore_tag(int);
int get_ignored_tag(char *);
void apply_initial_tags(corpus_t, struct hashmap);
void apply_initial_tag(char *, struct hashmap, size_t, corpus_t);
void apply_initial_unknown_word_tag(char *, size_t, corpus_t);
void apply_rules_to_corpus(rules_list_t, corpus_t);
void apply_rule_to_corpus(contextual_rule_t, corpus_t);
bool check_contextual_rule(contextual_rule_t, size_t, corpus_t);
//bool store_contextual_info(contextual_info_t *, size_t, corpus_t*);

#endif
