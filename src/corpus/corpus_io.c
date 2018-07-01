#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "corpus_io.h"
#include "../tagger/tags.h"
// tags with these types are never altered.
void fix_newline(char*);
bool ignore_tag(int hash){
    //should be slightly faster than if statement
    switch(hash){
        case COL:
            return true;
        case SCOL:
            return true;           
        case LPAR:
            return true;            
        case RPAR:
            return true;     
        case DQ:
            return true;       
        case PER:
            return true;            
        case COM:
            return true;            
        case QUE:
            return true; 
        case EXC:
            return true;           
        case ZZ:
            return true;
        case NUL:
            return true;
        default:
            return false;
    }
}
/*void create_corpora(char *filename, ){

}*/
// output number of lines and populated corpus_t, returns false on failure
void parse_corpus(char *filename, size_t num_bytes, size_t num_lines, corpus_t *corpus){
    corpus->num_lines = num_lines;
    allocate_corpus(corpus);
    char *corpus_text = mmap_corpus(num_bytes, filename);
    size_t byte_index = 0;
    size_t linenum = 0;
    while(linenum < num_lines && byte_index < num_bytes){
        parse_line(&corpus_text[byte_index], &byte_index, corpus, linenum);
        linenum++;
    }
    int testing = 0;
    for(size_t linenum = 0; linenum < num_lines; linenum++){
        if(ignore_tag(corpus->human_tags[linenum])){
//            if(testing < 50){testing++; printf("Should be ignoring tag: %s at index: %zu\n", corpus->words[linenum], linenum);}
            corpus->info[linenum].ignore_flag = true;
            corpus->info[linenum].next_bound = 0;
            corpus->info[linenum].prev_bound = 0;
        }
        else{
            corpus->machine_tags[linenum] = 0; //no tag -- maps to nothing
            set_boundaries(linenum, corpus);
        }
    }
    munmap(corpus_text, num_bytes);
}
//todo: add tag error checking
//returns the end index of the line
void parse_line(char *line, size_t *offset, corpus_t *corpus, size_t index){
    
    int word_len = word_length(line);
    //if(index%1000 == 0) printf("currently trying to parse %s\n", line);
    if(word_len == -1){
        printf("Error: Word length is greater than maximum\n");
        exit(0);
    }
    char one_per[2];
    one_per[0] = line[2];
    one_per[1] = '\0';
    //if(index == 20942) printf("value of line2 vs one_per: %c vs %s\n", line[2], one_per);   
    int one_hash = tag_to_hash(one_per);
    if(ignore_tag(one_hash)){
//	   printf("Here is the char being saved: %c\n", line[2]);
           corpus->words[index] = (char*)malloc(sizeof(char)*2);
	   corpus->words[index][1]='\0';
	   corpus->words[index][0] = line[2];
    }
    else{
    corpus->words[index] = (char*)malloc(sizeof(char)*word_len);
    corpus->words[index][word_len-1]='\0';
//    fix_newline(line);
    int len = -1;
    
    strncpy(corpus->words[index], line, word_len-1);
    //if(corpus->words[index][0]=='\n') corpus->words[index][0]='\0';//printf("newline was found\n"); //corpus->words[index][0] = '\0';
    //if(corpus->words[index][0] == '\n'){corpus->words[index][0] = corpus->words[index][1]; corpus->words[index][1] = '\0';}    
    }
    corpus->words[index][strcspn(corpus->words[index], "\n")] = '\0';
    //if(len != -1){ printf("Line %s has newline at: %d\n", corpus->words[index], len);}
    *offset+=word_len-1+TAG_BUFFER_LENGTH+1; //points to beginning of next line
    //int f = -1;
    //f = tag_to_hash(&line[word_len]);
    //if(f == -1) printf("currently trying to parse%s\n", line);
    if(!(&line[word_len])){ printf("word that is wrong: %s\n", &line[word_len]);}
    corpus->human_tags[index] = tag_to_hash(&line[word_len]);
    //}
}
void print_corpus(corpus_t corpus){
    char tag_buffer[TAG_BUFFER_LENGTH];
    char applied_tag_buffer[TAG_BUFFER_LENGTH];
    for(int i = 0; i < corpus.num_lines; i++){
        hash_to_tag(corpus.human_tags[i], tag_buffer);
        //if(!*tag_buffer)
          //  strcpy(tag_buffer, "none");
        hash_to_tag(corpus.machine_tags[i], applied_tag_buffer);
        //if(!*applied_tag_buffer) 
          //  strcpy(applied_tag_buffer, "none");
        printf("------Corpus line %d------\n"
               "Word:             %s\n"
               "Tag:              %s\n"
               "                  %d\n"
               "Learned Tag:      %s\n"
               "                  %d\n"
               "Prev Bound:       %d\n"
               "Next Bound:       %d\n" 
               "Ignore Flag:      %s\n",
               i, 
               corpus.words[i],
               tag_buffer, 
               corpus.human_tags[i], 
               applied_tag_buffer, 
               corpus.machine_tags[i],
               corpus.info[i].prev_bound,
               corpus.info[i].next_bound,
               (corpus.info[i].ignore_flag?"true":"false")
               );
    }
}
void allocate_corpus(corpus_t *corpus){
    corpus->words = (char**)malloc(sizeof(char*)*corpus->num_lines);
    memset(corpus->words, 0, sizeof(char*)*corpus->num_lines);
    corpus->human_tags = (int*)malloc(sizeof(int)*corpus->num_lines);
    memset(corpus->human_tags, 0, sizeof(int)*corpus->num_lines);
    corpus->machine_tags = (int*)malloc(sizeof(int)*corpus->num_lines);
    memset(corpus->machine_tags, 0, sizeof(int)*corpus->num_lines);
    corpus->info = (word_info_t*)malloc(sizeof(word_info_t)*corpus->num_lines);
    memset(corpus->info, 0, sizeof(word_info_t)*corpus->num_lines);
}
void free_corpus(corpus_t corpus){
    for(int i = 0; i < corpus.num_lines; i++){
        free(corpus.words[i]);
        corpus.words[i]=NULL;
    }
    free(corpus.words);
    corpus.words=NULL;
    free(corpus.human_tags);
    corpus.human_tags=NULL;
    free(corpus.machine_tags);
    corpus.machine_tags=NULL;
    free(corpus.info);
}
 /* this method allows for checking contextual rules,
  nulls break continuity so bounds are set at the beginning/end 
  of the corpus and at a null.*/
