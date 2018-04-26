#ifndef rule_io_h
#define rule_io_h
#include "../rules/rules.h"
/* 
  for each index in the mem mapped file where tag1 is the current tag,
    check the trigger function passing in arg1 and arg2
    (often arg2 will be null). 
    For each of those where trig function evals
    to true, change current tag to tag2
*/


rules_list_t * parse_rules_from_file(char *);
int get_fn_number(char *);
void get_fn_string(int, char*);
void allocate_contextual_rule(contextual_rule_t *);
void parse_contextual_rule(char *, contextual_rule_t*);
void free_rules_list(rules_list_t*);
void print_rules_debug(rules_list_t*);
void print_rules_list(rules_list_t *list);


/*
Tagging rules are of the form:
    ([Tag1]>[Tag2]):[Trigger function number]([args])
    if current tag is [Tag1] and the trigger function
    (indexed in rule checker trigger function) evals to true  
    change current tag to Tag2.
    Example: (APPGE>CSN):10(Z,W)
*/

    

#endif
