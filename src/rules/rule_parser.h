#ifndef rule_parser_h
#define rule_parser_h
/*
Trigger function numbers: 
    0:PREV_TAG_IS
    1:NEXT_TAG_IS
    2:PREV_2_TAG_IS
    3:NEXT_2_TAG_IS
    4:PREV_1_OR_2_TAG_IS
    5:NEXT_1_OR_2_TAG_IS
    6:PREV_1_OR_2_OR_3_TAG_IS
    7:NEXT_1_OR_2_OR_3_TAG_IS
    8:PREV_TAG_IS_X_AND_NEXT_TAG_IS_Y
    9:PREV_TAG_IS_X_AND_NEXT_2_TAG_IS_Y
    10:NEXT_TAG_IS_X_AND_PREV_2_TAG_IS_Y
    11:NEXT_TAG_IS_X_AND_NEXT_2_TAG_IS_Y
    12:PREV_TAG_IS_X_AND_PREV_2_TAG_IS_Y
*/
typedef struct contextual_rule_t{
    int tag1;
    int tag2;
    int triggerfn;
    int arg1;
    int arg2;
}contextual_rule_t;

/* length is stored for freeing */
typedef struct rules_list_t{
    contextual_rule_t *rules ;
    int length;
}rules_list_t;
/* 
  for each index in the mem mapped file where tag1 is the current tag,
    check the trigger function passing in arg1 and arg2
    (often arg2 will be null). 
    For each of those where trig function evals
    to true, change current tag to tag2
*/
rules_list_t * parse_rules_from_file(char *);
void allocate_contextual_rule(contextual_rule_t *);
void parse_contextual_rule(char *, contextual_rule_t*);
void rules_list_free(rules_list_t*);
void rules_list_print(rules_list_t*);

/*
Tagging rules are of the form:
    ([Tag1]>[Tag2]):[Trigger function number]([args])
    if current tag is [Tag1] and the trigger function
    (indexed in rule checker trigger function) evals to true  
    change current tag to Tag2.
    Example: (APPGE>CSN):10(Z,W)
*/

    

#endif