void set_boundaries(size_t index, corpus_t *corpus){
    int8_t lowerbound = -3;
    int8_t upperbound = 3;
    size_t diff;
    if(index < 3)
        lowerbound = -index;
    if ((diff = corpus->num_lines-1-index) < 3)
        upperbound = diff;
    for(int8_t i = -1; i >= lowerbound; i--){
        if(corpus->human_tags[index+i] == NUL){
            lowerbound = i+1;
            break;
        }
    }
    for(int8_t i = 1; i <= upperbound; i++){
        if(corpus->human_tags[index+i] == NUL){
            upperbound = i-1;
            break;
        }
    }
    corpus->info[index].next_bound = upperbound;
    corpus->info[index].prev_bound = lowerbound;
}
/* memory maps the corpus in plain text. 
   gives the file for closing later, and the number of bytes in the file */
char * mmap_corpus(size_t numchars, char *filename){
    char *mem_map;
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
        printf("Failed to open corpus file \"%s\"\n", filename);
        exit(0);
    }
    if((mem_map = (char*)mmap(NULL, numchars, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED){
        printf("Failed to map corpus file \"%s\"\n", filename);
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
    while (line[i] != '\t' && line[i] != '\0'){
        if(i > LINE_MAX_LENGTH) 
            return -1; // error (avoids long looping for invalid file)
        i++;
    }
    return i+1; //includes null byte
}
void fix_newline(char* line){
    int size = word_length(line);
    int move = 0;
    for(int i = 0; i < size; i++){
        if(line[i] == '\n' || line[i]== ' ') move++;
    }
    int stop = strlen(line);
    for(int j = 0; j < size; j++){
        if(j == stop) break;
        line[j] = line[move+j];
    }

    for(int x = size-move; x < size; x++){
    line[x] = '\0';
    }
}
