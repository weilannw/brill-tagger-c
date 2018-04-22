#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#ifndef corpus_io_h
#define corpus_io_h
#define NUM_LINES 1000
#define LINE_MAX_LENGTH 100 // max line length in mem map
#define TAG_BUFFER_LENGTH 6 // includes max tag length with newline, carriage return omitted by script
#define NTHREADS 1 // to be replaced by omp_get_num_threads

//testing corpus will be used for checking error amount every so often
//training will be used during learning.
//stores list of words, and 
typedef struct corpus_map_t{
    size_t index; //each thread/process gets its index in the array
    char *words;
    int *tags;
    int *evolving_tags;
}corpus_map_t;

corpus_map_t *subcorpora;

/* find end of word in a line (delimited by tab)*/
int word_length(char *);
bool goto_prev_tag_index(size_t *, char *);
bool goto_next_tag_index(size_t *, char *, size_t);
char * mmap_plain_text_corpus(FILE **, size_t *, char *);
/* applies the tag to the place in memory where the tag starts */
void apply_tag(int, char *);
char * get_tagged_text(int, int);
#endif