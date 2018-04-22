#include <stdio.h>
#include "io/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_parser.h"
#define TRAINING_CORPUS_PATH "training-corpus.txt"
#define TESTING_CORPUS_LENGTH //hardcode this using wc -c on a file -- mine is (14938398)
#define TESTING_CORPUS_LINES //use wc -l (1302584)
#define TESTING_CORPUS_PATH "testing-corpus.txt"
#define RULES_LIST_PATH "rules.txt" //must be present in build directory
int main(int argc, char* argv[]){
    //map_t dict_hashmap = generate_dictionary(TRAINING_CORPUS_PATH);
    size_t corpus_length;
    corpus_t corpus;
    parse_corpus(TESTING_CORPUS_PATH, TESTING_CORPUS_LENGTH, TESTING_CORPUS_LINES, &corpus);
    rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
    subcorpus_t sub;
    sub.corpus = corpus;
    sub.index = 0;
    sub.num_lines = TESTING_CORPUS_LINES;

    print_corpus(corpus);
    free_corpus(corpus);

    print_rules_list(rules);
    free_rules_list(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);    
   // printMap(map, "James");
    return 1;
}










