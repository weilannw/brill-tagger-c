#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include "../corpus/corpus_io.h"
#include "../tagger/tags.h"
#include "../lib/hashmap.h"
#include "learner.h"
#include "../rules/rules.h"
#include "../util/dynamic_array.h"
#include "../tagger/tagger.h"
#include "../dictionary/dictionary_reduce.h"
contextual_rule_t learned_rules[NUMRULES];
size_t learned_rule_index = 0;

HASHMAP_FUNCS_CREATE(error, int, error_t);

struct hashmap global_hashmap;
/*void learner_init(){
    int size = sizeof(learned_rules)/sizeof(rules_list_t);
    for(int i = 0; i < size; i++){
        learned_rules
    }
    learned_rules
    //initialize_dynamic_array(&learned_rules, 2, sizeof(contextual_rule_t*));
}*/
/*contextual_rule_t instantiate_rule(int fn, int tag1, int tag2){
    return
}*/
/*void add_rule(contextual_rule_t *rule){
    add_to_dynamic_array(&learned_rules, rule);
}*/
void find_best_rule(corpus_t corpus){
    sorted_error_list_t *errors = error_frequencies(corpus);
    int maximprovement = -1;
    //contextual_rule_t *best_rule = (contextual_rule_t*)malloc(sizeof(contextual_rule_t));
    contextual_rule_t current_rule;
    printf("Here is the length: %zu\n", errors->length);
    for(int i = 0; i < errors->length; i++){
        error_t error = errors->errors[i];
    	printf("Trying to find patterns with error of size: %zu\n", error.number);
    //   print_dynamic_array(&error.indices);
       pattern_t pattern = find_patterns(corpus, error); // finds the most frequent prev and next tags
    	printf("prev3: %d prev2: %d prev1: %d next1: %d next2: %d next3: %d\n", pattern.prevtag3,pattern.prevtag2, pattern.prevtag1, pattern.nexttag1, pattern.nexttag2, pattern.nexttag3);
        current_rule.tag1 = error.machine_tag;
        current_rule.tag2 = error.human_tag;
        for(int ii = 0; ii < sizeof(contextual_rules); ii++){
            current_rule.triggerfn = ii;
            instantiate_rule(pattern, ii, &current_rule);
            int improvement = get_rule_error_improvement(corpus, current_rule, error);
            if(improvement>maximprovement){
                maximprovement = improvement;
                learned_rules[learned_rule_index].tag1 = current_rule.tag1;
                learned_rules[learned_rule_index].tag2 = current_rule.tag2;
                learned_rules[learned_rule_index].arg1 = current_rule.arg1;
                learned_rules[learned_rule_index].arg2 = current_rule.arg2;
                learned_rules[learned_rule_index].triggerfn = current_rule.triggerfn;
            }
        }
        if(i==errors->errors[i].number-1 || maximprovement >= errors->errors[i+1].number)
            break;
    }
    learned_rule_index++;
    apply_rule_to_corpus(learned_rules[learned_rule_index], corpus);
}
/*rule num is the index in the ruls array*/
void instantiate_rule(pattern_t pattern, int rule_num, contextual_rule_t *rule){
    int tmp;
    switch(rule_num){
        case PREV_TAG_IS:
            rule->arg1 = pattern.prevtag1;
            rule->arg2 = NONE;
            break;
        case NEXT_TAG_IS:
            rule->arg1 = pattern.nexttag1;
            rule->arg2 = NONE;
            break;        
        case PREV_2_TAG_IS:
            rule->arg1 = pattern.prevtag2;
            rule->arg2 = NONE;
            break;
        case NEXT_2_TAG_IS:
            rule->arg1 = pattern.nexttag2;
            rule->arg2 = NONE;
            break;
        case PREV_1_OR_2_TAG_IS:
            rule->arg1 = (pattern.prev1freq >= pattern.prev2freq)?pattern.prevtag1:pattern.prevtag2;
            rule->arg2 = NONE;
            break;
        case NEXT_1_OR_2_TAG_IS:
            rule->arg1 = (pattern.next1freq >= pattern.next2freq)?pattern.nexttag1:pattern.nexttag2;
            rule->arg2 = NONE;
            break;
        case PREV_1_OR_2_OR_3_TAG_IS:
            rule->arg1 = (
                    (tmp = ((pattern.prev1freq >= pattern.prev2freq)?
                        pattern.prevtag1
                        :pattern.prevtag2))
                        >pattern.prev3freq)
                            ?tmp
                            :pattern.prev3freq;
            rule->arg2 = NONE;
            break;
        case NEXT_1_OR_2_OR_3_TAG_IS:
            rule->arg1 = (
                    (tmp = ((pattern.next1freq >= pattern.next2freq)?
                        pattern.nexttag1
                        :pattern.nexttag2))
                        >pattern.next3freq)
                            ?tmp
                            :pattern.next3freq;
            rule->arg2 = NONE;
            break;
        case PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y:
            rule->arg1 = pattern.prevtag1;
            rule->arg2 = pattern.nexttag1;
            break;
        case PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y:
            rule->arg1 = pattern.prevtag1;
            rule->arg2 = pattern.nexttag2;
            break;
        case NEXT_TAG_IS_X_AND_PREV_2_TAG_IS_Y:
            rule->arg1 = pattern.nexttag1;
            rule->arg2 = pattern.prevtag2;
            break;
        case NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y:
            rule->arg1 = pattern.nexttag1;
            rule->arg2 = pattern.nexttag2;
            break;
        case PREV_TAG_IS_X_AND_PREV_2_TAG_IS_Y:
            rule->arg1 = pattern.prevtag1;
            rule->arg2 = pattern.prevtag2;
            break;
        default:
            break;
    }
}
/* calculates the error improved by a rule */
int get_rule_error_improvement(corpus_t corpus, contextual_rule_t rule, error_t error){
    int improvement = 0;
    int errors_created = 0;
    for(size_t i = 0; i < error.number; i++){
        int *intptr = (int*)error.indices.elems[i];
        if(check_contextual_rule(rule, *intptr, corpus))
            improvement++;
    }
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.machine_tags[i] == corpus.human_tags[i] &&
           check_contextual_rule(rule, i, corpus)){
                errors_created++;
        }
    }    
    return improvement - errors_created;
}

