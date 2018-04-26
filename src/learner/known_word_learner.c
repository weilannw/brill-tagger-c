#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include "../io/corpus_io.h"
#include "../tagger/tags.h"
#include "../lib/hashmap.h"

HASHMAP_FUNCS_CREATE(error, int, error_t);

hashmap_t error_frequencies(corpus_t corpus){
    
    struct hashmap map;
    
    hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);
    
    for(size_t i = 0; i < corpus.num_lines; i++){
        if(corpus.human_tags[i] != corpus.machine_tags[i]){
            error_t er* = error_hashmap_get(&map, corpus.human_tags[i] + corpus.machine_tags[i]);
            
            //If the hashmap entry did not exist, allocate a new error_t struct and initialize variables
            //Idk how to properly malloc the struct, but I know you do. So instead of calling malloc, I
            //suppose just write a method that returns a pointer to a properly malloced error_t struct.
            //Idk how to do the int* :p
            if(er == NULL){
                struct error_t *error = malloc (sizeof (struct error_t));
                error->number+=1;
                error->indices[error->number-1] = i;
                error->human_tag = corpus.human_tags[i];
                error->machine_tag = corpus.machine_tags[i];
                
                //Put the error_t struct in the hashmap with the appropriate key
                error_hashmap_put(&map, corpus.human_tags[i] + corpus.machine_tags[i], er);
            }
            
            //If the hashmap entry did exist, increase the frequency by 1 and keep track of the index
            else{
                er->number+=1;
                er->indices[error->number-1] = i;
            }
        }
    }
    
    return map;
}

//Method used to return an array with key values in order from low to high according to frequency.
//Keys starting at index [size-1] have the highest frequency, with subsequent values having lower frequencies.
//This will prevent us from having to iterate through the hashmap n amount of times.
error_t* error_order(hashmap_t map){
  
    int index = 0;
    int count = hashmap_size(&map);
    int* initial_order;
    error_t* error_order;
    
    initial_order = malloc(count * sizeof(int));
    error_order = malloc(count * sizeof(error_t));


    struct hashmap_iter *iter;
    
    //Iterate through the data. Get the pointer to the error_t struct and put its frequency in the array
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        error_t er* = hashmap_iter_get_data(iter);
        initial_order[index] = er->number;
        index++;
    }
    
   //Qsort using the comparator helper function. We are sorting COUNT pieces of data
   qsort(initial_order, count, sizeof(int), cmpfunc);
    
    //Iterate back through the hashmap. This time, replace the curent err_order values (which are the frequencies)
    //with their corresponding keys. The array is in the correct order.
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        error_t er* = (error_t *)hashmap_iter_get_data(iter);
        
        //This inner loop iterates through the initial_order array and compares the current
        //error_t structs frequency value. If it's a match, the error_t struct is placed into the array
        //at the correct index.
        //Tiebreakers are unnecesary since error_t's with the same frequency value don't have a specific order.
        for(int i = 0; i < count; i++){
            if(er->number == initial_order[i]){
                error_order[i] = *er;
                break;
            }
        }
    }
    
    free(initial_order);

    
    //Reminder, free this pointer as well as the hashmap. This array of error_t
    //point to the same spot as the hashmap, so freeing this should free up the hashmap as well.
    //Then make sure to call hashmap destroy.
   return error_order;
    
    
}

//Helper method for qsort
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}
