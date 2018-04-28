//#ifdef _OPENMP
#include <omp.h>
//#endif
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "corpus/corpus_io.h"
#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#include "rules/rule_io.h"
#include "tagger/tagger.h"
#include "dictionary/dictionary_reduce.h"
#include "util/dynamic_array.h"
#include "util/config.h"
#include "util/fileio.h"
#include "accuracy/accuracy_check.h"
#define CONF_FILE "config"
#define DEFAULT_LEARNER_ITER 1000
#define OMP_NUM_THREADS 4
int parse_options (int, char **, bool *, size_t *, int*);
void prompt_for_print(corpus_t corpus){
    char scan;
    printf("Print corpus?(Y/N):");
    scanf("%c", &scan);
    if(scan=='y' || scan=='Y')
        print_corpus(corpus);
}
int main(int argc, char* argv[]){
    config.threshold = 0; 
    config.iterations = DEFAULT_LEARNER_ITER;
    bool learning_mode = false;
    size_t threshold = 0;
    int threads = 0;
    int exists = 0;
    hashmap_t hashmap;
    corpus_t corpus;
    parse_options(argc, argv, &learning_mode, &threshold, &threads);
    load_configuration(CONF_FILE);
    config.learning_mode = learning_mode;
    config.threshold = threshold;
    config.nthreads = threads;
    #ifdef _OPENMP
        omp_set_dynamic(0);     // Explicitly disable dynamic teams
        omp_set_num_threads(config.nthreads); 
    #endif
    if(file_exists(config.frequency_count_path))
        exists = 1;
    print_config();
    if(config.threshold)
        config.iterations = 0;
    if(config.learning_mode){
        parse_corpus(config.testing_corpus_path, config.testing_corpus_chars, config.testing_corpus_lines, &corpus);
        hashmap = generate_dictionary(corpus);
        apply_initial_tags(corpus, hashmap);
    }
    else if(!exists){
        printf("Error: your '%s' file must be generated "
               "in learning mode before running tagging mode.\n",
                config.frequency_count_path);
        exit(EXIT_FAILURE);
    }
    else{// tagging mode -- no machine learning
        /*if we had more time, this would use the input file and its length and line number */
        rules_list_t *rules = parse_rules_from_file(config.rules);
        //mprintf("l\n");
        parse_corpus(config.testing_corpus_path, config.testing_corpus_chars, config.testing_corpus_lines, &corpus);
        apply_rules_to_corpus(*rules, corpus);
        hashmap = generate_dictionary(corpus);
    }
    destroy_reduced(hashmap, exists);
    printf("Final accuracy %.2f%%\n", accuracy(corpus));
    prompt_for_print(corpus);
    return 1;
}

int parse_options (int argc, char **argv, bool * learning, size_t * threshold, int *threads)
{
  int index;
  int c;
  while ((c = getopt (argc, argv, "lht:p:")) != -1)
    switch (c)
      {
      case 'l':
        *learning = true;
        break;
      case 'h':
        printf("Help:\n"
        "\t-l: learning mode\n"
        "\t-t: <threshold> error threshold for completing training\n"
        "\t-h: print help\n");
        exit(EXIT_SUCCESS);
        break;
      case 'p':
        *threshold = atoi(optarg);
        if(!(*threshold > 0 && *threshold < 100)){
            printf("Error: threshold '%s' must be a valid number > 0 and < 100\n", optarg);
            exit(EXIT_FAILURE);
        }
        break;
      case 't':
        *threads = atoi(optarg);
        if(!*threads){
            printf("Error: threads '%s' must be a valid number > 0\n", optarg);
            exit(EXIT_FAILURE);
        }
        break;
      case '?':
        printf("Help:\n"
        "\t-l: learning mode\n"
        "\t-t: <threshold> error threshold for completing training\n"
        "\t-h: print help\n");
        exit(EXIT_FAILURE);
        return 1;
      default:
        abort ();
      }
  return 0;
}