sorted_error_list_t* error_frequencies(corpus_t corpus){
  
    printf("we are currently in this method\n");
    struct hashmap map;
    hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);
    
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.info[i].ignore_flag)
            continue;
        //If there is an error, see if the key exists
      //  printf("Here is the comparisons for word %s\t %d %d\n", corpus.words[i], corpus.machine_tags[i], corpus.human_tags[i] );
        if(corpus.machine_tags[i] != corpus.human_tags[i]){
    //        printf("Checking to see if the key exists\n");
            int* tempkey;
            *tempkey = corpus.human_tags[i] + corpus.machine_tags[i];
            error_t *er = error_hashmap_get(&map, tempkey);
            size_t *sizetptr = (size_t*)malloc(sizeof(size_t));

            //If the hashmap entry did not exist, allocate a new error_t struct and initialize variables
            //Idk how to properly malloc the struct, but I know you do. So instead of calling malloc, I
            //suppose just write a method that returns a pointer to a properly malloced error_t struct.
            //Idk how to do the int* allocation :p
            if(er == NULL){
                error_t *error = malloc (sizeof (struct error_t));
                int *key = malloc(sizeof(int*));
  		//int *number = malloc(sizeof(int*));
		//*number = 1;
                *key =corpus.human_tags[i] + corpus.machine_tags[i];
     //           printf("Key value for this iteration is: %d\n", *key);
                error->number=1;
                initialize_dynamic_array(&(error->indices), ERROR_STARTING_LENGTH, sizeof(size_t*));
                *sizetptr = i;
     //           printf("Index of this error is: %zu\n", i);
                add_to_dynamic_array(&(error->indices), sizetptr);
                //error->indices[error->number-1] = i;
                error->human_tag = corpus.human_tags[i];
                error->machine_tag = corpus.machine_tags[i];
                //Put the error_t struct in the hashmap with the appropriate key
                error_hashmap_put(&map, key, error);
            }
            
            //If the hashmap entry did exist, increase the frequency by 1 and keep track of the index
            else{
	//	printf("Should be incrementing the number by 1\n");
                *sizetptr = i;
                er->number+=1;
                add_to_dynamic_array(&(er->indices), sizetptr);
            }
        }
    }
    return errors_sorted_by_frequency(map);
}

//Method used to return an array with key values in order from low to high according to frequency.
//Keys starting at index [size-1] have the highest frequency, with subsequent values having lower frequencies.
//This will prevent us from having to iterate through the hashmap n amount of times.

//This method could also just return an int* containing the keys in the correct order. Either or is easy to do.
sorted_error_list_t* errors_sorted_by_frequency(hashmap_t map){
  
    int index = 0;
    int count = hashmap_size(&map);
    int* initial_order;
    error_t* errors_ordered;
    
    initial_order = malloc(count * sizeof(int));
    sorted_error_list_t* errors= malloc(sizeof(sorted_error_list_t));
    errors_ordered = (error_t *)malloc(count * sizeof(error_t));
    memset(errors_ordered, 0, count*sizeof(error_t));
    struct hashmap_iter *iter;
    
    //Iterate through the data. Get the pointer to the error_t struct and put its frequency in the array
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        error_t *er = hashmap_iter_get_data(iter);
        //printf("human tag %d vs machine tag %d\n", er->human_tag, er->machine_tag);
        //printf("number = %zu\n", er->number);
	initial_order[index] = er->number;
        index++;
    }
    
   //Qsort using the comparator helper function. We are sorting COUNT pieces of data
   qsort(initial_order, count, sizeof(int), cmpfunc);
    
    //Iterate back through the hashmap. This time, corresponding spots in the errors_ordered will be populated with
    //The correct struct. For example, if initial order has frequencies {5, 7, 9}
    //Then errors_ordered will have {error_t struct with 5 freq, error_t struct with 7 freq, error_t struct with 9 freq}
   // printf("We have made it past qsort\n");
    //if(index == 20942)
    //for(int i = 0; i < count; i++){
