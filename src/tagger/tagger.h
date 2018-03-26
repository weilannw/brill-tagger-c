#ifndef tagger_h
#define tagger_h

typedef struct word_tag_pair_t{
    char *line_ptr; // pointer to beginning of line in memory_map
    int tag;
}word_tag_pair_t;
#endif