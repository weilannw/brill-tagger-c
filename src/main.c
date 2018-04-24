#include <stdio.h>
#include "io/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_parser.h"
#include "tagger/tagger.h"
#define TRAINING_CORPUS_PATH "training-corpus.txt"
#define TESTING_CORPUS_LENGTH 14938398
#define TESTING_CORPUS_LINES 1302584
#define TESTING_CORPUS_PATH "testing-corpus.txt"
#define RULES_LIST_PATH "rules.txt" //must be present in build directory
int main(int argc, char* argv[]){    
    corpus_t corpus;
    parse_corpus(TESTING_CORPUS_PATH, TESTING_CORPUS_LENGTH, TESTING_CORPUS_LINES, &corpus);
    //rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
    //apply_initial_tags(corpus, dict_hashmap);
    //struct hashmap dict_hashmap = generate_dictionary(corpus);
    //hashmap_destroy(&dict_hashmap);
    //subcorpus_t sub;
    //sub.corpus = corpus;
    //sub.index = 0;
    //sub.num_lines = TESTING_CORPUS_LINES;
    //for(size_t i = 0; i < corpus.num_lines; i++)
        //printf("AppliedTags[%lu], %d\n", i, corpus.applied_tags[i]);

 //   print_corpus(corpus);
 //   free_corpus(corpus);

    //print_rules_list(rules);
    //free_rules_list(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);    
   // printMap(map, "James");
    return 1;
}










