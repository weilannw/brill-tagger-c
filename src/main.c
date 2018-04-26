#include <stdio.h>
#include "io/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "io/rule_io.h"
#include "tagger/tagger.h"
#include "dictionary/dictionary_reduce.h"
#include "util/dynamic_array.h"
#define TRAINING_CORPUS_PATH "training-corpus.txt"
#define TESTING_CORPUS_LENGTH 226
#define TESTING_CORPUS_LINES 20
#define TESTING_CORPUS_PATH "testing-corpus.txt"
#define RULES_LIST_PATH "rules.txt" //must be present in build directory
int main(int argc, char* argv[]){ 
/*void initialize_dynamic_array(dynamic_array_t *array, size_t initial_length, uint8_t size_of){
    array->current_length = initial_length;
    array->elems = malloc(sizeof(size_of)*initial_length);
    array->size_of_elem = size_of;
    array->current_index = 0;
}
void add_to_dynamic_array(dynamic_array_t *array, void *any_type){
    if(sizeof(any_type) != array->size_of_elem){
        printf("Error: item being added to dynamic array is of incorrect size\n");
        exit(EXIT_FAILURE);
    }
    array->current_index+=1;
    if(array->current_index >= array->current_length)
        grow_dynamic_array(array);
    array->elems[array->current_index-1] = any_type;
}
static void grow_dynamic_array(dynamic_array_t *array){
    array->current_length *= 2;
    array->elems = realloc(array->elems, array->size_of_elem * array->current_length);
}*/
    dynamic_array_t errors;
    error_t error;
    initialize_dynamic_array(&errors, 1, sizeof(error_t*));
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);
    add_to_dynamic_array(&errors, &error);

    print_dynamic_array(&errors);
    free_dynamic_array(&errors);
    //free_dynamic_array(d)
    //int exists = 0;
    //FILE* file;
    //file = fopen("frequencies.txt", "r");
    //if(file){ exists = 1; fclose(file);}
    //fclose(file);  
    //todo: change delim from comma to something else in rule parser 
    //corpus_t corpus;
    //parse_corpus(TESTING_CORPUS_PATH, TESTING_CORPUS_LENGTH, TESTING_CORPUS_LINES, &corpus);
    //rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
    //hashmap_t dict_hashmap = generate_dictionary(corpus);
    
//    int* num = (int *)hashmap_get(&dict_hashmap, "rupee");

//    printf("Here is the value for rupee: %d", *num);
   // FILE* fp = fopen("frequencies.txt", "r");
    //if(*fp == NULL){
   //	FILE* file;
    /*if (exists == 1) { 
//	fclose(file);
//	printf("FILE EXISTS\n\n\n");     
        destroy_reduced(dict_hashmap, 1);
   	//fclose(file);
    }
    else{
//	fclose(file);
        destroy_reduced(dict_hashmap, 0);
	
    }
   // hashmap_destroy(&dict_hashmap);

    //subcorpus_t sub;*/
    //sub.corpus = corpus;
    //sub.index = 0;
    //sub.num_lines = TESTING_CORPUS_LINES;
    //for(size_t i = 0; i < corpus.num_lines; i++)
        //printf("AppliedTags[%lu], %d\n", i, corpus.applied_tags[i]);

   /// print_corpus(corpus);
   // free_corpus(corpus);

    //print_rules_list(rules);
   // free_rules_list(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);    
   // printMap(map, "James");
    return 1;
}










