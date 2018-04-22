#include <stdio.h>
#include "io/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_parser.h"
#define TRAINING_CORPUS_PATH "training-corpus.txt"
#define TESTING_CORPUS_PATH "testing-corpus.txt"
#define RULES_LIST_PATH "rules.txt" //must be present in build directory
int main(int argc, char* argv[]){
    /* dictionary with word frequency */
    //map_t dict_hashmap = generate_dictionary(TRAINING_CORPUS_PATH);
    FILE *corpus_file;
    size_t corpus_length;
    char * corpus_mmap = mmap_plain_text_corpus(&corpus_file, &corpus_length, TESTING_CORPUS_PATH);
    rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
    //current index in corpus
    size_t cur_index = 0;
    //goto_next_tag_index(&cur_index, corpus_mmap, false, corpus_length);
    

   // rules_list_print(rules);
   // rules_list_free(rules);
    //rules_list_print(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);    
   // printMap(map, "James");
    return 1;
}
