#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include "corpus_io.h"
#include "../tagger/tags.h"
 // todo: create memory maps of the corpus
// list of offsets
// each thread/ proc num gets an offset
// each thread gets a memory map
/* get index of tag in corpus + or - 1 line. result is stored in 
the current index pointer */
/*char *allocate_subcorpora(char *mem_map, size_t size, size_t nthreads){

}
bool error_check(corpus_map_t map, size_t index){
    return map()
}
char *create_corpus_mmap(char *tagged_corpusfn, char *evolving_corpusfn, off_t offset, size_t size, ){
}*/
/* create memory maps divided based on number of threads */
/*void create_mem_maps(){
    return 0;
}
void munmap_corpus_map(corpus_map_t *map){
    munmap()
}
//offset is in terms of line number
//memory mapping for vastly improved machine learning performance 
corpus_map_t *create_corpus_map(size_t index, size_t lines, size_t chars, off_t offset, FILE *words, FILE *tags, FILE *evolving_tags){
    corpus_map_t *corpus_map = (*corpus_map_t)malloc(sizeof(corpus_map_t));
    corpus_map->index=index;
    if((corpus_map->tags = (int*)mmap((void*)(corpus_map->tags), lines * sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, tags, offset * sizeof(int))) == MAP_FAILED){
        printf("Failed to map tags file at index %d\n", index);
        exit(0);
    }
    if((corpus_map->evolving_tags = (int*)mmap((void*)(corpus_map->evolving_tags), lines * sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, evolving_tags, offset * sizeof(int))) == MAP_FAILED){
        printf("Failed to map evolving_tags file at index %d\n", index);
        exit(0);
    }
    if((corpus_map->words = (char*)mmap((void*)(corpus_map->words), lines * LINE_BUFFER_LENGTH, PROT_READ|PROT_WRITE, MAP_SHARED, words, offset * LINE_BUFFER_LENGTH)) == MAP_FAILED){
        printf("Failed to map words file at index %d\n", index);
        exit(0);
    }
    return corpus_map;
}
FILE *create_file(char *filename, size_t length){
    FILE *file = fopen(filename, "w+");
    if(!file)
        exit(0);
    fseek(file, length, SEEK_SET);
    fputc('\0', file);
    return file;
}*/
static void getfileinfo(FILE *file, size_t *numlines, size_t *numchars){
    char cur;
    *numlines = 0;
    *numchars = 0;
    while((cur = getc(file))!=EOF){
        *numchars+=1;
        if(cur == '\n')
            *numlines+=1;
    }
    fseek(file, 0, SEEK_SET);
}







/* memory maps the corpus in plain text. 
   gives the file for closing later, and the number of bytes in the file */
char * mmap_plain_text_corpus(FILE **fileptr, size_t *numbytes, char *filename){
    size_t numlines = 0;
    size_t numchars = 0;
    char *mem_map;
    FILE *corpus = fopen(filename, "r+");
    *fileptr = corpus;
    if(!corpus){
        printf("Failed to open plaintext corpus file\n");
        exit(0);
    }
    getfileinfo(corpus, &numlines, &numchars);
    *numbytes = numchars;
    if((mem_map = (char*)mmap((void*)(mem_map), numchars, PROT_READ|PROT_WRITE, MAP_SHARED, fileno(corpus), 0)) == MAP_FAILED){
        printf("Failed to map plaintext corpus file\n");
        exit(0);
    }
    return mem_map;
}
//start index of previous tag 
//corpus_size is the number of bytes
//return true for out of bounds
bool goto_prev_tag_index(size_t *cur_index, char *corpus){
    while((int)*cur_index-TAG_BUFFER_LENGTH-1 >= 0){
        if(corpus[*cur_index]=='\t'){
            *cur_index-=TAG_BUFFER_LENGTH+1;
            return false;
        }
        *cur_index-=1;
    }
    return true;
}  
//start index of next tag
//corpus_size is the number of bytes
//return true for out of bounds
bool goto_next_tag_index(size_t *cur_index, char *corpus, size_t corpus_size){
    while(*cur_index<(int)corpus_size-1-TAG_BUFFER_LENGTH){
        if(corpus[*cur_index]=='\t'){
            *cur_index+=1;
            return false;
        }
        *cur_index+=1;
    }
    return true;
}  
/* tag points to the start of the tag buffer in the corpus mmap */
void apply_tag(int tag_hash, char * tag){
    /* this will insert the tag string in the specified location */
    hash_to_tag(tag_hash, tag);
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