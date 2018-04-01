#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "rule_parser.h"
#define MAX_TAG_LEN 6
#define MAX_RULE_LEN 30
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
        allocate_contextual_rule(&(list->rules)[i]);
        parse_contextual_rule(line, &(list->rules)[i]);
    }
    fclose(file);
    return list;
}
void parse_contextual_rule(char * rulestr, contextual_rule_t *rule){
    char *saveptr;
    char *delim = "(>):,\n";
    strncpy(rule->tag1, strtok_r(rulestr, delim, &saveptr), MAX_TAG_LEN);
    strncpy(rule->tag2, strtok_r(NULL, delim, &saveptr), MAX_TAG_LEN);
    rule->triggerfn = atoi(strtok_r(NULL, delim, &saveptr)); 
        //^ index of the trigger function in the trigger function array
    strncpy(rule->arg1, strtok_r(NULL, delim, &saveptr), MAX_TAG_LEN);
    strncpy(rule->arg2, strtok_r(NULL, delim, &saveptr), MAX_TAG_LEN);
}
void allocate_contextual_rule(contextual_rule_t *rule){
    rule->arg1 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->arg2 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->tag1 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->tag2 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
}
void rules_list_print(rules_list_t *list){
    contextual_rule_t *rules = list->rules;
    for(int i = 0; i < list->length; i++){
        printf("*******rules[%d]*******\n" 
            "tag1: %s\n"
            "tag2: %s\n"
            "fn: %d\n"
            "arg1: %s\n"
            "arg2: %s\n",
            i, rules[i].tag1, rules[i].tag2, rules[i].triggerfn, 
            rules[i].arg1, rules[i].arg2);
    }
}
void rules_list_free(rules_list_t *list){
    contextual_rule_t *rules = list->rules;
    for(int i = 0; i < list->length; i++){
        free(list->rules[i].arg1);
        list->rules[i].arg1 = NULL;
        free(list->rules[i].arg2);
        list->rules[i].arg2 = NULL;
        free(list->rules[i].tag1);
        list->rules[i].tag1 = NULL;
        free(list->rules[i].tag2);
        list->rules[i].tag2 = NULL;
    }
    free(list->rules);
    free(list);
}