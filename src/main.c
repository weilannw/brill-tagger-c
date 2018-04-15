#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_parser.h"
#define TRAINING_CORPUS_PATH "../corpus/training-corpus.txt"
#define TESTING_CORPUS_PATH "../corpus/testing-corpus.txt"
#define DICT_PATH "../dictionary/dictionary.txt"
#define RULES_LIST_PATH "rules.txt" //must be present in build directory
int main(int argc, char* argv[]){
    /* dictionary with word frequency */
    //map_t dict_hashmap = generate_dictionary(TRAINING_CORPUS_PATH);
    //rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);
   // rules_list_print(rules);
   // rules_list_free(rules);
    //rules_list_print(rules);
    //printMap(dict_hashmap, "s");
    /* clean up */
    //hashmap_free(dict_hashmap);
    //rules_list_free(rules);
    
    map_t map = generate_dictionary("test.txt");
    
   // printMap(map, "James");
    return 1;
}
