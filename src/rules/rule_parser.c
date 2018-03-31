#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "rule_parser.h"
#define MAX_TAG_LEN 6
static int countlines(FILE *file){
    char cur;
    int count = 0;
    while((cur = getc(file))!=EOF)
        if(cur == '\n')
            count++;
    fseek(file, 0, SEEK_SET);
    return count;
}
rules_list_t * parse_rules_from_file(char * fp){
    FILE * file = fopen(fp, "r");
    if(file == NULL){
        printf("Could not open file '%s' (errno %d)\n", fp, errno);
        exit(EXIT_FAILURE);
    }
    printf("file: %s\n", fp);
    char *line;
    ssize_t read;
    rules_list_t *list = 
        (rules_list_t*)malloc(sizeof(rules_list_t));
    list->length = countlines(file);
    list->rules = 
        (contextual_rule_t*)malloc(sizeof(contextual_rule_t)*list->length);
    size_t len;
    int cur = 0;
    while ((read = getline(&line, &len, file)) != -1){
        printf("WOWOOW\n");
        allocate_current_rule(&(list->rules)[cur]);
        parse_contextual_rule(line, &(list->rules)[cur++]);
    }
    return list;
}
void parse_contextual_rule(char * rulestr, contextual_rule_t *rule){
    char *saveptr;
    char *attr[5];
    rule->tag1 = strtok_r(rulestr, "(>):,\n", &saveptr);
    rule->tag2 = strtok_r(NULL, "(>):,\n", &saveptr);
    rule->triggerfn = atoi(strtok_r(NULL, "(>):,\n", &saveptr)); 
        //^ index of the trigger function in the trigger function array
    rule->arg1 = strtok_r(NULL, "(>):,\n", &saveptr);
    rule->arg2 = strtok_r(NULL, "(>):,\n", &saveptr);
}
void allocate_current_rule(contextual_rule_t *rule){
    rule->arg1 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->arg2 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->tag1 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
    rule->tag2 = (char*)malloc(sizeof(char)*MAX_TAG_LEN);
}
void rules_list_print(rules_list_t *list){
    contextual_rule_t *rules = list->rules;
    for(int i = 0; i < list->length; i++){
        printf("rules[%d]:\n" 
            "tag1:%s\n"
            "tag2:%s\n"
            "fn:%d\n"
            "arg1:%s\n"
            "arg2:%s\n",
            i, rules->tag1, rules->tag2, rules->triggerfn, 
            rules->arg1, rules->arg2);
    }
}
void rules_list_free(rules_list_t *list){
    contextual_rule_t *rules = list->rules;
    for(int i = 0; i < list->length; i++){
        for(int ii = 0; ii < MAX_TAG_LEN; ii++){
            free(rules[i].arg1);
            rules[i].arg1 = NULL;
            free(rules[i].arg2);
            rules[i].arg2 = NULL;
            free(rules[i].tag1);
            rules[i].tag1 = NULL;
            free(rules[i].tag2);
            rules[i].tag2 = NULL;
        }
        free(&rules[i]);
    }
    free(list);
}