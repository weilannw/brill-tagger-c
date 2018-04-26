#ifndef dynamic_array_h
#define dynamic_array_h
typedef struct dynamic_array_t{
    size_t current_length;
    size_t current_index;
    size_t size_of_elem;
    void **elems;
}dynamic_array_t;

void initialize_dynamic_array(dynamic_array_t*, size_t, size_t);
void add_to_dynamic_array(dynamic_array_t *, void *);
static void grow_dynamic_array(dynamic_array_t*);
void print_dynamic_array(dynamic_array_t *);
void free_dynamic_array(dynamic_array_t *);
#endif