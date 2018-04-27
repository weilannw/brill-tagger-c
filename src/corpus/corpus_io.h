#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#ifndef corpus_io_h
#define corpus_io_h
#define MAX_LINE_LENGTH 300 // max line length in mem map
#define TAG_BUFFER_LENGTH 6 // includes max tag length with newline, carriage return omitted by script
#define NTHREADS 1 // to be replaced by omp_get_num_threads

//testing corpus will be used for checking error amount every so often
//training will be used during learning.
/* type passed into contextual rules for checking */
typedef struct word_info_t{
    bool ignore_flag;
    int8_t next_bound;
    int8_t prev_bound;//boundaries of prev and next tags
                     //(based on size of corpus and null tags which break continuity)
}word_info_t;
/* stores list of words and their original tags, and tags from applying rules */
typedef struct corpus_t{
    size_t num_lines;
    char **words; //words are never modified by human or computer
    int *human_tags;  //tags from original human-tagged text (hashed)
    int *machine_tags; // tag hashes applied by the computer--"learned" tags
    word_info_t *info; //stores the boundaries so that prev and next tags can be checked
}corpus_t;
/*section of corpus accessed by individual thread*/
typedef struct subcorpus_t{
    corpus_t corpus;
    size_t index; //each thread gets its index in the corpus_t (indicates starting line)
    size_t num_lines; //length
}subcorpus_t;

/* find end of word in a line (delimited by tab)*/
bool ignore_tag(int);
int word_length(char *);
void parse_corpus(char *, size_t, size_t, corpus_t*);
void print_corpus(corpus_t);
void allocate_corpus(corpus_t*);
void free_corpus(corpus_t);
char * mmap_corpus(size_t, char *);
void parse_line(char *, size_t *, corpus_t*, size_t);
void set_boundaries(size_t, corpus_t *);

/* applies the tag to the place in memory where the tag starts */
//int get_next_tag_hash(size_t *, char *, size_t, bool);
//void store_contextual_info(contextual_info_t *, size_t, char *, size_t);
void apply_tag(int, char *);
char * get_tagged_text(int, int);
#endif
