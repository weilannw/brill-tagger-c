//
//  dictionary_reduce.c
//  
//
//  Created by Colton Simmons on 4/23/18.
//

#include "dictionary_reduce.h"
#include "dictionary_generator.h"
#include "../lib/hashmap.h"

HASHMAP_FUNCS_CREATE(freq, const char, int);

struct hashmap reduce_map(struct hashmap map){
    struct hashmap newmap;
    hashmap_init(&newmap, hashmap_hash_string, hashmap_compare_string, 0);
    
    struct hashmap_iter *iter;
    struct tagcounts_t *data;
    iter = hashmap_iter(&map);
    
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        int highest = (int)malloc(sizeof(int));
        data = (tagcounts_t*)hashmap_iter_get_data(iter);
        highest = get_highest_frequency(data);
        char* key = (char *)hashmap_iter_get_key(iter);
        printf("Putting in key: %s with value: %d\n", key, highest);
        freq_hashmap_put(&newmap, key, highest);
    }
    hashmap_destroy(&map);
    return newmap;
}
