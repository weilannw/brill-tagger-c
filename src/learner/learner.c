#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include "../io/corpus_io.h"
#include "../tagger/tags.h"
#include "../lib/hashmap.h"
#include "learner.h"
#include "../rules/rules.h"
#include "../util/dynamic_array.h"
#define ERROR_STARTING_LENGTH 100
dynamic_array_t learned_rules;

void learner_init(){
    initialize_dynamic_array(&learned_rules, 2, sizeof(contextual_rule_t*));
}
/*contextual_rule_t instantiate_rule(int fn, int tag1, int tag2){
    return
}*/
void add_rule(contextual_rule_t *rule){
    add_to_dynamic_array(&learned_rules, rule);
}

/* 
 first find error,
 find most frequent pattern
 find most frequent rule

 if next greatest number of errors is less 
 than most frequent pattern minus the number of 
 non-error words of same tag and pattern, stop looking
 and add to list of learned rules 
*/

HASHMAP_FUNCS_CREATE(error, int, error_t);


sorted_error_list_t *error_frequencies(corpus_t corpus){
  //  struct error_t errors;
  //  initialize_dynamic_array(&errors, ERROR_STARTING_LENGTH, sizeof(*error_t));
  //  initialize_dynamic_array(&keys, ERROR_STARTING_LENGTH, sizeof(*int));
    struct hashmap map;
    hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);
    
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.info[i].ignore_flag)
            continue;
        //If there is an error, see if the key exists
        if(corpus.machine_tags[i] != corpus.human_tags[i]){
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
                *key =corpus.human_tags[i] + corpus.machine_tags[i];
                error->number+=1;
                initialize_dynamic_array(&(error->indices), ERROR_STARTING_LENGTH, sizeof(size_t*));
                *sizetptr = i;
                add_to_dynamic_array(&(error->indices), sizetptr);
                //error->indices[error->number-1] = i;
                error->human_tag = corpus.human_tags[i];
                error->machine_tag = corpus.machine_tags[i];
                //Put the error_t struct in the hashmap with the appropriate key
                error_hashmap_put(&map, key, error);
            }
            
            //If the hashmap entry did exist, increase the frequency by 1 and keep track of the index
            else{
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
        initial_order[index] = er->number;
        index++;
    }
    
   //Qsort using the comparator helper function. We are sorting COUNT pieces of data
   qsort(initial_order, count, sizeof(int), cmpfunc);
    
    //Iterate back through the hashmap. This time, corresponding spots in the errors_ordered will be populated with
    //The correct struct. For example, if initial order has frequencies {5, 7, 9}
    //Then errors_ordered will have {error_t struct with 5 freq, error_t struct with 7 freq, error_t struct with 9 freq}
    
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        error_t *er = (error_t *)hashmap_iter_get_data(iter);
        
        //This inner loop iterates through the initial_order array and compares the current
        //error_t structs frequency value. If it's a match, the error_t struct is placed into the array
        //at the correct index. errors_ordered[i] is checked for null to avoid overwriting another struct.
        //Tiebreakers are unnecesary since error_t's with the same frequency value don't have a specific order.
        for(int i = 0; i < count; i++){
            error_t temp = errors_ordered[i];
            error_t * temppoint = &temp;
            if(er->number == initial_order[i] && !temppoint){
                errors_ordered[i] = *er;
                break;
            }
        }
    }
    errors->length = count;
    errors->errors = errors_ordered;
    
    free(initial_order);

    return errors;
    
    //Reminder, free this pointer as well as the hashmap. This array of error_t
    //point to the same spot as the hashmap, so freeing this should free up the hashmap as well.
    //Then make sure to call hashmap destroy.
}

pattern_t find_patterns(corpus_t corpus, error_t error){
    int number = error.number;
    int prev3[number];
    int prev2[number];
    int prev1[number];
    int next1[number];
    int next2[number];
    int next3[number];

    for(int i = 0; i < number; i++){
        int *prev3i  = ((int *)(error.indices.elems[number])) -3;
        int *prev2i  = ((int *)(error.indices.elems[number])) -2;
        int *prev1i  = ((int *)(error.indices.elems[number])) -1;
        int *next1i  = ((int *)(error.indices.elems[number])) +3;
        int *next2i  = ((int *)(error.indices.elems[number])) +3;
        int *next3i  = ((int *)(error.indices.elems[number])) +3;

        prev3[i] = (corpus.info[i].prev_bound<=-3)?corpus.machine_tags[*prev3i]:0;
        prev2[i] = (corpus.info[i].prev_bound<=-2)?corpus.machine_tags[*prev2i]:0;
        prev1[i] = (corpus.info[i].prev_bound<=-1)?corpus.machine_tags[*prev1i]:0;
        next1[i] = (corpus.info[i].next_bound>=1)?corpus.machine_tags[*next1i]:0;
        next2[i] = (corpus.info[i].next_bound>=2)?corpus.machine_tags[*next2i]:0;
        next3[i] = (corpus.info[i].next_bound>=3)?corpus.machine_tags[*next3i]:0;
    }
    
    pattern_t pattern;
    pattern.prevtag3 = find_most_frequent(prev3, number);
    pattern.prevtag2 = find_most_frequent(prev2, number);
    pattern.prevtag1 = find_most_frequent(prev1, number);
    pattern.nexttag1 = find_most_frequent(next1, number);
    pattern.nexttag2 = find_most_frequent(next2, number);
    pattern.nexttag3 = find_most_frequent(next3, number);
    
    return pattern;
}
/* calculates the error improved by a rule */
int get_rule_error_improvement(corpus_t corpus, contextual_rule_t rule, error_t error){
    int improvement = 0;
    int errors_created = 0;
    for(size_t i = 0; i < error.number; i++){
        int *ind = ((int *)(error.indices.elems[i]));
        if(check_contextual_rule(rule, corpus, *ind))
            improvement++;
    }
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(rule.tag1 == error.machine_tag && check_contextual_rule(rule, corpus, i)){
            errors_created++;
    }
}
   
}
//Helper method for qsort
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

//Helper method for finding most frequent tag in an array
int find_most_frequent(int* values, size_t size){
    int highest = -1;
    int temp_highest = 0;
    int temp_freq;
    int freq;
    for(size_t i = 0; i < size; i++){
        temp_freq = values[i];
        for(size_t j = 0; j < size; j++){
            if(i != j){
                if(values[j] == temp_freq) temp_highest++;
            }
        }
        if(temp_highest > highest) freq = temp_freq;
    }
    
    return freq;
}














