#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "corpus_io.h"
#include "../tagger/tags.h"

// output number of lines and populated corpus_t, returns false on failure
void parse_corpus(char *filename, size_t num_bytes, size_t num_lines, corpus_t *corpus){
    corpus->num_lines = num_lines;
    allocate_corpus(corpus, num_lines);
    char *corpus_text = mmap_corpus(num_bytes, filename);
    size_t byte_index = 0;
    size_t linenum = 0;
    while(linenum < num_lines && byte_index < num_bytes){
        parse_line(&corpus_text[byte_index], &byte_index, corpus, linenum);
        linenum++;
    }
    munmap(corpus_text, num_bytes);
}
//todo: add tag error checking
//returns the end index of the line
void parse_line(char *line, size_t *offset, corpus_t *corpus, size_t index){
    int word_len = word_length(line);
    if(word_len == -1){
        printf("Error: Word length is greater than maximum\n");
        exit(0);
    }
    corpus->words[index] = (char*)malloc(sizeof(char)*word_len);
    corpus->words[index][word_len]='\0';
    strncpy(corpus->words[index], line, word_len);
    *offset += word_len + TAG_BUFFER_LENGTH + 1; //points to beginning of next line
    corpus->tags[index] = tag_to_hash(&line[word_len+1]);
}
void print_corpus(corpus_t corpus){
    char tag_buffer[TAG_BUFFER_LENGTH];
    char applied_tag_buffer[TAG_BUFFER_LENGTH];
    for(int i = 0; i < corpus.num_lines; i++){
        hash_to_tag(corpus.tags[i], tag_buffer);
        if(!*tag_buffer)
            strcpy(tag_buffer, "none");
        hash_to_tag(corpus.applied_tags[i], applied_tag_buffer);
        if(!*applied_tag_buffer) 
            strcpy(applied_tag_buffer, "none");
        printf("------Corpus line %d------\n"
               "Word:             %s\n"
               "Tag:              %s\n"
               "                  %d\n"
               "Learned Tag:      %s\n"
               "                  %d\n", 
               i, corpus.words[i], tag_buffer, corpus.tags[i], applied_tag_buffer, corpus.applied_tags[i]);
    }
}
void allocate_corpus(corpus_t *corpus, size_t num_lines){
    corpus->words = (char**)malloc(sizeof(char*)*num_lines);
    corpus->tags = (int*)malloc(sizeof(int)*num_lines);
    corpus->applied_tags = (int*)malloc(sizeof(int)*num_lines);
}
void free_corpus(corpus_t corpus){
    for(int i = 0; i < corpus.num_lines; i++){
        free(corpus.words[i]);
        corpus.words[i]=NULL;
    }
    free(corpus.words);
    corpus.words=NULL;
    free(corpus.tags);
    corpus.tags=NULL;
    free(corpus.applied_tags);
    corpus.applied_tags=NULL;
}
/*returns bool indicating if contextual info was stored
  this method allows for checking contextual rules,
  nulls break continuity so bounds are set at the beginning/end 
  of the corpus and at a null.*/
bool store_contextual_info(contextual_info_t *info, size_t index, corpus_t *corpus){
    if(corpus->applied_tags[index] == NUL)
        return false;
    info->corpus = corpus;
    info->index = index;
    int lowerbound = -3;
    int upperbound = 3;
    int diff;
    if(index < 3)
        lowerbound = -index;
    else if ((diff = corpus->num_lines-1-index) < 3)
        upperbound = diff;
    for(int i = -1; i >= lowerbound; i--)
        if(corpus->applied_tags[index+i] == NUL){
            lowerbound = i;
            break;
        }
    for(int i = 1; i <= upperbound; i++)
        if(corpus->applied_tags[index+i] == NUL){
            upperbound = i;
            break;
        }
    info->prev_bound = lowerbound;
    info->next_bound = upperbound;
    return true;
}
/* memory maps the corpus in plain text. 
   gives the file for closing later, and the number of bytes in the file */
char * mmap_corpus(size_t numchars, char *filename){
    char *mem_map;
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
        printf("Failed to open corpus file\n");
        exit(0);
    }
    if((mem_map = (char*)mmap(NULL, numchars, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED){
        printf("Failed to map corpus file\n");
        exit(0);
    }
    return mem_map;
}

char * get_tagged_text(int tag, int index){
    return NULL;
}
//char * get_next_line(int index)
int word_length(char * line){
    int i = 0;
    while (line[i] != '\t'){
        if(i > LINE_MAX_LENGTH) 
            return -1; // error (avoids long looping for invalid file)
        i++;
    }
    return i;
}