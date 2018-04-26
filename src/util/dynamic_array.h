#ifndef dynamic_array_h
#define dynamic_array_h
typedef struct dynamic_array_t{
    size_t current_length;
    size_t current_index;
    uint8_t size_of_elem;
    void *elems;
}dynamic_array_t;

void initialize_dynamic_array(dynamic_array_t);
void add_to_dynamic_array(dynamic_array_t *, void *);
static void grow_dynamic_array(dynamic_array_t);
#endif