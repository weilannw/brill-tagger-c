#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../io/corpus_io.h"
#include "../rules/rules.h"
#include "../tagger/tagger.h"
#include "../tagger/tags.h"
#include "accuracy_check.h"


float accuracy(rules_list_t rules, corpus_t corpus){
    apply_rules_to_corpus(rules, corpus);
    
    float average = 0.0;
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.human_tags[i] == corpus.machine_tags[i])
            average++;
    }
    average = (average/corpus.num_lines)*100;
    return average;
}
