#ifndef tagger_h
#define tagger_h

typedef struct word_tag_pair_t{
    int word_id; // index of the word in the corpus
    int tag;
}word_tag_pair_t;

int apply_tag(int, int);
char * output_tagged_text(int, int);
#endif