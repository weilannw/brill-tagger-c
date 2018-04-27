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

    //free_dynamic_array(d)
    int exists = 0;
    FILE* file;
    file = fopen("frequencies.txt", "r");
    if(file){ exists = 1; fclose(file);}
    fclose(file);  
    corpus_t corpus;
    parse_corpus(TESTING_CORPUS_PATH, TESTING_CORPUS_LENGTH, TESTING_CORPUS_LINES, &corpus);
    //rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
    hashmap_t dict_hashmap = generate_dictionary(corpus);
    apply_initial_tags(corpus, dict_hashmap);
    for(int i = 0; i < 1000; i++)
        find_best_rule(corpus);
    rules_list_t rules;
    rules.length = learned_rule_index;
    rules.rules = learned_rules;
    print_rules_list(&rules);
    hashmap_destroy(&dict_hashmap);
    free_corpus(corpus);

    
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

    //subcorpus_t sub;*/
    //sub.corpus = corpus;
    //sub.index = 0;
    //sub.num_lines = TESTING_CORPUS_LINES;
    //for(size_t i = 0; i < corpus.num_lines; i++)
        //printf("AppliedTags[%lu], %d\n", i, corpus.applied_tags[i]);

   /// print_corpus(corpus);

    //print_rules_list(rules);
    //free_rules_list(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);    
   // printMap(map, "James");
    return 1;
}










