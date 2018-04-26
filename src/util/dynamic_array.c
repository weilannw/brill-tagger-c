#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "dynamic_array.h"
void initialize_dynamic_array(dynamic_array_t *array, size_t initial_length, uint16_t size_of){
    array->current_length = initial_length;
    array->elems = malloc(sizeof(size_of)*initial_length);
    array->size_of_elem = size_of;
    array->current_index = 0;
}
void add_to_dynamic_array(dynamic_array_t *array, void *any_type){
    if(sizeof(any_type) != array->size_of_elem){
        printf("Error: item being added to dynamic array is of incorrect size\n");
        exit(EXIT_FAILURE);
    }
    array->current_index+=1;
    if(array->current_index >= array->current_length)
        grow_dynamic_array(array);
    array->elems[array->current_index-1] = any_type;
}
static void grow_dynamic_array(dynamic_array_t *array){
    array->current_length *= 2;
    array->elems = realloc(array->elems, array->size_of_elem * array->current_length);
}
void free_dynamic_array(){

}