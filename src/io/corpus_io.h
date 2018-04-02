#include <stdbool.h>
#ifndef corpus_io_h
#define corpus_io_h
#define LINE_MAX_LENGTH 100 // max line length in mem map
#define TAG_BUFFER_LENGTH 6

/* find end of word in a line (delimited by tab)*/
int word_length(char *);
int get_tag_hash(int, char *, int, bool);
int get_tag_index(int, char *, int, bool);

/* applies the tag to the place in memory where the tag starts */
void apply_tag(int, char *);
char * get_tagged_text(int, int);
#endif