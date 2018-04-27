#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include "../util/fileio.h"
#include "../util/config.h"
config_t config;
char *options[14] = {
    "max_line_length",
    "tag_buffer_length",
    "training_corpus_path",
    "training_corpus_lines",
    "training_corpus_chars",
    "testing_corpus_path",
    "testing_corpus_lines",
    "testing_corpus_chars",
    "frequency_count_path",
    "input_file_path",
    "learning_mode", //1 or 0, 0 indicates tagging mode
    "nthreads", // 1 for serial
    "iterations",
    "threshold"
};
static int option_number(char * option){
   // printf("%s\n", option);
    if(!option || !*option)
        return -1;
    for(int i = 0; i < sizeof(options); i++){
        if(strcmp(option, options[i]) == 0){
            return i;
            break;
        }
    }
    return -1;
}
static void parse_option(char * line, config_t * config){
    char *saveptr;
    char * option = strtok_r(line, "\":=\t", &saveptr);
    char * optarg = strtok_r(NULL, "\":=\t", &saveptr);
    switch(option_number(option)){
        case 0:
            config->max_line_length = atoi(optarg);
            if(!config->max_line_length){
                printf("Error: max_line_length must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 1:
            config->tag_buffer_length = atoi(optarg);
            if(!config->tag_buffer_length){
                printf("Error: tag_buffer_length must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 2:
            strcpy(config->training_corpus_path, optarg);
            if(!file_exists(optarg)){
                printf("Error: Corpus path '%s' must be relative to directory of the executable.\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;
        case 3:
            config->training_corpus_lines = atoi(optarg);
            if(!config->training_corpus_lines){
                printf("Error: training_corpus_lines must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 4:
            config->training_corpus_chars = atoi(optarg);
            if(!config->training_corpus_chars){
                printf("Error: training_corpus_chars must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 5:
            strcpy(config->testing_corpus_path, optarg);
            if(!file_exists(optarg)){
                printf("Error: Corpus path '%s' must be relative to directory of the executable.\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;
        case 6:
            config->testing_corpus_lines = atoi(optarg);
            if(!config->testing_corpus_lines){
                printf("Error: testing_corpus_lines must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 7:
            config->testing_corpus_chars = atoi(optarg);
            if(!config->testing_corpus_chars){
                printf("Error: testing_corpus_chars must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 8:
            strcpy(config->frequency_count_path, optarg);
            break;
        case 9:
            strcpy(config->input_file_path, optarg);
            if(!config->learning_mode && !file_exists(optarg)){
                printf("Error: Plaintext path '%s' must be relative to directory of the executable.\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;            
        case 10:
            config->learning_mode = (strcmp(optarg, "true") == 0 || atoi(optarg));
            break;
        case 11:
            config->nthreads = atoi(optarg);
            if(!config->testing_corpus_lines){
                printf("Error: nthreads must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 12:
            config->iterations = atoi(optarg);
            if(!config->iterations){
                printf("Error: iterations must be a valid number > 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 13:
            config->threshold = atoi(optarg);
            if(!config->threshold || config->threshold >= 100){
                printf("Error: threshold '%lu' must be a valid number > 0 and < 100\n", config->threshold);
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Error: config option '%s' is not a valid option.\n", optarg);
            exit(EXIT_FAILURE);
    }
}  
void load_configuration(char * fp){
    FILE * file = fopen(fp, "r");
    if(file == NULL){
        printf("Could not open config file '%s' (errno %d)\n", fp, errno);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("Reading config file '%s'\n", fp);
    ssize_t read;
    size_t numlines = 0;
    size_t numchars = 0;
    getfileinfo(file, &numlines, &numchars);
    char contents[numchars];
    int cur = 0;
    fread(contents, numchars, 1, file);
    char *line;
    char *saveptr;
    for(int i = 0; i < numlines; i++){
        if(i == 0)
            line = strtok_r(contents, "\r\n", &saveptr);
        else 
            line = strtok_r(NULL, "\r\n", &saveptr);
        parse_option(line, &config);
    }
    fclose(file);
}
void print_config(){
    if(config.learning_mode){
        printf("----Learning Mode----\n"
               "    max_line_length:       %d\n"
               "    tag_buffer_length:     %d\n"
               "    training_corpus_path:  %s\n"
               "    training_corpus_lines: %lu\n"
               "    training_corpus_chars: %lu\n"
               "    testing_corpus_path:   %s\n"
               "    testing_corpus_lines:  %lu\n"
               "    testing_corpus_chars:  %lu\n"
               "    frequency_count_path:  %s\n"
               "    nthreads:              %d\n"
               "    iterations:            %lu\n"
               "    threshold:             %lu\n",
            config.max_line_length,
            config.tag_buffer_length,
            config.training_corpus_path,
            config.training_corpus_lines,
            config.training_corpus_chars,
            config.testing_corpus_path,
            config.testing_corpus_lines,
            config.testing_corpus_chars,
            config.frequency_count_path,
            config.nthreads,
            config.iterations,
            config.threshold);
    }
    else{
        printf("----Tagging Mode----\n"
               "    max_line_length:       %d\n"
               "    tag_buffer_length:     %d\n"
               "    frequency_count_path:  %s\n"
               "    input_file_path:       %s\n",
            config.max_line_length,
            config.tag_buffer_length,
            config.frequency_count_path,
            config.input_file_path);
    }
    
}