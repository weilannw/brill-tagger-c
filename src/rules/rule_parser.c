#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "rule_parser.h"
#include "../tagger/tags.h"
static void getfileinfo(FILE *file, size_t *numlines, size_t *numchars){
    char cur;
    *numlines = 0;
    *numchars = 0;
    while((cur = getc(file))!=EOF){
        *numchars+=1;
        if(cur == '\n')
            *numlines+=1;
    }
    fseek(file, 0, SEEK_SET);
}
rules_list_t * parse_rules_from_file(char * fp){
    FILE * file = fopen(fp, "r");
    if(file == NULL){
        printf("Could not open file '%s' (errno %d)\n", fp, errno);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    ssize_t read;
    rules_list_t *list = 
        (rules_list_t*)malloc(sizeof(rules_list_t));
    size_t numlines = 0;
    size_t numchars = 0;
    getfileinfo(file, &numlines, &numchars);
    list->length = numlines;
    list->rules = 
        (contextual_rule_t*)malloc(sizeof(contextual_rule_t)*list->length);
    char contents[numchars];
    int cur = 0;
    fread(contents, numchars, 1, file);
    char *line;
    char *saveptr;
    for(int i = 0; i < list->length; i++){
        if(i == 0)
            line = strtok_r(contents, "\n", &saveptr);
        else 
            line = strtok_r(NULL, "\n", &saveptr);
        parse_contextual_rule(line, &(list->rules)[i]);
    }
    fclose(file);
    return list;
}
void parse_contextual_rule(char * rulestr, contextual_rule_t *rule){
    char *saveptr;
    char *delim = "(>):,\n";
    rule->tag1 = tag_to_hash(strtok_r(rulestr, delim, &saveptr));
    rule->tag2 = tag_to_hash(strtok_r(NULL, delim, &saveptr));
    rule->triggerfn = atoi(strtok_r(NULL, delim, &saveptr)); 
        //^ index of the trigger function in the trigger function array
    rule->arg1 = tag_to_hash(strtok_r(NULL, delim, &saveptr));
    rule->arg2 = tag_to_hash(strtok_r(NULL, delim, &saveptr));
}
void rules_list_print(rules_list_t *list){
    contextual_rule_t *rules = list->rules;
    for(int i = 0; i < list->length; i++){
        printf("*******rules[%d]*******\n" 
            "tag1: %d\n"
            "tag2: %d\n"
            "fn: %d\n"
            "arg1: %d\n"
            "arg2: %d\n",
            i, 
            rules[i].tag1, 
            rules[i].tag2, 
            rules[i].triggerfn, 
            rules[i].arg1, 
            rules[i].arg2);
    }
}
void rules_list_free(rules_list_t *list){
    free(list->rules);
    free(list);
}