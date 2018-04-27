
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../corpus/corpus_io.h"
#include "../rules/rules.h"
#include "../tagger/tagger.h"
#include "../lib/hashmap.h"

float accuracy(rules_list_t rules, corpus_t corpus);
