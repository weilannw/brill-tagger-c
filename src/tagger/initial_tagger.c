#include <stdio.h>
#include "../dictionary/dictionary_generator.h"
#include "tags.h"
#include "../lib/hashmap.h"
#include <strings.h>


void process_line(char* mem_map_line, map_t map){
    //memory map is a pointer to the beginning of the line in the memory map
    int hashed_value;
    
    if(hashmap_get(mymap, word, (void **)&hashed_value) == MAP_MISSING){
        //TO-DO:
        //Send most common hashed tag value.
    }
    else{
        if(apply_tag(hashed_value, mem_map_line)==-1) exit(0);
    }
    
    
}