//	printf("initial_order[%d] = %d\n", i, initial_order[i]);
//    }

    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        error_t *er = (error_t *)hashmap_iter_get_data(iter);
        
        //This inner loop iterates through the initial_order array and compares the current
        //error_t structs frequency value. If it's a match, the error_t struct is placed into the array
        //at the correct index. errors_ordered[i] is checked for null to avoid overwriting another struct.
        //Tiebreakers are unnecesary since error_t's with the same frequency value don't have a specific order.
        for(int i = 0; i < count; i++){
            //error_t temp = errors_ordered[i];
            //printf("Number: %d\n", temp.number);
	    error_t * temppoint = &errors_ordered[i];
	    //printf("temppoint numver = %zu\n", temppoint->number);
            //if(i!=0){ error_t*  temppoint = &errors_ordered[i]};
	    if(er->number == initial_order[i] && temppoint->number == 0){
    //            printf("Putting error with size: %zu into index %d\n", er->number, i);
		errors_ordered[i] = *er;
                break;
            }
        }
    }
    
    errors->length = count;
    errors->errors = errors_ordered;
    global_hashmap = map;
    printf("Value of length is %zu\n", errors->length); 
    free(initial_order);
    return errors;
    
    //Reminder, free this pointer as well as the hashmap. This array of error_t
    //point to the same spot as the hashmap, so freeing this should free up the hashmap as well.
    //Then make sure to call hashmap destroy.
}

pattern_t find_patterns(corpus_t corpus, error_t error){
    size_t number = error.number;
    int* prev3 = malloc(sizeof(int *) * number);
    int* prev2 = malloc(sizeof(int *) * number);
    int* prev1 = malloc(sizeof(int *) * number);
    int* next1 = malloc(sizeof(int *) * number);
    int* next2 = malloc(sizeof(int *) * number);
    int* next3 = malloc(sizeof(int *) * number);
    /*go to index of each error and get prev and next tags.*/
    for(int i = 0; i < number; i++){
        int prev3i  = *((int *)(error.indices.elems[i])) -3;
        int prev2i  = *((int *)(error.indices.elems[i])) -2;
        int prev1i  = *((int *)(error.indices.elems[i])) -1;
        int next1i  = *((int *)(error.indices.elems[i])) +1;
        int next2i  = *((int *)(error.indices.elems[i])) +2;
        int next3i  = *((int *)(error.indices.elems[i])) +3;
        prev3[i] = (corpus.info[i].prev_bound<=-3)?corpus.machine_tags[prev3i]:0;
        prev2[i] = (corpus.info[i].prev_bound<=-2)?corpus.machine_tags[prev2i]:0;
        prev1[i] = (corpus.info[i].prev_bound<=-1)?corpus.machine_tags[prev1i]:0;
        next1[i] = (corpus.info[i].next_bound>=1)?corpus.machine_tags[next1i]:0;
        next2[i] = (corpus.info[i].next_bound>=2)?corpus.machine_tags[next2i]:0;
        next3[i] = (corpus.info[i].next_bound>=3)?corpus.machine_tags[next3i]:0;
    }
    pattern_t *pattern = malloc(sizeof(pattern_t));
    size_t frequency;
    pattern->prevtag3 = find_most_frequent(prev3, &frequency, number);
    pattern->prev3freq = frequency;
    pattern->prevtag2 = find_most_frequent(prev2, &frequency, number);
    pattern->prev2freq= frequency;
    pattern->prevtag1 = find_most_frequent(prev1, &frequency, number);
    pattern->prev1freq= frequency;
    pattern->nexttag1 = find_most_frequent(next1, &frequency, number);
    pattern->next1freq= frequency;
    pattern->nexttag2 = find_most_frequent(next2, &frequency, number);
    pattern->next2freq= frequency;
    pattern->nexttag3 = find_most_frequent(next3, &frequency, number);
    pattern->next3freq= frequency;

    free(prev3);
    free(prev2);
    free(prev1);
    free(next1);
    free(next2);
    free(next3);

    printf("Done parsing pattern\n");
    return *pattern;
}

//Helper method for qsort
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

//Helper method for finding most frequent tag in the surround tags
int find_most_frequent(int* values, size_t *frequency, size_t size){
    int highest = -1;
    int count = 0; // count of an individual tag
    int tag; // stores tag
    int most_frequent;
    for(size_t i = 0; i < size; i++){
        if(i%10000 == 0) printf("Currently at index: %zu\n", i);
	count = 0;
        tag = values[i];
        for(size_t j = 0; j < size; j++){
            if(j != i) // no point checking against itself.
                if(values[j] == tag) count++;
        }
        if(count > highest)
        {
            highest = count;
            most_frequent = tag;
        }
	
    }
    *frequency = highest; 
    printf("returning most frequent: %d\n", most_frequent);
    return most_frequent;
}

hashmap_t return_map(){
	return global_hashmap;
}