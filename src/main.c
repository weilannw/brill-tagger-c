#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_parser.h"
#include "tagger/tags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    char sentence[20];
    char *word1;
    char *word2;
    char *word3;
    char *saveptr;

    map_t map = generate_dictionary("test.txt");
    
    fgets(sentence,20, stdin);
    
    word1 = strtok_r(sentence, " ", &saveptr);
    word2 = strtok_r(NULL, " ", &saveptr);
    word3 = strtok_r(NULL, " ", &saveptr);

    int high1;
    int high2;
    int high3;
    
    hashmap_get(map, word3, (void**)&high3);
    hashmap_get(map, word2, (void**)&high2);
    hashmap_get(map, word1, (void**)&high1);
  //  printf("high1: %d high2: %d high3: %d\n",high1,high2, high3);
    char tag1[5];
    char tag2[5];
    char tag3[5];

  //
    hash_to_tag(high1, tag1);
    hash_to_tag(high2, tag2);
    hash_to_tag(high3, tag3);
    
    printf("%s \\%s\n", word1, tag1);
    printf("%s \\%s\n", word2, tag2);
    printf("%s \\%s\n", word3, tag3);

    return 1;
}










