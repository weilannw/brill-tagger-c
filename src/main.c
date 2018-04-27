#include <stdio.h>
#include <unistd.h>
#include "corpus/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_io.h"
#include "tagger/tagger.h"
#include "dictionary/dictionary_reduce.h"
#include "util/dynamic_array.h"
#include "util/config.h"
#define CONF_FILE "config"
#define DEFAULT_LEARNER_ITER 1000
int parse_options (int, char **, bool *, size_t *);

/*int learning (corpus_t corpus){

}
int tagging (corpus_t corpus){
    rules_list_t *rules = parse_rules_from_file(RULES_LIST_PATH);

}*/
int main(int argc, char* argv[]){
    config.threshold = 0; 
    config.iterations = DEFAULT_LEARNER_ITER;
    corpus_t corpus;
    load_configuration(CONF_FILE);
    parse_options(argc, argv, &config.learning_mode, &config.threshold);
    if(config.threshold)
        config.iterations = 0;
    if(config.learning_mode){
        parse_corpus(config.testing_corpus_path, config.testing_corpus_chars, config.testing_corpus_lines, &corpus);
    }
    print_corpus(corpus);
    print_config();
   /* char* file = NULL; 
    bool learning = false;
    int exists = 0;
    if(frequency_map_file_exists()){
        exists = 1;
    }
    parse_options(argc, argv, &learning);
    corpus_t corpus; 
    parse_corpus(TESTING_CORPUS_PATH, TESTING_CORPUS_LENGTH, TESTING_CORPUS_LINES, &corpus);
    hashmap_t dict_hashmap = generate_dictionary(corpus);
    apply_initial_tags(corpus, dict_hashmap);
    if(learning){
        printf("Learning using corpus file %s\n", TRAINING_CORPUS_PATH);
        learning();
    }
    else{
        printf("Applying tagging rules to formatted text file\n");
        tagging();
    }
    for(int i = 0; i < 1000; i++)
        find_best_rule(corpus);
    rules_list_t rules;
    rules.length = learned_rule_index;
    rules.rules = learned_rules;
    print_rules_list(&rules);
    destroy_reduced(dict_hashmap, exists);
    free_corpus(corpus);*/
    return 1;
}

int parse_options (int argc, char **argv, bool * learning, size_t * threshold)
{
  int index;
  int c;
  while ((c = getopt (argc, argv, "lht:")) != -1)
    switch (c)
      {
      case 'l':
        *learning = true;
        break;
      case 'h':
        printf("Help:\n"
        "\t-l: learning mode\n"
        "\t-t: error threshold for completing training\n"
        "\t-h: print help\n");
        exit(EXIT_SUCCESS);
        break;
      case 't':
        *threshold = atoi(optarg);
        if(!(*threshold > 0 && *threshold < 100)){
            printf("Error: learner_threshold must be a valid number > 0 and < 100\n");
            exit(EXIT_FAILURE);
        }
        break;
      case '?':
        printf("Help:\n"
        "\t-l: learning mode\n"
        "\t-t: error threshold for completing training\n"
        "\t-h: print help\n");
        exit(EXIT_FAILURE);
        return 1;
      default:
        abort ();
      }
  return 0;
}






