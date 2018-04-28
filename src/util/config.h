#include <stdbool.h>
#define MAXFNLEN 100
typedef struct config_t{
    int max_line_length;
    int tag_buffer_length;
    char training_corpus_path[MAXFNLEN];
    size_t training_corpus_lines;
    size_t training_corpus_chars;
    char testing_corpus_path[MAXFNLEN];
    size_t testing_corpus_lines;
    size_t testing_corpus_chars;
    char frequency_count_path[MAXFNLEN];
    char input_file_path[MAXFNLEN];
    bool learning_mode;
    int nthreads;
    size_t iterations;
    size_t threshold;
    char rules[MAXFNLEN];
}config_t;
extern config_t config;
void load_configuration(char * fp);
void print_config();