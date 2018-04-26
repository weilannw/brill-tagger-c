#ifndef learner_h
#define learner_h
typedef struct error_t{
    size_t number;
    size_t *indices;
    int machine_tag; // tag is this
    int human_tag; //should be this
}error_t;
typedef struct pattern_t{
    int prevtag3;
    int prevtag2;
    int prevtag1;
    int nexttag1;
    int nexttag2;
    int nexttag3;
}pattern_t;
#endif

/* 
 first find error,
 find most frequent pattern
 find most frequent rule

 if next greatest number of errors is less 
 than most frequent pattern minus the number of 
 non-error words of same tag and pattern, stop looking
 and add to list of learned rules 
*/