#include "learner/learner.h"
#include "lib/hashmap.h"
#include "dictionary/dictionary_generator.h"
#define TRAINING_CORPUS_PATH "../corpus/training-corpus.txt"
#define TESTING_CORPUS_PATH "../corpus/testing-corpus.txt"
#define DICT_PATH "dictionary/dictionary.txt"
int main(int argc, char* argv[]){
    /* dictionary with word frequency */
    map_t dict_hashmap = generate_dictionary(TRAINING_CORPUS_PATH);
}
