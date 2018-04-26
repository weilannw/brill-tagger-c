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

rules_list_t learned_rules;

//called once by a single thread
void allocate_new_rule(rules_list_t rules){
    //rules.m
}
/*contextual_rule_t instantiate_rule(int fn, int tag1, int tag2){
    return
}*/
void add_rule(contextual_rule_t rule){
    //learned_rules.frequency 
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

hashmap_t error_frequencies(corpus_t corpus){
    
    struct hashmap map;
    
    hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);
    
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.info[i].ignore_flag)
            continue;
        //If there is an error, see if the key exists
        if(corpus.human_tags[i] != corpus.machine_tags[i]){
            int* tempkey;
            *tempkey = corpus.human_tags[i] + corpus.machine_tags[i];
            error_t *er = error_hashmap_get(&map, tempkey);
            
            //If the hashmap entry did not exist, allocate a new error_t struct and initialize variables
            //Idk how to properly malloc the struct, but I know you do. So instead of calling malloc, I
            //suppose just write a method that returns a pointer to a properly malloced error_t struct.
            //Idk how to do the int* allocation :p
            if(er == NULL){
                error_t *error = malloc (sizeof (struct error_t));
                int* key = malloc(sizeof(int*));
                *key =corpus.human_tags[i] + corpus.machine_tags[i];
                error->number+=1;
                error->indices[error->number-1] = i;
                error->human_tag = corpus.human_tags[i];
                error->machine_tag = corpus.machine_tags[i];
                
                //Put the error_t struct in the hashmap with the appropriate key
                error_hashmap_put(&map, key, error);
            }
            
            //If the hashmap entry did exist, increase the frequency by 1 and keep track of the index
            else{
                er->number+=1;
                er->indices[er->number-1] = i;
            }
        }
    }
    return map;
}

//Method used to return an array with key values in order from low to high according to frequency.
//Keys starting at index [size-1] have the highest frequency, with subsequent values having lower frequencies.
//This will prevent us from having to iterate through the hashmap n amount of times.

//This method could also just return an int* containing the keys in the correct order. Either or is easy to do.
void errors_sorted_by_frequency(hashmap_t map, struct sorted_error_list_t *errors){
  
    int index = 0;
    int count = hashmap_size(&map);
    int* initial_order;
    error_t* errors_ordered;
    
    initial_order = malloc(count * sizeof(int));
    errors_ordered = malloc(count * sizeof(error_t));
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
            /*if(er->number == initial_order[i] && errors_ordered[i] == 0){
                errors_ordered[i] = *er;
                break;
            }*/
        }
    }
    
    free(initial_order);

    
    //Reminder, free this pointer as well as the hashmap. This array of error_t
    //point to the same spot as the hashmap, so freeing this should free up the hashmap as well.
    //Then make sure to call hashmap destroy.
   errors->errors = errors_ordered;
}

//Helper method for qsort
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

