#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "dynamic_array.h"
void initialize_dynamic_array(dynamic_array_t *array, size_t initial_length, size_t size_of){
    if(initial_length == 0){
        printf("Error: dynamic array must be initialized with length of mat least 1\n");
        exit(EXIT_FAILURE);
    }
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
    if(array->current_index >= array->current_length-1)
        grow_dynamic_array(array);
    array->elems[array->current_index] = any_type;
    array->current_index+=1;
}
static void grow_dynamic_array(dynamic_array_t *array){
    array->current_length *= 2;
    array->elems = realloc(array->elems, array->size_of_elem * array->current_length);
    printf("GREW: %lu\n", array->current_length);
}
void print_dynamic_array(dynamic_array_t *array){
    for(size_t i = 0; i < array->current_index; i++)
        printf("arr[%lu]: %p\n", i, (void*)array->elems[i]);
}
void free_dynamic_array(dynamic_array_t *array){
    free(array->elems);
    array->elems = NULL;
}