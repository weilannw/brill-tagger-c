#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../corpus/corpus_io.h"
#include "../rules/rules.h"
#include "../tagger/tagger.h"
#include "../tagger/tags.h"
#include "accuracy_check.h"

//rules_list_t should include the number of rules since the last rule check,
// testing corpus is passed in. 
float accuracy(corpus_t corpus){    
    float accuracy = 0.0;
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.human_tags[i] == corpus.machine_tags[i])
            accuracy++;
    }
    accuracy = (accuracy/corpus.num_lines)*100;
    return accuracy;
}
