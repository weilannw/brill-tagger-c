#include <stdio.h>
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
    return count;
}
contextual_rule_t * parse_rules_from_file(char * fp){
    FILE * file = fopen(fp, "r");
    char *line;
    ssize_t read;
    int numlines = countlines(file);
    contextual_rule_t *rules = 
        (contextual_rule_t*)malloc(sizeof(contextual_rule_t)*numlines);
    size_t len;
    int cur = 0;
    if(file == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, file)) != -1){
        allocate_current_rule(&rules[cur]);
        parse_contextual_rule(line, &rules[cur++]);
    }
    return rules;
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